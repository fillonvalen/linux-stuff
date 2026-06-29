Así como *make* resulta ser un sistema de compilación, *CMake* es un sistema para crear sistemas de compilación. Y sí, hay más de uno, como *Ninja*, diseñado como reemplazo o alternativa de *make*. 
##### Ejemplo básico
La creación de un archivo *CMake* es simple. Primero hay que crear, en el directorio con nuestro código fuente, un archivo de nombre `CMakeLists.txt`, con el siguiente contenido:
~~~
cmake_minimum_required(VERSION 3.10)
project(fsoc)
add_executable(fsoc)
target_sources(fsoc fsoc.c)
~~~
> El usuario, al instalar el código fuente, deberá crear en el mismo directorio, otro directorio llamado `build/`, para entrar a ese directorio y ejecutar el comando `cmake ..`, pero aún así todo lo generado se queda en `build/`.
###### Explicación detallada
`cmake_minimum_required(VERSION 3.28)`:  