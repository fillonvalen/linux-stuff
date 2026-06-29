##### ETAPAS
El proceso de la compilación consiste en **transformar** código de alto nivel (más entendible para el humano, como JavaScript, C++, HTML, Python, etc) a uno de bajo nivel (más entendible para una computadora, como lo es el lenguaje ensamblador o el binario), también llamado código máquina. El responsable de esto es un programa llamado ***compilador***.
El proceso en sí se divide en varias partes, pero vamos a ver estas 6:
1. Convierte el código en ***tokens***, siendo estos la unidad **más pequeña** en un lenguaje de programación (como *int* en C, u operadores, números, cadenas de texto, etc).
2. En esta etapa se encarga de **verificar** que el código sigue ciertas reglas gramaticales establecidas, o sea que la sintáxis sea correcta.
3. A continuación sigue el análisis semántico, en el cual se **verifica que el código tenga sentido**, porque por ejemplo si sumaramos una cadena de texto con un número, puede estar sintácticamente bien escrito pero eso no significa que sea una operación legal.
4. Acá se genera un **código intermediario**, o *IR* (Intermediate Representation), que vendría a ser un puente entre el código fuente y el máquina, con la diferencia que esta representación no está atada a ninguna máquina en específico. Esto se da para poder estructurar y simplificar el programa y así bajar los recursos que puede llegar a consumir.
5. El código intermediario es mejorado de vuelta.
6. En la etapa final es cuando el código intermediario se **transforma** en lenguaje ensamblador o máquina (binario).

##### MAKEFILES
A la hora de compilar un archivo, por ejemplo con código de C, utilizamos el comando `gcc`, pero ¿Qué pasaría si tuvieramos que compilar 70 archivos con un solo comando? Bueno, acá es cuando entran los *makefiles*, que son archivos usados junto al comando:
- `make` *options command*

para establecer cómo construir e instalar cierto software, teniendo una estructura con reglas que nos permite establecer los **prerequisitos**, **qué hay que construir**, y qué **comandos** usar para la construcción.

##### ESTRUCTURA
La forma en la que se establecen las reglas anteriormente mencionadas en un *archivo make* o *makefile* es la siguiente:
~~~
target: prerequisites
	command
	command
	...
~~~

Donde `target` es el archivo que queremos **construir**, `prerequisites` una lista de los archivos y/o *targets* necesarios para la construcción, y  `command` una serie de **comandos** de la shell a ejecutar, todos prefijados con una tabulación (no espacios, tabulación). También simplemente puede tratarse de una secuencia de comandos o un comando con opciones que queramos ejecutar, sin necesidad de añadir ningún prerequisito.


> [!important]
>Cabe mencionar que tanto en `target` como en  `prerequisites` puede haber un solo elemento o una lista de elementos separados por un espacio.
>También es importante saber que si un *target1* tiene como prerequisito a un *target2*, entonces primero va a dirigirse a ese *target2* antes de ejecutar sus respectivos comandos. En caso contrario, *target2* va a ser ignorado y solo va a poder ser ejecutado si lo aclaramos con el comando `make`.
###### Variables 
Las variables pueden resultar muy útiles al facilitarte la vida. Para definirlas se utiliza la sintáxis:
`VAR=value`
Y para referenciarla se escribiría `$(VAR)` o `${VAR}` (es lo mismo).
Las variables más comunes son:
* `CC`: el compilador, por ejemplo `gcc`.
* `CFLAGS`: opciones del compilador, como `-Wall -O2`[^1].
* `SOURCES`: lista de archivos que se van a usar en la compilación. Una manera diferente de usarlo, es darle por ejemplo el valor de `$(wildcard src/*.c)`, donde `wildcard` es una función que permite detectar todos aquellos archivos, en este caso ubicados en el directorio `src/`, que terminen en `.c`. Esta variable sirve para la que sigue en la lista.
* `OBJECTS`: si por ejemplo necesitamos en `prerequisites` una muy larga lista de archivos que terminen en `.o` que serían los mismos archivos terminados en `.c` pero compilados a medias. En ese caso, podemos darle un valor como `$(SOURCES:src/%.c=%.o)`, diciéndole básicamente que todos y cada uno de los archivos (`%`) en el directorio `src/` que terminan en `.c` y están presentes en la lista `SOURCES`, cambie la extensión por `.o`.
###### Reglas de patrones
También existen ciertas "variables predefinidas" que se usan en la/s sección/es `command`, que **generalizan** los archivos que cumplen cierto patrón establecido en la parte `target` y en `prerequisites` con la ayuda de `%`, que ya lo vimos anteriormente:
* `$@`: se refiere al nombre del `target`.
* `$<`: hace referencia al primer requisito.
* `$^`: significa "todos los prerequisitos"
###### Ejemplo
Con toda la información anterior, un ejemplo de *makefile* sería el siguiente:
~~~
CC = gcc
CFLAGS = -Wall -O2
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:src/%.c=%.o)
all: program
program: $(OBJECTS)
	$(CC) %(CFLAGS) $^ -o program
