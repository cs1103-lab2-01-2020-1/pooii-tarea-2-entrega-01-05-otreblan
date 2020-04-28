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

#include <string.h>

namespace aru
{

template <typename T>
class Lifo
{
private:
	T* data;
	size_t size;
	size_t capacity;
public:
	Lifo():
		data(new T[1]),
		size(0),
		capacity(1)
	{};

	virtual ~Lifo()
	{
		delete[] data;
	};

	void push(const T& value)
	{
		if(size == capacity)
		{
			T* new_data = new T[capacity*=2];

			mempcpy(new_data, data, sizeof(T)*size);
			delete[] data;

			data = new_data;
		}

		data[size++] = value;
	}

	void pop()
	{
		if(size != 0)
			size--;
	}

	T& top()
	{
		return data[size-1];
	}
};
}
