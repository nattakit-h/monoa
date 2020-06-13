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

#include <iostream>
#include <memory>
#include <ast/compiler.hpp>
#include <ast/printer.hpp>
#include <parser/lexer.hpp>
#include <parser/parser.hpp>

using namespace monoa;

auto main(int argc, char* argv[]) -> int
{
    auto source = R"(
fun main() -> i64
{
    let a = 10;
    return 74 - 10 + 44 * 99 - 346 / 2;
}

fun pow() -> i64
{
    return 10;
}

)";
    auto lexer = std::make_unique<parser::lexer>(source);
    if (lexer->error().has_value()) {
        std::cerr << "lexing error : " << lexer->error().value();
        return EXIT_FAILURE;
    }

    auto parser = std::make_unique<parser::parser>(lexer->get_tokens());
    if (parser->error().has_value()) {
        std::cerr << "parsing error : " << parser->error().value();
        return EXIT_FAILURE;
    }

    auto compiler = std::make_unique<ast::compiler>(parser->ast());
    if (compiler->error().has_value()) {
        std::cerr << "compiling error : " << compiler->error().value();
        return EXIT_FAILURE;
    }

    std::cout << compiler->result();
    return EXIT_SUCCESS;
}
