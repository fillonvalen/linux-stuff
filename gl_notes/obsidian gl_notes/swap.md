Revisar [[mountpoints_part#^a6de26]].

>[!Note]
>Sí, la memoria swap puede ser tanto borrada como restaurada, ya que no deja de ser igual a una partición cualquiera.

- `free`: con este comando podemos revisar si existe una memoria swap presente en el sistema, ya que en caso de no haber, todos los valores de swap estarían en 0.
	-  `-h`: muestra los tamaños de la memoria principal y swap de una forma más legible. 
- `swapon` *file*: activa una partición o archivo swap
	- `-a`: activa todas las particiones/archivos swap presentes en `/etc/fstab`.
	- `--show`: muestra las particiones o archivos swap activados en el sistema.
- `swapoff` *file*: igual que el comando anterior, pero en vez de activar, desactiva. 

##### archivo swap
Si el sistema cuenta con la memoria swap en una partición, o simplemente el sistema ya contaba con la memoria swap en un archivo y se quiere restaurar, esta es una guía para construir uno.

>[!note]
> la memoria swap en un archivo ofrece más flexibilidad al ser más facil de manipular tanto el archivo como el espacio que ocupa en el sistema

> Primero vamos a necesitar este comando.

- `fallocate` *file*: similar a `touch`, con la diferencia de que nos permite manipular el espacio reservado para el archivo en el disco.
	- `-l *size*: sirve para especificar el espacio que va a ocupar el archivo que creemos, por ejemplo, `250M`.

>A partir de este comando creamos el archivo `/swapfile`, que tiene que tener al menos la capacidad de `1G`.
Luego sigue este comando:

- `mkswap`: configura el archivo o partición que sea para que se comporte como una memoria swap.

>Finalmente, añadimos lo siguiente en el archivo `/etc/fstab`:

 `/swapfile none swap sw 0 0`

¡Listo!