##### Ínodos
Antes de saber sobre los enlaces, hay que conocer a los ínodos (*inode*) o índices de nodos (*index node*), que vendrían a ser una “caja” que almacena todos los metadatos de un archivo, a excepción del nombre del mismo y la información que contiene.
Un ínodo contiene datos como:
* El tamaño del archivo.
* Las IDs del usuario dueño (*UID*) y del grupo dueño (*GID*) del archivo.
* Permisos.
* El dispositivo de almcenamiento en el que se encuentra.
* Los bloques de almacenamiento (la información en el disco es guardada en forma de bloques, todos con un tamaño arreglado, como 512 bytes) en los que se pueden encontrar la data del archivo.

En el sistema, el número de ínodos es estático, esto significa que si uno tiene los suficientes archivos, puede quedarse sin ínodos sin haber ocupado todo el espacio del disco, provocando fallos en el mismo, obligando a uno a reconstruir el sistema de archivos para poner un límite de ínodos más grande. Cosa rara pero cierta.
Si quisieramos ver cuántos ínodos está utilizando nuestro sistema de archivos, podemos usar el comando `df` (más adelante este comando se usa con más profundidad) junto a la opción `-i`.
También se puede usar `ls -i` para mostrar el número de ínodo de cada archivos.

##### Ahora sí, enlaces duros
Un archivo en un sistema de archivos es básicamente un enlace a un ínodo, y de esa manera, un enlace duro (*hard link*) es otro archivo que apunta a exactamente el mismo ínodo.

##### Enlaces simbólicos
En cambio, este tipo de enlace (*soft / symbolic link*) es un archivo especial que apunta a otro archivo estándar que existe en otro lado del sistema. Dicho de otra manera, un enlace simbólico apunta un nombre de archivo a otro, que a su vez apunta a información en cierto dispositivo. Como los accesos directos de Windows.

##### Comando
Pero claro, ¿Cómo los creamos?
- `ln` *options target file link file*: con este, sin opciones, creamos el enlace duro de un archivo. Podemos darnos cuenta de que tanto *target file* como *linked file* apuntan al mismo ínodo usando `ls -i`.
	+ `-s`: esta opción crea el *symbolic link* de un archivo, y tales los podemos apreciar con el comando `ls -l`.





