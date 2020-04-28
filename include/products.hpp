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

namespace aru
{

// Lista de productos
enum class productos
{
	pan = 0,
	carne
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc99-designator"
#pragma GCC diagnostic ignored "-Wunused-variable"

static char* const productVector[] =
{
	[(int)productos::pan] = (char*)"pan",
	[(int)productos::carne] = (char*)"carne",
	0
};

#pragma GCC diagnostic pop
}
