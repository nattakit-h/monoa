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

#ifndef MONOA_PARSER_PARSER_HPP
#define MONOA_PARSER_PARSER_HPP

#include <memory>
#include <optional>
#include <vector>
#include <ast/ast.hpp>
#include <parser/token.hpp>

namespace monoa::parser {

class parser
{
public:
    parser(std::vector<token> tokens);
    auto ast() -> ast::root*;
    auto error() -> std::optional<std::string>;

private:
    unsigned int current = 0;
    std::vector<token> tokens;
    std::optional<std::string> error_string;
    std::unique_ptr<ast::root> syntax_tree;

    auto set_error(std::string message) -> void;
    auto is_end() -> bool;
    auto peek() -> token;
    auto advance() -> token;
    auto parse() -> void;
    auto make_compound_statement() -> std::unique_ptr<ast::compound_statement>;
    auto make_expression() -> std::unique_ptr<ast::expression>;
    auto make_constant() -> std::unique_ptr<ast::literal>;
    auto make_decl_var() -> std::unique_ptr<ast::variable_declaration>;
    auto make_decl_fun() -> std::unique_ptr<ast::function_declaration>;
    auto make_fun_parameters() -> std::vector<std::unique_ptr<ast::function_parameter>>;
    auto make_return() -> std::unique_ptr<ast::return_statement>;
};

} // namespace monoa::parser

#endif // MONOA_PARSER_PARSER_HPP
