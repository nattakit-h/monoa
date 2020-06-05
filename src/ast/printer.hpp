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

#ifndef MONOA_AST_PRINTER_HPP
#define MONOA_AST_PRINTER_HPP

#include <ast/visitor.hpp>

namespace monoa::ast {

class printer : visitor
{
public:
    auto visit(root* node) -> void override;
    auto visit(literal* node) -> void override;
    auto visit(unary_operation* node) -> void override;
    auto visit(binary_operation* node) -> void override;
    auto visit(compound_statement* node) -> void override;
    auto visit(variable_declaration* node) -> void override;
    auto visit(function_declaration* node) -> void override;
    auto visit(function_parameter* node) -> void override;
    auto visit(return_statement* node) -> void override;

private:
    unsigned int level = 0;

    auto print_node(std::string message) -> void;
};

} // namespace monoa::ast

#endif // MONOA_AST_PRINTER_HPP
