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

#ifndef MONOA_AST_VISITOR_HPP
#define MONOA_AST_VISITOR_HPP

#include <ast/ast.hpp>

namespace monoa::ast {

class visitor
{
public:
    virtual auto visit(root* node) -> void = 0;
    virtual auto visit(literal* node) -> void = 0;
    virtual auto visit(unary_operation* node) -> void = 0;
    virtual auto visit(binary_operation* node) -> void = 0;
    virtual auto visit(compound_statement* node) -> void = 0;
    virtual auto visit(variable_declaration* node) -> void = 0;
    virtual auto visit(function_declaration* node) -> void = 0;
    virtual ~visitor() = default;
};

} // namespace monoa::ast

#endif // MONOA_AST_VISITOR_HPP
