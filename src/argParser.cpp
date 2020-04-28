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
#include <products.hpp>

#include <string>
#include <iostream>

const std::vector<option> aru::ArgParser::options =
{
	{"help",    no_argument,       nullptr, 'h'},
	{"track",   no_argument,       nullptr, 't'},
	{"list",    no_argument,       nullptr, 'l'},
	{"destiny", required_argument, nullptr, 'd'},
	{"order",   required_argument, nullptr, 'o'},
	{"bicycle", no_argument,       nullptr, 'b'},
	{"truck",   no_argument,       nullptr, 'T'},
	{"user",    required_argument, nullptr, 'u'},

	{nullptr,   0,                 nullptr, 0}
};

void aru::ArgParser::usage()
{
	std::cout <<
		"Tarea 3\n"
		"Modo de uso: tarea-3 [OPCIONES]\n"
		"\t-h, --help                 Muestra esta ayuda\n"
		"\t-t, --track                Trackea las órdenes de un usuario\n"
		"\t-l, --list                 Muestra las órdenes\n"
		"\t-d, --destination=DESTINO  Destino de la orden\n"
		"\t-o, --order=LISTA          Lista de productos separada por comas\n"
		"\t-b, --bicycle              Usar la bicicleta como vehículo\n"
		"\t-T, --truck                Usar el camión como vehículo\n"
		"\t-u, --user=USUARIO         El usuario que envía la orden\n"
		"\n"
		"Lista de productos disponibles (En --order deben ir en minúsculas):\n"
		"\tPan\n"
		"\tCarne\n"
		"\n"
		"Ejemplo:\n"
		"\ttarea-3 -To pan,pan=100,carne=2 -u aru -d lima\n"
		"\n"
		"Una orden del usuario aru de panes y carnes enviada por camión hacia lima.\n"
		"La cantidad de productos se suma, por lo en este ejemplo la orden sería\n"
		"de 101 panes y 2 carnes.\n"
		"\n"
		"El LIFO está en include/lifo.hpp\n"
		"Las listas están en la línea 54 del main.cpp\n"
	;
}

aru::ArgParser::ArgParser(){};
aru::ArgParser::~ArgParser(){};

bool aru::ArgParser::parse(int argc, char* argv[])
{
	using aru::Products;

	// No errors from getopt
	opterr = 0;

	while(true)
	{
		int cc;
		int option_index;


		// Parsing
		cc = getopt_long(argc, argv, "htld:o:bTu:", options.data(), &option_index);

		// No quedan más opciones
		if(cc == -1)
			break;

		switch (cc)
		{
			case 'h':
				action = Action::help;
				break;
			case 't':
				action = Action::track;
				break;
			case 'l':
				action = Action::list;
				break;
			case 'd':
				destination.emplace(optarg);
				break;
			case 'o':
			{
				action = Action::order;
				char* optargarg;
				int cantidad = 0;
				Products prod;
				while(*optarg != '\0')
				{
					prod = (Products)getsubopt(&optarg, productVector, &optargarg);

					if((int)prod == -1)
					{
						std::cerr << "Producto inválido\n";
						exit(EXIT_FAILURE);
					}

					// Por default la cantidad es 1
					if(optargarg == NULL)
						cantidad = 1;
					else
						cantidad = atoi(optargarg);

					order[prod] += cantidad;

					// Sin órdenes vacías
					if(order[prod] == 0)
						order.erase(prod);
				}
				break;
			}
			case 'b':
				vehicle = Vehicle::bicycle;
				break;
			case 'T':
				vehicle = Vehicle::truck;
				break;
			case 'u':
				user.emplace(optarg);
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

	return true;
}
