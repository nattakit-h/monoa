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

#include <cstdlib>
#include <memory>
#include <iostream>
#include <parser.hpp>
#include <lexer.hpp>
#include <ast/printer.hpp>

auto main(int argc, char* argv[]) -> int
{
    auto lexer = std::make_unique<monoa::lexer>("let _x123 = 1;");
    lexer->print_tokens();
    auto parser = std::make_unique<monoa::parser>(lexer->get_tokens());
    auto printer = std::make_unique<monoa::ast::printer>();
    printer->visit(parser->ast());
    return EXIT_SUCCESS;
}
