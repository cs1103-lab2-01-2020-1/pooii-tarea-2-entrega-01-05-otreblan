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

#pragma once

#include <products.hpp>

#include <getopt.h>
#include <vector>
#include <optional>
#include <map>

namespace aru
{

// Lista de las posibles acciones
enum class Action
{
	help,
	track,
	list,
	order
};

// Posibles vehículos
enum class Vehicle
{
	bicycle,
	truck
};

class ArgParser
{
private:
	static const std::vector<option> options;

public:
	ArgParser();
	virtual ~ArgParser();

	void usage();
	bool parse(int argc, char* argv[]);

	// Destino de la orden
	std::optional<std::string> destination;

	// Cantidad de productos en la orden
	std::map<aru::productos, int> order;

	// El vehículo en el que se llevará la orden
	std::optional<Vehicle> vehicle;

	// La acción que ejecutará el programa
	std::optional<Action> action;

	// El usuario
	std::optional<std::string> user;
};

}
