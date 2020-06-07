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

#include <ast/ast.hpp>
#include <ast/visitor.hpp>

namespace monoa::ast {

auto root::accept(visitor* visitor) -> void
{
    return visitor->visit(this);
}

auto literal::accept(visitor* visitor) -> void
{
    visitor->visit(this);
}

auto unary_operation::accept(visitor* visitor) -> void
{
    visitor->visit(this);
}

binary_operation::binary_operation(std::unique_ptr<expression> left, operation op, std::unique_ptr<expression> right)
    : left(std::move(left)), op(op), right(std::move(right))
{
}

auto binary_operation::accept(visitor* visitor) -> void
{
    visitor->visit(this);
}

auto compound_statement::accept(visitor* visitor) -> void
{
    visitor->visit(this);
}

auto variable_declaration::accept(visitor* visitor) -> void
{
    visitor->visit(this);
}

auto function_declaration::accept(visitor* visitor) -> void
{
    visitor->visit(this);
}

auto return_statement::accept(visitor* visitor) -> void
{
    visitor->visit(this);
}

} // namespace monoa::ast
