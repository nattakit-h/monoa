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

#ifndef MONOA_PARSER_LEXER_HPP
#define MONOA_PARSER_LEXER_HPP

#include <string>
#include <vector>
#include <parser/token.hpp>

namespace monoa::parser {

class lexer
{
public:
    lexer(std::string source);
    auto get_tokens() -> std::vector<token>;
    auto print_tokens() -> void;

private:
    unsigned int current = 0;
    unsigned int line = 1;
    std::vector<token> tokens;
    std::string source;
    auto process_source() -> void;
    auto make_token(enum token::type type, std::string lexeme) -> void;
    auto is_end() -> bool;
    auto peek() -> unsigned char;
    auto peek_next() -> unsigned char;
    auto consume_char(unsigned int amount = 1) -> char;
    auto consume_word() -> std::string;
    auto consume_new_line() -> void;
    auto consume_white_space() -> void;
    auto consume_operator(enum token::type type, unsigned int length = 1) -> void;
    auto consume_keyword(std::string expected, enum token::type type) -> void;
    auto consume_literal() -> void;
    auto consume_number() -> void;
    auto consume_string() -> void;
};

} // namespace monoa::parser

#endif // MONOA_PARSER_LEXER_HPP
