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
#include <iostream>
#include <memory>
#include <ast/printer.hpp>
#include <parser/lexer.hpp>
#include <parser/parser.hpp>

auto main(int argc, char* argv[]) -> int
{
    auto source = R"(
fun main() -> int
{
    let x = 1;
    return 1;
}

)";
    auto lexer = std::make_unique<monoa::parser::lexer>(source);
    lexer->print_tokens();
    auto parser = std::make_unique<monoa::parser::parser>(lexer->get_tokens());
    if (!parser->error().has_value()) {
        std::cout << std::endl;
        auto printer = std::make_unique<monoa::ast::printer>();
        printer->visit(parser->ast());
    } else {
        std::cerr << "parsing error : " << parser->error().value();
    }

    return EXIT_SUCCESS;
}
