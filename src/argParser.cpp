// Tarea 3
// Copyright © 2020 otreblan
//
// tarea-3 is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// tarea-3 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with tarea-3.  If not, see <http://www.gnu.org/licenses/>.

#include <argParser.hpp>
#include <string>
#include <iostream>

void aru::ArgParser::usage()
{
	std::cout
		<< "Tarea 3\n"
		<< "Modo de uso: tarea-3 [OPCIONES]\n"
		<< "--help      Muestra esta ayuda\n"
		;
}

aru::ArgParser::ArgParser(){};

aru::ArgParser::~ArgParser(){};

bool aru::ArgParser::parse(int argc, char* argv[])
{
	using namespace std::literals;

	if("--help"s == argv[argc-1])
	{
		usage();
	}
	return true;
}
