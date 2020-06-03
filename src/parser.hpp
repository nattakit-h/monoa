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

#ifndef MONOA_PARSER_HPP
#define MONOA_PARSER_HPP

#include <memory>
#include <vector>
#include <ast/ast.hpp>
#include <token.hpp>

namespace monoa {

class parser {
public:
    parser(std::vector<token> tokens);
    auto ast() -> ast::root*;

private:
    unsigned int current = 0;
    std::vector<token> tokens;
    std::unique_ptr<ast::root> syntax_tree;

    auto is_end() -> bool;
    auto peek() -> token;
    auto advance() -> token;
    auto peek_type() -> token_type;
    auto parse() -> void;
    auto make_statement(std::unique_ptr<ast::statement> statement) -> void;
    auto make_expression() -> std::unique_ptr<ast::expression>;
    auto make_constant() -> std::unique_ptr<ast::literal>;
    auto make_decl_var() -> void;
};

} // namespace monoa

#endif // MONOA_PARSER_HPP
