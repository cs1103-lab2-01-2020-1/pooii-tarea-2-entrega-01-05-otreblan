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

bool aru::System::
	order(const std::string& user, const std::map<aru::productos, int>& order)
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
				break;
			case Action::list:
				break;
			case Action::order:
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
