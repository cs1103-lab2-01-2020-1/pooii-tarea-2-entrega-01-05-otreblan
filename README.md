# Programación Orientado a Objetos II
![C/C++ CI](https://github.com/cs1103-lab2-01-2020-1/pooii-tarea-2-entrega-01-05-otreblan/workflows/C/C++%20CI/badge.svg)

## Build
### Dependencias
- `Ubuntu >= 20.04`
- `CMake >= 3.13`
- `gcc >= 9`
- `git`

```bash
git clone https://github.com/cs1103-lab2-01-2020-1/pooii-tarea-2-entrega-01-05-otreblan
cd pooii-tarea-2-entrega-01-05-otreblan
mkdir build
cd build
cmake ..
make -j$(nproc)

./tarea-3 --help
```

## Tarea 3

1.- Implementar un sistema logístico en C++.

Solo considerar las diferentes clases y relaciones entre ellos.

* El sistema toma una orden y lo envia a una determinado destino.

* La orden es una lista de productos y hay un costo para procesar
cada orden.

* El usuario tiene que registrarse solo/sola en el sistema.

* El usuario puede trackear su orden.

* Las ordenes pueden ser enviadas por bicicleta o camion, pero
solamente una orden es enviada por un vehiculo.


Tener en cuenta:
*   Crear CMakeLists.txt
*   Crear Directorios src, build
*   Todas las clases involucradas en un sistema logístico mencionadas arriba.
*   Relaciones en clases: Herencia, Polimorfismo, Agregación, etc.

2.- Implementar una estructura de datos LIFO (Last In First Out) usando arrays.


3.- Crear dos arrays y convertilas en listas donde se pueda realizar
operaciones de merge, sorting, busqueda binaria, y obtener el lower bound del elemento mayor del array generado


4.- Crear una estructura generica template que soporte la estructura LIFO.
