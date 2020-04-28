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

#include <system.hpp>

#include <iostream>

aru::System::System(ArgParser& args):
	args(args)
{};

aru::System::~System(){};

bool aru::System::track(const std::string& user)
{
	return true;
}

bool aru::System::order(const std::string& user,
	const std::string& destination,
	const std::map<aru::productos, int>& order,
	const Vehicle vehicle)
{
	return true;
}

bool aru::System::list()
{
	return true;
}

bool aru::System::start()
{
	if(args.action.has_value())
	{
		switch (*args.action)
		{
			case Action::help:
				args.usage();
				break;
			case Action::track:
				if(args.user.has_value())
				{
					track(args.user.value());
				}
				else
				{
					std::cerr << "Usuario no especificado\n";
					exit(EXIT_FAILURE);
				}
				break;
			case Action::list:
				list();
				break;
			case Action::order:
				if(!args.user.has_value())
				{
					std::cerr << "Usuario no especificado\n";
					exit(EXIT_FAILURE);
				}
				if(!args.destination.has_value())
				{
					std::cerr << "Destino no especificado\n";
					exit(EXIT_FAILURE);
				}
				if(!args.vehicle.has_value())
				{
					std::cerr << "Vehículo no especificado\n";
					exit(EXIT_FAILURE);
				}
				if(args.order.size() == 0)
				{
					std::cerr << "La orden no puede estar vacía\n";
					exit(EXIT_FAILURE);
				}
				order(args.user.value(),
					args.destination.value(),
					args.order,
					args.vehicle.value());
				break;
		}
	}
	else
	{
		std::cerr << "Acción no especificada\n";
		exit(EXIT_FAILURE);
	}
	return true;
}
