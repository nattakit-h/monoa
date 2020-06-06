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

#include <cctype>
#include <iostream>
#include <parser/lexer.hpp>

namespace {

constexpr unsigned int token_string_padding = 17;

}

namespace monoa::parser {

lexer::lexer(std::string source) : source(source)
{
    this->process_source();
}

auto lexer::get_tokens() -> std::vector<token>
{
    return this->tokens;
}

auto lexer::print_tokens() -> void
{
    unsigned int line = 0;
    for (token token : this->tokens) {
        if (token.line != line) {
            line = token.line;
            std::cout << token.line << std::endl;
        }

        std::string message = "| " + token.type_string();

        unsigned int padding_length;
        if (message.length() > token_string_padding) {
            padding_length = 0;
        } else {
            padding_length = token_string_padding - message.length();
        }

        std::string padding;
        for (int i = 0; i < padding_length; i++) {
            padding += ' ';
        }

        std::cout << message << padding << " : " << token.string() << std::endl;
    }
}

auto lexer::process_source() -> void
{
    while (!this->is_end()) {
        if (!this->tokens.empty() && this->tokens.back().type == token::type::ctr_error) {
            break;
        }

        switch (this->peek()) {
        case '\n':
            this->consume_new_line();
            break;
        case '\t':
        case ' ':
            this->consume_white_space();
            break;
        case '+':
            this->consume_operator(token::type::opt_plus);
            break;
        case '-':
            if (this->peek_next() == '>') {
                this->consume_operator(token::type::opt_return, 2);
            } else {
                this->consume_operator(token::type::opt_minus);
            }
            break;
        case '=':
            if (this->peek_next() == '=') {
                this->consume_operator(token::type::opt_equal_equal, 2);
            } else {
                this->consume_operator(token::type::opt_equal);
            }
            break;
        case ':':
            this->consume_operator(token::type::puc_colon);
            break;
        case ';':
            this->consume_operator(token::type::puc_semi_colon);
            break;
        case '(':
            this->consume_operator(token::type::puc_left_paren);
            break;
        case ')':
            this->consume_operator(token::type::puc_right_paren);
            break;
        case '{':
            this->consume_operator(token::type::puc_left_brace);
            break;
        case '}':
            this->consume_operator(token::type::puc_right_brace);
            break;
        case 'f':
            this->consume_keyword("fun", token::type::key_fun);
            break;
        case 'l':
            this->consume_keyword("let", token::type::key_let);
            break;
        case 'r':
            this->consume_keyword("return", token::type::key_return);
            break;
        case '"':
            this->consume_string();
            break;
        default:
            this->consume_literal();
            break;
        }
    }
}

auto lexer::make_token(enum token::type type, std::string lexeme) -> void
{
    this->tokens.emplace_back(token{type, lexeme, this->line});
}

auto lexer::is_end() -> bool
{
    return this->current >= this->source.length();
}

auto lexer::peek() -> unsigned char
{
    return this->source[this->current];
}

auto lexer::peek_next() -> unsigned char
{
    return this->is_end() ? '\0' : this->source[this->current + 1];
}

auto lexer::consume_char(unsigned int amount) -> char
{
    char start_char = this->peek();
    this->current += amount;
    return start_char;
}

auto lexer::consume_word() -> std::string
{
    std::string word;
    while (!is_end() && (std::isalnum(this->peek()) || this->peek() == '_')) {
        word.push_back(this->consume_char());
    }
    return word;
}

auto lexer::consume_new_line() -> void
{
    this->line++;
    this->consume_char();
}

auto lexer::consume_white_space() -> void
{
    while (std::isblank(this->peek())) {
        this->consume_char();
    }
}

auto lexer::consume_operator(enum token::type type, unsigned int length) -> void
{
    this->consume_char(length);
    this->make_token(type, "");
}

auto lexer::consume_keyword(std::string expected, enum token::type type) -> void
{
    std::string word = this->consume_word();
    if (!expected.empty() && word == expected) {
        this->make_token(type, "");
    } else if (!word.empty()) {
        this->make_token(token::type::lit_identifier, word);
    } else {
        this->make_token(token::type::ctr_error, word);
    }
}

auto lexer::consume_literal() -> void
{
    if (std::isspace(this->peek())) {
        this->consume_white_space();
    } else if (!std::isalnum(this->peek()) && this->peek() != '_') {
        this->make_token(token::type::ctr_error, std::string(1, this->consume_char()));
    } else if (std::isdigit(this->peek())) {
        this->consume_number();
    } else {
        this->make_token(token::type::lit_identifier, this->consume_word());
    }
}

auto lexer::consume_number() -> void
{
    std::string number;
    enum token::type type = token::type::lit_int;
    while (std::isdigit(this->peek())) {
        number += this->consume_char();
    }
    if (this->peek() == '.') {
        number += this->consume_char();
        type = token::type::lit_float; // TODO: Check for trailing dot ?
        while (std::isdigit(this->peek())) {
            number += this->consume_char();
        }
    }
    this->make_token(type, number);
}

auto lexer::consume_string() -> void
{
    std::string value;
    this->consume_char();
    while (!is_end()) {
        if (this->peek() != '"') {
            value += this->consume_char();
        } else {
            this->consume_char();
            this->make_token(token::type::lit_string, value);
            return;
        }
    }
    this->make_token(token::type::ctr_error, "");
}

} // namespace monoa
