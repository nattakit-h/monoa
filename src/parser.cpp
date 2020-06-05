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

auto parser::error() -> std::optional<std::string>
{
    return this->error_string;
}

auto parser::set_error(std::string message) -> void
{
    this->error_string = message + " at line : " + std::to_string(this->peek().line);
}

auto parser::is_end() -> bool
{
    return this->current == this->tokens.size() - 1 || this->error_string.has_value();
}

auto parser::peek() -> token
{
    return this->tokens[this->current];
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
    this->syntax_tree->statement_list = this->make_compound_statement();
}

auto parser::make_compound_statement() -> std::unique_ptr<ast::compound_statement>
{
    auto comp_stmt = std::make_unique<ast::compound_statement>();

    std::optional<enum token::type> end_token;
    if (this->peek().type == token::type::puc_left_brace) {
        end_token = token::type::puc_right_brace;
        this->advance();
    }

    while (!this->is_end() && end_token.value_or(token::type::ctr_error) != this->peek().type) {
        switch (this->peek().type) {
        case token::type::key_let:
            comp_stmt->statements.emplace_back(this->make_decl_var());
            break;
        case token::type::key_fun:
            comp_stmt->statements.emplace_back(this->make_decl_fun());
            break;
        case token::type::key_return:
            comp_stmt->statements.emplace_back(this->make_return());
            break;
        default:
            this->set_error("unexpected '" + this->peek().lexeme + "'");
        }
    }

    if (this->peek().type == end_token) {
        this->advance();
    }

    return comp_stmt;
}

auto parser::make_expression() -> std::unique_ptr<ast::expression>
{
    std::unique_ptr<ast::expression> expr;
    bool end = false;
    std::optional<enum token::type> end_token;
    if (this->peek().type == token::type::puc_right_brace) {
        this->advance();
        end_token = token::type::puc_left_brace;
    }

    while (!end && !this->error_string.has_value() && (!end_token.has_value() || this->peek().type == end_token)) {
        switch (this->peek().type) {
        case token::type::lit_int:
            expr = this->make_constant();
            break;
        case token::type::puc_semi_colon:
            this->advance();
            end = true;
            break;
        default:
            this->error_string = "unexpected '" + this->peek().lexeme + "' at line : " + std::to_string(this->peek().line);
            break;
        }
    }

    if (end_token.has_value()) {
        this->advance();
    }

    return expr;
}

auto parser::make_constant() -> std::unique_ptr<ast::literal>
{
    auto c = std::make_unique<ast::literal>();
    c->value = (std::stoi(this->advance().lexeme));
    c->type = std::make_unique<ast::scalar_type>(ast::basic_type::i32);
    return c;
}

auto parser::make_decl_var() -> std::unique_ptr<ast::variable_declaration>
{
    auto var_decl = std::make_unique<ast::variable_declaration>();
    this->advance();
    if (this->peek().type != token::type::lit_identifier) {
        this->error_string = "expecting variable name";
    }
    var_decl->name = this->advance().lexeme;
    this->advance(); // assignment
    var_decl->expr = make_expression();
    return var_decl;
}

auto parser::make_decl_fun() -> std::unique_ptr<ast::function_declaration>
{
    auto fun_decl = std::make_unique<ast::function_declaration>();
    this->advance();                         // fun
    fun_decl->name = this->advance().lexeme; // fun name
    fun_decl->parameters = this->make_fun_parameters();
    if (this->peek().type == token::type::opt_return) {
        advance(); // return opt
        fun_decl->return_type = std::make_unique<ast::scalar_type>(ast::basic_type::i32);
        advance();
    }
    fun_decl->statement_list = this->make_compound_statement();
    return fun_decl;
}

auto parser::make_fun_parameters() -> std::vector<std::unique_ptr<ast::function_parameter>>
{
    this->advance();
    this->advance();
    auto fun_parameters = std::vector<std::unique_ptr<ast::function_parameter>>();
    return fun_parameters;
}

auto parser::make_return() -> std::unique_ptr<ast::return_statement>
{
    auto ret_stmt = std::make_unique<ast::return_statement>();
    this->advance();
    ret_stmt->return_value = this->make_expression();
    return ret_stmt;
}

} // namespace monoa
