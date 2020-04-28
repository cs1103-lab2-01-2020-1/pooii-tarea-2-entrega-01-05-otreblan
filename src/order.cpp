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

#include <order.hpp>
#include <products.hpp>

#include <iostream>
#include <sstream>

std::ostream& aru::operator <<(std::ostream& os, const aru::Order& order)
{
	os
		<< order.time << '\t'
		<< order.user << '\t'
		<< order.destination << '\t'
		<< (int)order.vehicle << '\t'
	;

	for(auto i = order.products.begin(); i != order.products.end(); i++)
	{
		os << (int)i->first << '=' << i->second << '\t';
	}

	return os << "0=0" <<"\t\n";
}

std::istream& aru::operator >>(std::istream& is, Order& order)
{
	std::string buf;

	int vehicle;
	is
		>> order.time
		>> order.user
		>> order.destination
		>> vehicle
	;
	order.vehicle = (Vehicle)vehicle;

	int n1;
	int n2;

	while(std::getline(is, buf, '\t'))
	{
		if(buf.size() == 0)
			continue;

		sscanf(buf.data(), "%d=%d", &n1, &n2);
		if(n1 == 0 && n2 == 0)
		{
			break;
		}

		order.products[(Products)n1] = n2;
	}


	return is;
}

bool aru::Order::fancy_print(std::ostream& os)
{
	os
		<< '\t'
		<< "\033[1;33m"
		<< "Tiempo: "
		<< "\033[0m"
		<< ctime(&time)

		<< '\t'
		<< "\033[1;33m"
		<< "Usuario: "
		<< "\033[0m"
		<< user
		<< '\n'

		<< '\t'
		<< "\033[1;33m"
		<< "Destino: "
		<< "\033[0m"
		<< destination
		<< '\n'

		<< '\t'
		<< "\033[1;33m"
		<< "Productos: "
		<< "\033[0m"
		<< '\n'
	;

	for(const auto& [product, Q]: products)
	{
		std::string product_name = productVector[(int)product];
		product_name.data()[0] = toupper(product_name.data()[0]);

		os
			<< "\t\t"
			<< "\033[1;31m"
			<< product_name << ": "
			<< "\033[0m"
			<< Q
			<< '\n'
		;
	}

	os << '\n';

	return true;
}
