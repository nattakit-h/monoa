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

auto get_token_type_string(token_type type) -> std::string
{
    switch (type) {
    case token_type::puc_left_paren:
        return "puc_left_paren";
    case token_type::puc_right_paren:
        return "puc_right_paren";
    case token_type::puc_left_brace:
        return "puc_left_brace";
    case token_type::puc_right_brace:
        return "puc_right_brace";
    case token_type::puc_colon:
        return "puc_colon";
    case token_type::opt_plus:
        return "opt_plus";
    case token_type::opt_minus:
        return "opt_minus";
    case token_type::opt_star:
        return "opt_star";
    case token_type::opt_slash:
        return "opt_slash";
    case token_type::opt_equal:
        return "opt_equal";
    case token_type::lit_identifier:
        return "lit_identifier";
    case token_type::lit_int:
        return "lit_int       ";
    case token_type::lit_dec:
        return "lit_dec       ";
    case token_type::lit_string:
        return "lit_string    ";
    case token_type::key_var:
        return "key_var";
    case token_type::key_fun:
        return "key_fun";
    case token_type::ctr_error:
        return "ctr_error";
    default:
        return "ctr_unknow";
    }
}

} // namespace monoa
