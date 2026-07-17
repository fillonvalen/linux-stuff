Así como *make* resulta ser un sistema de compilación, *CMake* es un sistema para crear sistemas de compilación, conviertiéndose en una herramienta muy útil al adaptarse a las características de cualquier sistema. Y sí, hay más de un sistema de compilación, como por ejemplo *Ninja*, diseñado como reemplazo o alternativa de *make*. 
##### Ejemplo básico
La creación de un archivo *CMake* es simple. Primero hay que crear, en el directorio con nuestro código fuente, un archivo de nombre `CMakeLists.txt`, con el siguiente contenido:
~~~
cmake_minimum_required(VERSION 3.10)
project(fsoc)
add_executable(fsoc)
target_sources(fsoc
	PRIVATE
		fsoc.c
)
~~~

> El usuario, al instalar el código fuente, deberá crear en el mismo directorio, otro directorio llamado `build/`, y ejecutar `cmake -B build`, diciéndole que todos los archivos generados durante la compilación se dirigan al directorio `build`.
###### Explicación detallada
`cmake_minimum_required(VERSION 3.28)`: asegura que *CMake* tenga el comportamiento de la versión escrita, más allá de  si la versión del programa en el sistema es más nueva o no.
`project(fsoc)`: esta es una función compleja, pero por ahora nos quedamos con que toma el nombre de nuestro proyecto.
`add_executable(fsoc)`: este comando crea un *target* con el nombre que queramos, en este caso el ejecutable `fsoc`. 
`target_sources(fsoc PRIVATE fsoc.c)`: este comando toma como primer argumento el nombre del *target* seguido de uno o más archivos con código fuente. Antes de cada lista de archivos va a haber un *scope keyword*, que determinan la disponibilidad de las propiedades para los diferentes *targets*, y en total hay tres: `PRIVATE`, `PUBLIC` y `INTERFACE`. La manera más simple de entender estos, desde el punto de vista del *target*, es así: 
`PRIVATE` es solo para mí, `INTERFACE` es para los otros, y `PUBLIC`, es para todos nosotros.

##### Librerías
~~~
add_library(mylib)
target_sources(mylib,
	PRIVATE
		mylib.c
		
	PUBLIC
		FILE_SET my_headers
		TYPE HEADERS 
		BASE_DIRS
			include
		FILES
			include/lib_header.h
)
~~~

En este caso, queremos tener una colección de archivos *header* (`.h`) en una librería que creamos con el comando `add_library()`, que es lo mismo que `add_executable()` pero para librerías. Para describir esta colección de archivos de encabezado (*header* = encabezado) vamos a usar un `FILE_SET`, seguido del nombre que querramos ponerle. Luego se divide en estas partes:
+ `TYPE`: delante va a ir el tipo de archivos que estamos describiendo, en este caso `HEADERS`. Si el nombre de `FILE_SET` fuera el mismo que `TYPE`, entonces esta opción se puede pasar por alto. **PRESCINDIBLE**. 
+ `BASE_DIRS`: es el o los directorios “principales” que serán descritos al compilador para que pueda encontrar los *headers*. Si no se aclara ningún valor, toma de manera predeterminada el directorio del proyecto. **PRESCINDIBLE**.
+ `FILES`: aquí se encuentra la lista de los archivos. **IMPRESCINDIBLE**.

Entonces, un ejemplo de esto usando los tres *scope keywords* luciría así:
~~~
target_sources(mylib,
	PRIVATE
		FILE_SET internal_only_headers
		TYPE HEADERS
		FILES
			internal_only.h
	INTERFACE
		FILE_SET consumer_only_headers
		TYPE HEADERS
		FILES
			consumer_only.h
	PUBLIC
		FILE_SET public_headers
		TYPE HEADERS
		FILES
			public.h
)
~~~

##### Conectando librerías y ejecutables
Ya tenemos el ejecutable y la librería listas. Para enlazar ambas cosas simplemente debemos hacerlo con el comando `target_link_libraries()`:
`target_link_libraries(fsoc PRIVATE mylib)`
##### Subdirectorios
Con lo anterior es más que suficiente como para un proyecto pequeño, pero si se trata de algo grande, vamos a querer dividir el proyecto en partes para que no se vuelta todo un nudo gigante que no vamos a saber cómo desatarlo o vamos a tardar en hacerlo a través del estrés.
Un ejemplo básico. Hagamos de cuenta que en el directorio de nuestro proyecto tenemos dos subdirectorios: `math_functions` y `fsoc`, cada uno con un archivo `CMakeLists.txt`.

**fsoc/CMakeLists.txt**
~~~
add_executable(fsoc)
target_sources(fsoc PRIVATE fsoc.c)
target_link_libraries(fsoc PRIVATE math_functions)
~~~

**math_functions/CMakeLists.txt**
~~~
add_library(math_functions)
target_sources(math_functions
	PRIVATE
		math_fun.c
	PUBLIC
		FILE_SET HEADERS
		FILES
			math_fun.h
)
~~~

Entonces en el directorio principal del proyecto, habría que crear un `CMakeLists.txt` con el siguiente contenido:
~~~
add_subdirectory(fsoc)
add_subdirectory(math_functions)
~~~

##### Más avanzado
https://cmake.org/cmake/help/latest/guide/tutorial/index.html


