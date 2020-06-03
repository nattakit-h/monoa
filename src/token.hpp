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

#ifndef MONOA_TOKEN_HPP
#define MONOA_TOKEN_HPP

#include <string>

namespace monoa {

enum class token_type
{
    puc_left_paren,
    puc_right_paren,
    puc_left_brace,
    puc_right_brace,
    puc_dot,
    puc_comma,
    puc_colon,
    puc_semi_colon,

    opt_plus,
    opt_minus,
    opt_star,
    opt_slash,

    opt_equal,
    opt_equal_equal,
    opt_bang,
    opt_bang_equal,
    opt_greater,
    opt_greater_equal,
    opt_lesser,
    opt_lesser_equal,

    lit_identifier,
    lit_int,
    lit_dec,
    lit_string,

    typ_int,
    typ_dec,
    typ_string,

    key_if,
    key_else,
    key_for,
    key_let,
    key_fun,

    ctr_error
};

auto get_token_type_string(token_type type) -> std::string;

struct token
{
    token_type type = token_type::ctr_error;
    std::string lexeme = "";
    unsigned int line = 0;
};

} // namespace monoa

#endif // MONOA_TOKEN_HPP
