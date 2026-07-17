##### ¿Qué es eso?
Las librerías son muy importantes ya que son pedazos de código con funciones, rutinas, estructuras de datos, y demás, que pueden ser reutilizados en otros programas, facilitándoles la vida a los programadores.

##### Librerías estáticas
Cuando convertimos un programa en un ejecutable, si se emplea una de estas, la misma se copiará al  programa, solo tomando las funciones necesarias. Esto quiere decir que por más que eliminemos la librería, el programa va a seguir funcionando correctamente al tenerla ya incorporada. Estas tienen el formato `.a`.

##### Librerías dinámicas
En cambio, aquí no se copian, si no que el programa, cuando la necesite, buscará la función en la librería, pero sin copiarla, haciendo el programa completamente dependiente de que esté la librería. Con estas se emplea el formato `.so`.

##### Comandos relacionados
- `ldd` *executable*: muestra las librerías que utiliza el programa *executable* (un binario, como `/usr/bin/ls`).
- `ldconfig` *option*: al instalar una librería manualmente, el sistema no lo va a detectar como tal, y ahí es cuando entra este comando, que, de manera resumida, ayuda al sistema a que sepa dónde están las librerías dinámicas (`.so`) y qué versiones usar, usando enlaces simbólicos (o *symlinks*),
¿Por qué enlaces simbólicos?, porque por lo general, las librerías tienen un nombre con versión, por ejemplo `libx.so.1.7.2`, pero los programas buscan algo más genérico, como `libx.so.1`, o incluso `libx.so`, así que cuando se instala o actualiza una librería, `ldconfig` creará el/los enlace/s simbólico/s:

`libx.so` → `libx.so.1` → `libx.so.1.7.2`

Otra explicación más detallada: busca en los directorios hecho para las librerías compartidas (como `/usr/lib/`) y en los directorios escritos en el archivo `ld.so.conf` ubicado en el directorio `/etc`, actualiza la caché de librerías dinámicas en el archivo `ld.so.cache` también ubicado en `/etc`, guardando todo, y crea o actualiza los enlaces simbólicos para que las versiones de las librerías usadas sean las correctas.