%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f hello *.o
~~~

Si quisieramos que solo ejecute un *target* en específico, habría que utilizar el comando `make` seguido del `target`, como por ejemplo `make clean`.

###### Condicionales
En un archivo make podemos insertar diferentes tipos de condicionales:
* `ifeq (variable,value)` se utiliza para comparar si una variable cualquiera es igual al valor aclarado.
* `ifneq (variable,value)` es lo contrario a `ifeq`, retornando verdadero si la variable **no** es igual al valor escrito.
* `ifdef variable` devuelve verdadero si la variable está definida.
* `ifndef variable` da como valor verdadero si la variable **no** está definida.
Siguiendo con el ejemplo anterior del *makefile*, antes de definir los *targets* podríamos agregar:
~~~
ifdef DEBUG
	CFLAGS += -g
endif
~~~

> [!warning]
> La instrucción `endif` es obligatoria, aunque también puede ir un `else`, pero de todos modos habría que añadir `endif`al final.

> [!note]
>El `+=` es para agregar, no para sobreescribir, como `=`.

###### Comandos de shell
En un archivo make, podemose escribir el comando de nuestra shell que queramos, pero hay que tener en cuenta una cosa: mientras se ejecuten las instrucciones, cuando encuentre un comando de la shell, primero va a imprimir el comando en sí y luego el resultado. Para que solo muestre la salida, antes del comando hay que agregar `@`.

###### Order-only prerequisites
Así se les conoce en inglés a ciertos prerequisitos que van seguidos de `|`, quedando la estructura:
`target: prerequisites | order-only prerequisites`
Estos se usan en caso de que el prerequisito tenga que estar presente, pero cuyo contenido no afecta al *target* a producir. Por ejemplo, tenemos lo siguiente:
~~~
bin/game: bin
	...
bin:
	mkdir $@
~~~

donde, en caso de no existir el directorio `bin/`, entonces *make* va a dirigirse al *target* con el mismo nombre el cual lo crea. Si empleamos el comando `make`, todo va a ir viento en popa, y si lo ejecutamos nuevamente, no va a pasar nada porque ya está todo armado. El problema es que si en esta segunda vez, la fecha de modificación de `bin` es más nueva, ya sea porque se haya añadido, eliminado o modificado algún archivo dentro, *make* va a reconstruir el target `bin/game` lo cual es innecesario. En el caso de querer evitar eso, habría que convertir `bin` en un *order-only prerequisite*:
~~~
bin/game: | bin
	...
~~~
Una forma simple de verlo es que un *order-only prerequisite* es como un prerequisito que dice: "crea esto si no existe pero no toques el *target*", mientras que los prerequisitos a la izquierda de `|` sí van a tenerse en cuenta si fueron modificados, que en caso de que así sea, el *target* va a ser reconstruido.
###### Complejizando la estructura
Por lo general, para mayor organización, en un proyecto que involucre un *makefile*, hay tres directorios presentes: `src/`, `obj/` y `bin/`, estas dos últimas siendo creadas por el mismo archivo make. 
En `src/` van a estar los archivos que se van a compilar, en `obj/` los archivos a medio compilar (`.o`), y en `bin/` el o los archivos ejecutables.
Entonces, antes de `SOURCES` y `OBJECTS` podemos agregar tres variables en nuestro ejemplo:
```
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = obj
```

