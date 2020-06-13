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

namespace {

const char* prelude =
    R"(global _start
_start:
    sub rsp, 8
    call main
    mov rdi, rax
    mov rax, 60
    syscall
)";

}

namespace monoa::ast {

compiler::compiler(ast::root* ast)
{
    this->visit(ast);
}

auto compiler::result() -> std::string
{
    std::string result;
    result += "section .data\n";
    result += this->section_data;
    result += "section .text\n";
    result += prelude;
    result += this->section_text;
    return result;
}

auto compiler::is_unsigned(basic_type type) -> bool
{
    switch (type) {
    case basic_type::u8:
    case basic_type::u16:
    case basic_type::u32:
    case basic_type::u64:
        return true;
        break;
    default:
        return false;
    }
}

auto compiler::set_result_type(basic_type type) -> void
{
    if (this->result_type == type) {
        return;
    }
    auto lower = this->result_type > type ? type : this->result_type;
    auto higher = this->result_type > type ? this->result_type : type;
    switch (higher) {
    case basic_type::i64:
        this->result_type = basic_type::i64;
        break;
    case basic_type::u64:
        if (is_unsigned(lower)) {
            this->result_type = basic_type::u64;
        } else {
            this->result_type = basic_type::i64;
        }
        break;
    case basic_type::i32:
        this->result_type = basic_type::i32;
        break;
    case basic_type::u32:
        if (is_unsigned(lower)) {
            this->result_type = basic_type::u32;
        } else {
            this->result_type = basic_type::i32;
        }
        break;
    case basic_type::i16:
        this->result_type = basic_type::i16;
        break;
    case basic_type::u16:
        if (is_unsigned(lower)) {
            this->result_type = basic_type::u16;
        } else {
            this->result_type = basic_type::i16;
        }
        break;
    case basic_type::i8:
        this->result_type = basic_type::i8;
        break;
    case basic_type::u8:
        if (is_unsigned(lower)) {
            this->result_type = basic_type::u8;
        } else {
            this->result_type = basic_type::i8;
        }
        break;
    default:
        this->result_type = type;
    }
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
    this->set_result_type(node->type->type);
    switch (node->type->type) {
    case ast::basic_type::i8:
        this->push(std::get<int8_t>(node->value));
        break;
    case ast::basic_type::u8:
        this->push(std::get<uint8_t>(node->value));
        break;
    case ast::basic_type::i16:
        this->push(std::get<int16_t>(node->value));
        break;
    case ast::basic_type::u16:
        this->push(std::get<uint16_t>(node->value));
        break;
    case ast::basic_type::i32:
        this->push(std::get<int32_t>(node->value));
        break;
    case ast::basic_type::u32:
        this->push(std::get<uint32_t>(node->value));
        break;
    case ast::basic_type::i64:
        this->push(std::get<int64_t>(node->value));
        break;
    case ast::basic_type::u64:
        this->push(std::get<uint64_t>(node->value));
        break;
    default:
        break;
    }
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
        this->pop("rbx");
        this->pop("rax");
        this->command("add rax, rbx");
        this->push("rax");
        break;
    case ast::operation::subtraction:
        this->pop("rbx");
        this->pop("rax");
        this->command("sub rax, rbx");
        this->push("rax");
        break;
    case ast::operation::multiplication:
        this->pop("rbx");
        this->pop("rax");
        if (this->is_unsigned(this->result_type)) {
            this->command("imul rbx");
        } else {
            this->command("mul rbx");
        }
        this->push("rax");
        break;
    case ast::operation::division:
        this->pop("rbx");
        this->pop("rax");
        if (this->is_unsigned(this->result_type)) {
            this->command("idiv rbx");
        } else {
            this->command("div rbx");
        }
        this->push("rax");
        break;
    default:
        this->error_string = "unexpected operator";
    }
    this->result_type = basic_type::unknow;
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
    this->label("global " + node->name + ":function");
    this->label(node->name + ":");
    node->statement_list->accept(this);
    this->pop("rax");

    if (this->stack_length > 0) {
        this->command("add rsp, " + std::to_string(this->stack_length));
    }

    this->command("ret");
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
}

auto compiler::has_error() -> bool
{
    return this->error_string.has_value();
}

auto compiler::label(std::string lab) -> void
{
    this->section_text += lab + "\n";
}

auto compiler::command(std::string cmd) -> void
{
    this->section_text += "    " + cmd + "\n";
}

auto compiler::push(uint64_t data) -> void
{
    this->stack_length += 8;
    this->command("push " + std::to_string(data));
}

auto compiler::push(std::string reg) -> void
{
    this->stack_length += 8;
    this->command("push " + reg);
}

auto compiler::pop(std::string reg) -> void
{
    this->stack_length -= 8;
    this->command("pop " + reg);
}

} // namespace monoa::ast
