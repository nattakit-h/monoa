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
#include <parser.hpp>

namespace monoa {

parser::parser(std::vector<token> tokens) : tokens(tokens)
{
    this->parse();
}

auto parser::ast() -> ast::root*
{
    return this->syntax_tree.get();
}

auto parser::is_end() -> bool
{
    return this->current == this->tokens.size() - 1;
}

auto parser::peek() -> token
{
    return this->tokens[current];
}

auto parser::peek_type() -> token_type
{
    return this->tokens[current].type;
}

auto parser::advance() -> token
{
    if (!this->is_end()) {
        return this->tokens[this->current++];
    } else {
        return this->tokens[this->current];
    }
}

auto parser::parse() -> void
{
    this->syntax_tree = std::make_unique<ast::root>();
    this->syntax_tree->statement_list = std::make_unique<ast::compound_statement>();
    while (!is_end()) {
        switch (this->peek_type()) {
        case token_type::key_let:
            this->make_decl_var();
            break;
        default:
            this->advance();
        }
    }
}

auto parser::make_statement(std::unique_ptr<ast::statement> statement) -> void
{
    this->syntax_tree->statement_list->statements.emplace_back(std::move(statement));
}

auto parser::make_expression() -> std::unique_ptr<ast::expression>
{
    bool end = false;
    std::unique_ptr<ast::expression> expr;
    while (!end) {
        switch(this->peek_type()) {
            case token_type::lit_int:
                expr = this->make_constant();
                break;
            case token_type::puc_semi_colon:
                this->advance();
                end = true;
                break;
        }
    }
    return expr;
}

auto parser::make_constant() -> std::unique_ptr<ast::literal>
{
    auto c = std::make_unique<ast::literal>();
    c->value = (std::stoi(this->advance().lexeme));
    c->type = ast::basic_type::i32;
    return c;
}

auto parser::make_decl_var() -> void
{
    this->advance();
    auto var_decl = std::make_unique<ast::variable_declaration>();
    var_decl->name = this->advance().lexeme; // TODO: Check for identifier
    this->advance();                         // assignment
    var_decl->expr = make_expression();
    this->make_statement(std::move(var_decl));
}

} // namespace monoa