y ahora  vamos a modificar estas variables:
```
SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
```

y vamos a agregar:
`TARGET=$(BIN_DIR)/program`

también hay que añadir un `target` al final de todo para que cree los directorios necesarios:
```
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@
```

A través de las modificaciones necesarias, nuestro *Makefile* quedaría así:
```
CC = gcc
CFLAGS = -Wall -O2
BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/program
ifdef DEBUG
	CFLAGS += -g
endif

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $(TARGET) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@echo "Cleaning up build artifacts..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)
```

###### Targets .PHONY
Estos targets van a contener nombres de otros targets que no sean archivos, como por ejemplo `install` o `clean` o `test`, en caso de que existan archivos con el mismo nombre, y así evitar conflictos.
Se declaran de la siguiente manera en el comienzo del *Makefile*:
`.PHONY: all clean`

###### Target `all`
Este target es muy común en archivos *make*, ya que siempre el primer target es el predeterminado. En el target `all` se especifican el o los binarios que se esperan que sean construidos por el *Makefile*. No es necesario cuando hay un solo binario, pero aún así es una buena práctica.

##### CONFIGURE
Un *Makefile* hecho a mano resulta más que suficiente con proyectos pequeños, pero cuando se trata de algo más grande, hacer esto puede requerir mucho tiempo y energía valiosos. A la hora de compilar, probablemente se necesite tener instalado uno o más paquetes para que la instalación sea posible, y ahí es cuando entra en juego el archivo `./configure`. No solo hace eso, si no que también puede permitir al usuario cambiar ciertas configuraciones, como el tipo de instalación, la locación de las librerías o algunas funciones que se nos permita quitar o añadir. Otra función es la de generar un *Makefile* por nosotros una vez las dependencias estén listas. Y por último pero no menos importante, se encarga de correr algunas pruebas y así asegurar que el sistema sea compatible con el software que se está instalando.
Como se puede ver, es un archivo muy importante.

> [!Important]
> Siempre se va a utilizar `./configure` sobre todo para automatizar la creación del *Makefile*, debido a que si se creara manualmente, el software solo sería compatible con el sistema del que lo crea, y el que lo instale tendría que cambiar la configuración para evitar errores. `./configure` lo hace automáticamente por el usuario, permitiendo ahorrar tiempo y posibles dolores de cabeza.

El proceso de la generación de un archivo `./configure`, que por cierto es un conjunto inmenso de instrucciones para bash, tomaría un tiempo inhumano hacerlo a mano, por eso acá es cuando entran las herramientas automáticas de Unix, o *Unix autotools*, y en este caso vamos a necesitar tres paquetes que hay que instalar: `autoconf`, `automake` y `libtool`, que tienen varias herramientas. He aquí una forma simple de ver cómo funciona:
![[autotools_inwork.drawio.png]]
###### configure.ac
Para empezar, luego de haber instalado las herramientas necesarias, es crear un archivo de nombre `configure.ac`, en el cual vamos a añadir las siguientes líneas:
`AC_INIT([myprogram], [0.1], [my_mail@mail.com])`: esta función (macro) inicializa `autoconf` y configura información básica del programa a construir, como en este caso el nombre del programa, la versión, y el correo del que esté a cargo del proyecto.

`AM_INIT_AUTOMAKE`: es necesario para inicializar `automake`.

`AC_PROG_CC`: después de lo anterior, hay que decirle las dependencias que queremos que `configure` busque. En este caso se añade solo eso al ser el compilador de C (`cc`, sí, otro compilador aparte de `gcc`) el único requisito. Si hubiera más, podemos usar otro macro como `AC_PATH_PROG([variable],[program])`, que busca el programa `program` en la variable `PATH` del usuario, para después guardar la ruta absoluta hasta ese programa en la variable del nombre que sea.

`AC_CONFIG_FILES([Makefile])`: con esto le decimos que el archivo `configure` se encargue sola y exclusivamente de encontrar un archivo de nombre `Makefile.in`, sustituir ciertos nombres reservados con los valores aclarados (como la versión del programa, por ejemplo), y que el contenido resultante vaya a `Makefile`.

