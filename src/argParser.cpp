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

const std::vector<option> aru::ArgParser::options =
{
	{"help", no_argument, nullptr, 'h'},
	{nullptr, 0, nullptr, 0}
};

void aru::ArgParser::usage()
{
	std::cout <<
		"Tarea 3\n"
		"Modo de uso: tarea-3 [OPCIONES]\n"
		"\t-h, --help      Muestra esta ayuda\n"
	;
}

aru::ArgParser::ArgParser(){};

aru::ArgParser::~ArgParser(){};

bool aru::ArgParser::parse(int argc, char* argv[])
{
	// No errors from getopt
	opterr = 0;

	while(true)
	{
		int cc;
		int option_index;

		// Parsing
		cc = getopt_long(argc, argv, "h", options.data(), &option_index);

		if(cc == -1)
			break;

		switch (cc) {
			case 'h':
				usage();
				break;
			case '?':
				std::cerr << "no\n";
				exit(EXIT_FAILURE);
				break;
		}
	}

	while(optind < argc)
	{
		std::cerr << argv[optind++] << '\n';
	}

	//int i = '?';
	//std::cerr << i;

	return true;
}
