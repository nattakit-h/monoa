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

#ifndef MONOA_VM_COMPILER_HPP
#define MONOA_VM_COMPILER_HPP

#include <cstdint>
#include <optional>
#include <vector>
#include <ast/ast.hpp>
#include <ast/visitor.hpp>
#include <vm/opcode.hpp>

namespace monoa::vm {

class compiler : public ast::visitor
{
public:
    compiler(ast::root* ast);
    auto opcodes() -> std::vector<std::uint8_t>;
    auto print_opcodes() -> void;

    auto visit(ast::root* node) -> void;
    auto visit(ast::literal* node) -> void;
    auto visit(ast::unary_operation* node) -> void;
    auto visit(ast::binary_operation* node) -> void;
    auto visit(ast::compound_statement* node) -> void;
    auto visit(ast::variable_declaration* node) -> void;
    auto visit(ast::function_declaration* node) -> void;
    auto visit(ast::function_parameter* node) -> void;
    auto visit(ast::return_statement* node) -> void;

private:
    std::optional<std::string> error_string;
    std::vector<std::uint8_t> program;

    auto has_error() -> bool;
    auto emit(opcode data) -> void;
    auto emit(std::uint8_t data) -> void;
    auto emit(std::uint16_t data) -> void;
    auto emit(std::uint32_t data) -> void;
    auto emit(std::uint64_t data) -> void;
};

} // namespace monoa::vm

#endif // MONOA_VM_COMPILER_HPP
