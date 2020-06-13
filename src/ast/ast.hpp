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

#ifndef MONOA_AST_AST_HPP
#define MONOA_AST_AST_HPP

#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace monoa::ast {

class visitor;

enum class operation
{
    assignment,
    assignment_add,
    assignment_sub,
    addition,
    subtraction,
    multiplication,
    division,
    equal,
    not_equal,
    greater_equal,
    lesser_equal,
    negation,
};

enum class basic_type
{
    unknow,

    u8,
    i8,

    u16,
    i16,

    u32,
    i32,

    u64,
    i64,

    f32,
    f64
};

class node
{
public:
    virtual auto accept(visitor* visitor) -> void = 0;
    virtual ~node() = default;
};

class statement : public node
{
public:
    virtual ~statement() = default;
};

class expression : public statement
{
public:
    virtual ~expression() = default;
};

class type
{
};

class scalar_type : public type
{
public:
    scalar_type(basic_type type) : type(type){};
    basic_type type;
};

class literal : public expression
{
public:
    std::variant<int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t, float, double> value;
    std::unique_ptr<scalar_type> type;
    auto accept(visitor* visitor) -> void override;
};

class unary_operation : public expression
{
public:
    operation op;
    std::unique_ptr<expression> right;
    auto accept(visitor* visitor) -> void override;
};

class binary_operation : public expression
{
public:
    binary_operation(std::unique_ptr<expression> left, operation op, std::unique_ptr<expression> right);
    std::unique_ptr<expression> left;
    operation op;
    std::unique_ptr<expression> right;
    auto accept(visitor* visitor) -> void override;
};

class compound_statement : public statement
{
public:
    std::vector<std::unique_ptr<statement>> statements;
    auto accept(visitor* visitor) -> void override;
};

class variable_declaration : public statement
{
public:
    std::string name;
    std::unique_ptr<type> type_name;
    std::unique_ptr<expression> expr;
    auto accept(visitor* visitor) -> void override;
};

class function_parameter : public node
{
    std::string name;
    std::unique_ptr<type> parameter_type;
    auto accept(visitor* visitor) -> void override;
};

class function_declaration : public statement
{
public:
    std::string name;
    std::vector<std::unique_ptr<function_parameter>> parameters;
    std::unique_ptr<type> return_type;
    std::unique_ptr<compound_statement> statement_list = std::make_unique<compound_statement>();
    auto accept(visitor* visitor) -> void override;
};

class return_statement : public statement
{
public:
    std::unique_ptr<expression> return_value;
    auto accept(visitor* visitor) -> void override;
};

class root : public node
{
public:
    auto accept(visitor* visitor) -> void;
    std::unique_ptr<compound_statement> statement_list;
};

} // namespace monoa::ast

#endif // MONOA_AST_AST_HPP
