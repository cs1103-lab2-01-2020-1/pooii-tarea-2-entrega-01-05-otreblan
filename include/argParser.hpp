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

#include <getopt.h>
#include <vector>

#include <optional>

namespace aru
{

class ArgParser
{
private:
	static const std::vector<option> options;

public:
	ArgParser();
	virtual ~ArgParser();

	void usage();
	bool parse(int argc, char* argv[]);

	// Muestra la ayuda
	bool help = false;

	// Trackea una orden
	std::optional<std::string> track;

	// Muestra las órdenes
	bool _list = false;

	// Destino de la orden
	std::optional<std::string> destination;
};

}
