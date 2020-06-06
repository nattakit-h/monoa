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

#ifndef MONOA_VM_VM_HPP
#define MONOA_VM_VM_HPP

#include <cstdint>
#include <memory>
#include <vector>

namespace monoa::vm {

class vm
{
public:
    vm(std::vector<std::uint8_t> program);
    auto run() -> int;

private:
    std::uint64_t ip = 0;
    std::vector<std::uint8_t> program;
    std::vector<uint64_t> stack;

    auto advance() -> uint64_t;
    auto push(uint64_t data) -> void;
    auto pop() -> uint64_t;
};

} // namespace monoa::vm

#endif // MONOA_VM_VM_HPP
