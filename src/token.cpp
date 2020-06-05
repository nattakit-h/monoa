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

#include <token.hpp>

namespace monoa {

auto token::string() -> std::string
{
    switch (this->type) {
    case token::type::puc_left_paren:
        return "(";
    case token::type::puc_right_paren:
        return ")";
    case token::type::puc_left_brace:
        return "{";
    case token::type::puc_right_brace:
        return "}";
    case token::type::puc_colon:
        return ":";
    case token::type::puc_semi_colon:
        return ";";
    case token::type::opt_plus:
        return "+";
    case token::type::opt_minus:
        return "-";
    case token::type::opt_star:
        return "*";
    case token::type::opt_slash:
        return "/";
    case token::type::opt_equal:
        return "=";
    case token::type::opt_return:
        return "->";
    case token::type::key_let:
        return "let";
    case token::type::key_fun:
        return "fun";
    case token::type::key_return:
        return "return";
    case token::type::lit_identifier:
    case token::type::lit_int:
    case token::type::lit_float:
    case token::type::lit_string:
        return this->lexeme;
    case token::type::ctr_error:
        return "error";
    default:
        return "ctr_unknow";
    }
}

auto token::type_string() -> std::string
{
    switch (this->type) {
    case token::type::puc_left_paren:
        return "puc_left_paren";
    case token::type::puc_right_paren:
        return "puc_right_paren";
    case token::type::puc_left_brace:
        return "puc_left_brace";
    case token::type::puc_right_brace:
        return "puc_right_brace";
    case token::type::puc_colon:
        return "puc_colon";
    case token::type::puc_semi_colon:
        return "puc_semi_colon";
    case token::type::opt_plus:
        return "opt_plus";
    case token::type::opt_minus:
        return "opt_minus";
    case token::type::opt_star:
        return "opt_star";
    case token::type::opt_slash:
        return "opt_slash";
    case token::type::opt_equal:
        return "opt_equal";
    case token::type::opt_return:
        return "opt_return";
    case token::type::lit_identifier:
        return "lit_identifier";
    case token::type::lit_int:
        return "lit_int";
    case token::type::lit_float:
        return "lit_float";
    case token::type::lit_string:
        return "lit_string";
    case token::type::key_let:
        return "key_let";
    case token::type::key_fun:
        return "key_fun";
    case token::type::key_return:
        return "key_return";
    case token::type::ctr_error:
        return "ctr_error";
    default:
        return "ctr_unknow";
    }
}

} // namespace monoa