`AC_OUTPUT`: esto le dice a `autoconf` que muestre la salida del *script*.

###### Makefile.am
Como se mencionó anteriormente, `configure` va a esperar un archivo `Makefile.in`. El problema es que la creación manual de dicho archivo es compleja y larga, por ende se utiliza un archivo `Makefile.am` que más tarde `automake` va a convertirlo en un `Makefile.in` por nosotros.
En el archivo vamos a añadir estas líneas:

`AUTOMAKE_OPTIONS = foreign`: resulta que la estructura estándar de los proyectos GNU consta de varios archivos:
 * `README`
 * `NEWS`
 * `AUTHORS`
 * `ChangeLog`
 * `COPYING
 pero si no se trata de un proyecto muy grande, estos archivos no son muy necesarios. Por eso, si no seguimos esta estructura, hay que usar la opción `foreign`.
 
`bin_PROGRAMS = myprogram`: el sufijo ocupado por `PROGRAMS` aclara las propiedades del archivo especificado, en este caso diciendole a `automake` que el archivo necesita ser creado. Mientras que si el archivo ya existe, entonces se emplean sufijos como `SCRIPTS`o `DATA`.
El prefijo `bin` le dice a `automake` que el archivo debe ser instalado en una variable predefinida llamada `bindir`, de valor `$(prefix)/bin`, donde `prefix = /usr/local`. Este último valor puede ser modificado más tarde cuando ejecutemos `configure`, seguido de la opción `--prefix=` y la ruta que queramos.
Existen varias variables de directorios predefinidas, pero también podemos crear las nuestras. Por ejemplo si quisieramos instalar ciertos archivos con código de Go como parte de nuestro programa, habría que añadir algo así:
~~~
godir = $(datadir)/go
go_DATA = script1.go script2.go
~~~

donde `$(datadir)` tiene un valor de `$(prefix)/share`. 

`myprogram_SOURCES = main.c`: aquí se aclaran el o los archivos con el código fuente.

`aclocal`
`autoconf`: va a crear el archivo `configure` a partir de `configure.ac`.
`automake --add-missing`: crea el archivo `Makefile.in`, y añade archivos faltantes para la construcción gracias a la opción `--add-missing`.

> [!tip] 
>  Se puede crear automáticamente un archivo llamado `configure.scan` usando el comando `autoscan` (sin parámetros) que vendría a ser lo mismo que `configure.ac` pero ya estructurizado dándote mejor idea de cómo funciona (Sí, habría que cambiarle el nombre el archivo al crearlo).

A partir de este punto ya tenemos nuestro proyecto armado, pudiendo borrar `Makefile.am` y `configure.ac`, que resultan intrascendentales.

##### CMAKE
Así como *make* resulta ser un sistema de compilación, *CMake* es un sistema para crear sistemas de compilación. Y sí, hay más de uno, como *Ninja*, diseñado como reemplazo o alternativa de *make*. 
###### Primer paso
La creación de un archivo *CMake* es simple. Primero hay que crear, en el directorio con nuestro código fuente, un archivo de nombre `CMakeLists.txt`, con el siguiente contenido:
~~~
cmake_minimum_required(VERSION 3.10)
project(fsoc)
add_executable(fsoc fsoc.c)
~~~

Esta es la forma más simple de un proyecto con *CMake*.
> El usuario, al instalar el código fuente, deberá crear en el mismo directorio, otro directorio llamado `build/`, para entrar a ese directorio y ejecutar el comando `cmake ..`, pero aún así todo lo generado se queda en `build/`.
###### Segundo paso
Lo más normal es que tengamos varios archivos con código, y en ese caso habría que ponerlos como una lista separada por espacios dentro de `add_executable()`, pero también puede darse que sean demasiados y se haga tedioso tener que copiar los archivos uno por uno.


[^1]: Tanto `-Wall` como `-O2` son opciones que activan otras opciones (demasiadas como para mencionarlas)  que permite que el compilador no solo muestre errores sino diferentes tipos de advertencias que no joden la salida del código pero sí su rendimiento. Echarle un vistazo al manual de `gcc`.

