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

#ifndef MONOA_AST_COMPILER_HPP
#define MONOA_AST_COMPILER_HPP

#include <cstdint>
#include <optional>
#include <vector>
#include <ast/ast.hpp>
#include <ast/visitor.hpp>

namespace monoa::ast {

class compiler : public visitor
{
public:
    compiler(root* ast);
    auto result() -> std::string;

    auto visit(root* node) -> void;
    auto visit(literal* node) -> void;
    auto visit(unary_operation* node) -> void;
    auto visit(binary_operation* node) -> void;
    auto visit(compound_statement* node) -> void;
    auto visit(variable_declaration* node) -> void;
    auto visit(function_declaration* node) -> void;
    auto visit(function_parameter* node) -> void;
    auto visit(return_statement* node) -> void;

private:
    std::optional<std::string> error_string;
    basic_type result_type = basic_type::unknow;
    std::string section_text;
    std::string section_data;
    unsigned int stack_length = 0;

    auto has_error() -> bool;
    auto is_unsigned(basic_type type) -> bool;
    auto set_result_type(basic_type type) -> void;
    auto label(std::string lab) -> void;
    auto command(std::string cmd) -> void;
    auto push(uint64_t data) -> void;
    auto push(std::string reg) -> void;
    auto pop(std::string reg) -> void;
};

} // namespace monoa::ast

#endif // MONOA_AST_COMPILER_HPP
