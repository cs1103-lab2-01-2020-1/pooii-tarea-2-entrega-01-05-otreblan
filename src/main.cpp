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

#include <iostream>
#include <numeric>
#include <list>

#include <argParser.hpp>
#include <system.hpp>
#include <lifo.hpp>

int main(int argc, char* argv[])
{
	//aru::Lifo<int> st;
	//st.push(1);
	//st.push(2);
	//st.push(3);
	//st.push(2);
	//st.push(5);
//
	//std::cerr << st.top() << '\n';
	//st.pop();
	//std::cerr << st.top() << '\n';
	//st.pop();
	//std::cerr << st.top() << '\n';
	//st.pop();
	//std::cerr << st.top() << '\n';
	//st.pop();
	//std::cerr << st.top() << '\n';
	//st.pop();
//
	//return 0;
	// El lifo está en ../include/lifo.hpp

	const size_t size = 10;
	int arr1[size], arr2[size];

	std::iota(arr1, arr1+size, 0);
	std::iota(arr2, arr2+size, 0);

	// Ahora son listas
	std::list list1(arr1, arr1+size);
	std::list list2(arr2, arr2+size);


	aru::ArgParser parser;

	parser.parse(argc, argv);

	if(argc == 1)
	{
		parser.usage();
		return EXIT_FAILURE;
	}

	aru::System system(parser);

	system.start();

	return EXIT_SUCCESS;
}
