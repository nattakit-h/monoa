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

#include <iostream>
#include <ast/printer.hpp>

namespace monoa::ast {

auto printer::print(root* node) -> void
{
    this->visit(node);
}

auto printer::visit(root* node) -> void
{
    node->statement_list->accept(this);
}

auto printer::visit(literal* node) -> void
{
    switch (node->type->type) {
    case ast::basic_type::i8:
        this->print_node("lit : " + std::to_string(std::get<int8_t>(node->value)));
        break;
    case ast::basic_type::u8:
        this->print_node("lit : " + std::to_string(std::get<uint8_t>(node->value)));
        break;
    case ast::basic_type::i16:
        this->print_node("lit : " + std::to_string(std::get<int16_t>(node->value)));
        break;
    case ast::basic_type::u16:
        this->print_node("lit : " + std::to_string(std::get<uint16_t>(node->value)));
        break;
    case ast::basic_type::i32:
        this->print_node("lit : " + std::to_string(std::get<int32_t>(node->value)));
        break;
    case ast::basic_type::u32:
        this->print_node("lit : " + std::to_string(std::get<uint32_t>(node->value)));
        break;
    case ast::basic_type::i64:
        this->print_node("lit : " + std::to_string(std::get<int64_t>(node->value)));
        break;
    case ast::basic_type::u64:
        this->print_node("lit : " + std::to_string(std::get<uint64_t>(node->value)));
        break;
    }
}

auto printer::visit(unary_operation* node) -> void
{
    this->print_node("un_op");
}

auto printer::visit(binary_operation* node) -> void
{
    this->print_node("bi_op : " + std::to_string(static_cast<int>(node->op)));
    this->level++;
    node->right->accept(this);
    node->left->accept(this);
    this->level--;
}

auto printer::visit(compound_statement* node) -> void
{
    this->print_node("block");

    this->level++;
    for (auto& s : node->statements) {
        s->accept(this);
    }
    this->level--;
}

auto printer::visit(variable_declaration* node) -> void
{
    this->print_node("var_delc : " + node->name);

    this->level++;
    node->expr->accept(this);
    this->level--;
}

auto printer::visit(function_declaration* node) -> void
{
    this->print_node("fun_delc : " + node->name);

    this->level++;
    node->statement_list->accept(this);
    this->level--;
}

auto printer::visit(function_parameter* node) -> void
{
    this->print_node("fun_param");
}

auto printer::visit(return_statement* node) -> void
{
    this->print_node("ret_stmt");

    this->level++;
    node->return_value->accept(this);
    this->level--;
}

auto printer::print_node(std::string message) -> void
{
    std::string line_level = " |";
    std::string line;

    for (int i = 0; i < this->level; i++) {
        line += line_level;
    }
    line += "-";
    line.erase(0, 1);

    std::cout << line << message << std::endl;
}

} // namespace monoa::ast
