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

#include <argParser.hpp>

#include <optional>
#include <iostream>
#include <sys/ioctl.h>

namespace aru
{

struct Order;

std::ostream& operator <<(std::ostream& os, const Order& order);
std::istream& operator >>(std::istream& is, Order& order);


struct Order
{
	time_t time;
	std::optional<time_t> exit_time;
	std::string user;
	std::string destination;
	Vehicle vehicle;
	std::map<aru::Products, int> products;

	friend std::ostream& operator <<(std::ostream& os, const Order& order);
	friend std::istream& operator >>(std::istream& is, Order& order);

	bool fancy_print(std::ostream& os) const;

	/// Loading bar
	bool bar_print(std::ostream& os, winsize size, int index);
};

}
