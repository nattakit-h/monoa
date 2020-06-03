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

namespace monoa::ast
{

auto printer::visit(root* node) -> void
{
    std::cout << "root" << std::endl;
    node->statement_list->accept(this);
}

auto printer::visit(literal* node) -> void
{
    std::cout << "literal : " << std::get<int>(node->value) << std::endl;
}

auto printer::visit(unary_operation* node) -> void
{
    std::cout << "unary_operation" << std::endl;
}

auto printer::visit(binary_operation* node) -> void
{
    std::cout << "binary_operation" << std::endl;
}

auto printer::visit(compound_statement* node) -> void
{
    std::cout << "compound_statement" << std::endl;
    for (auto & s : node->statements) {
        s->accept(this);
    }
}

auto printer::visit(variable_declaration* node) -> void
{
    std::cout << "variable_declaration : " << node->name << std::endl;
    node->expr->accept(this);
}

auto printer::visit(function_declaration* node) -> void
{
    std::cout << "function_declaration" << std::endl;
    node->statement_list->accept(this);
}

}
