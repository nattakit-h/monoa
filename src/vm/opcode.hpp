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

#ifndef MONOA_VM_OPCODE_HPP
#define MONOA_VM_OPCODE_HPP

#include <cstdint>

namespace monoa::vm {

enum class opcode : std::uint8_t
{
    op_nop,
    op_push_8,
    op_push_16,
    op_push_32,
    op_push_64,
    op_add_8,
    op_add_16,
    op_add_32,
    op_add_64,
    op_sub_8,
    op_sub_16,
    op_sub_32,
    op_sub_64,
    op_mul_8,
    op_mul_16,
    op_mul_32,
    op_mul_64,
    op_div_8,
    op_div_16,
    op_div_32,
    op_div_64,
    op_ret,
};

}

#endif // MONOA_VM_OPCODE_HPP
