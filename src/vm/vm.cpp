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

#include <vm/opcode.hpp>
#include <vm/vm.hpp>

namespace monoa::vm {

vm::vm(std::vector<std::uint8_t> program) : program(program)
{
}

auto vm::run() -> int
{
    while (this->ip < program.size()) {
        switch (opcode(program[this->ip])) {
        case opcode::op_nop:
            this->advance();
            break;
        case opcode::op_push_8:
            this->advance();
            this->push(this->advance());
            break;
        case opcode::op_push_16:
            this->advance();
            this->push((this->advance() << 8) | this->advance());
            break;
        case opcode::op_push_32:
            this->advance();
            this->push((this->advance() << 24) | (this->advance() << 16) | (this->advance() << 8) | this->advance());
            break;
        case opcode::op_push_64:
            this->advance();
            this->push((this->advance() << 56) | (this->advance() << 48) | (this->advance() << 40) |
                       (this->advance() << 32) | (this->advance() << 24) | (this->advance() << 16) |
                       (this->advance() << 8) | this->advance());
            break;
        case opcode::op_ret:
            this->ip++;
            break;
        default:
            break;
        }
    }
    return pop();
}

auto vm::advance() -> uint64_t
{
    return this->program[this->ip++];
}

auto vm::push(uint64_t data) -> void
{
    this->stack.push_back(data);
}

auto vm::pop() -> uint64_t
{
    auto ret = this->stack.back();
    this->stack.pop_back();
    return ret;
}

} // namespace monoa::vm
