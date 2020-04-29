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
#include <order.hpp>

#include <filesystem>
#include <deque>
#include <sys/ioctl.h>

namespace aru
{

namespace fs = std::filesystem;


class System
{
private:

	// Es true cuando SIGINT es recibido
	static bool sigint;

	// Argumentos recibidos por tarea-3
	ArgParser& args;

	fs::path cache_dir;
	fs::path bicycle;
	fs::path truck;

	// Las dimensiones de la terminal
	static winsize size;
	static void update_size(int sig = 0);

	bool track(const std::string& user);
	std::deque<Order> parse_list(fs::path vehicle);
	bool recalculate_orders(std::deque<Order>& orders, Vehicle vehicle);
	bool re_order(const std::deque<Order>& orders, Vehicle vehicle);

	bool order(const std::string& user,
		const std::string& destination,
		const Vehicle vehicle,
		const std::map<aru::Products, int>& order);

	bool list();
	bool list_print(std::ifstream& os, const std::string& vehicle);

public:
	// Tiempo que demora la bicicleta en completar una orden
	static const time_t bicycle_time;

	// Tiempo que demora el camión en completar una orden
	static const time_t truck_time;

	System(ArgParser& args);
	virtual ~System();

	bool start();
};

}
