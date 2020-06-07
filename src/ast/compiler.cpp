/*
 * This file is part of Monoa
 * Copyright (c) 2020 Nattakit Hosapsin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iomanip>
#include <iostream>
#include <ast/compiler.hpp>

namespace monoa::ast {

compiler::compiler(ast::root* ast)
{
    this->visit(ast);
}

auto compiler::opcodes() -> std::vector<std::uint8_t>
{
    return this->program;
}

auto compiler::print_opcodes() -> void
{
    constexpr unsigned int line_max = 10;
    unsigned int line = 0;
    std::cout << std::hex << std::uppercase;
    for (std::uint8_t opcode : program) {
        std::cout << "0x" << std::setfill('0') << std::setw(2) << static_cast<int>(opcode) << " ";
        if (line++ == line_max - 1) {
            std::cout << std::endl;
            line = 0;
        }
    }
    std::cout << std::dec << std::nouppercase << std::endl;
}

auto compiler::visit(ast::root* node) -> void
{
    if (this->has_error()) {
        return;
    }
    node->statement_list->accept(this);
}

auto compiler::visit(ast::literal* node) -> void
{
    this->emit(vm::opcode::op_push_32);
    this->emit(static_cast<uint32_t>(std::get<int>(node->value))); //  TODO: Fix this
}

auto compiler::visit(ast::unary_operation* node) -> void
{
    if (this->has_error()) {
        return;
    }
}

auto compiler::visit(ast::binary_operation* node) -> void
{
    if (this->has_error()) {
        return;
    }
    node->left->accept(this);
    node->right->accept(this);
    switch (node->op) {
    case ast::operation::addition:
        this->emit(vm::opcode::op_add_32);
        break;
    case ast::operation::subtraction:
        this->emit(vm::opcode::op_sub_32);
        break;
    case ast::operation::multiplication:
        this->emit(vm::opcode::op_mul_32);
        break;
    case ast::operation::division:
        this->emit(vm::opcode::op_div_32);
        break;
    default:
        this->error_string = "unexpected operator";
    }
}

auto compiler::visit(ast::compound_statement* node) -> void
{
    if (this->has_error()) {
        return;
    }
    for (auto& statement : node->statements) {
        statement->accept(this);
    }
}

auto compiler::visit(ast::variable_declaration* node) -> void
{
    if (this->has_error()) {
        return;
    }
}

auto compiler::visit(ast::function_declaration* node) -> void
{
    if (this->has_error()) {
        return;
    }
    node->statement_list->accept(this);
}

auto compiler::visit(ast::function_parameter* node) -> void
{
    if (this->has_error()) {
        return;
    }
}

auto compiler::visit(ast::return_statement* node) -> void
{
    if (this->has_error()) {
        return;
    }
    node->return_value->accept(this);
    this->emit(vm::opcode::op_ret);
}

auto compiler::has_error() -> bool
{
    return this->error_string.has_value();
}

auto compiler::emit(vm::opcode data) -> void
{
    this->program.emplace_back(static_cast<std::uint8_t>(data));
}

auto compiler::emit(std::uint8_t data) -> void
{
    this->program.emplace_back(data);
}

auto compiler::emit(std::uint16_t data) -> void
{
    this->program.emplace_back((data >> 8) & 0xFF);
    this->program.emplace_back(data & 0xFF);
}

auto compiler::emit(std::uint32_t data) -> void
{
    this->program.emplace_back((data >> 24) & 0xFF);
    this->program.emplace_back((data >> 16) & 0xFF);
    this->program.emplace_back((data >> 8) & 0xFF);
    this->program.emplace_back(data & 0xFF);
}

auto compiler::emit(std::uint64_t data) -> void
{
    this->program.emplace_back((data >> 56) & 0xFF);
    this->program.emplace_back((data >> 48) & 0xFF);
    this->program.emplace_back((data >> 40) & 0xFF);
    this->program.emplace_back((data >> 32) & 0xFF);
    this->program.emplace_back((data >> 24) & 0xFF);
    this->program.emplace_back((data >> 16) & 0xFF);
    this->program.emplace_back((data >> 8) & 0xFF);
    this->program.emplace_back(data & 0xFF);
}

} // namespace monoa::ast
