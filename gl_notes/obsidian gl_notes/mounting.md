Revisar [[fs_part]] y [[mountpoints_part]] para refrescar sobre de qué trata el montaje de medios de almacenamiento.

##### Comandos
- `mount` *options device destination*: a secas, el comando lee y muestra el contenido del archivo `/proc/mounts`, que contiene todos los puntos de montaje presentes en el sistema. 
Supongamos que queremos montar una partición de nombre `sdc1`, ya formateada con algún sistema de archivos, para eso vamos a crear un subdirectorio con el nombre que queramos dentro de `/mnt`, y vamos a usar este comando de la siguiente manera:
`# mount /dev/sdc1 /mnt/test`
+ `-a`: monta todas las particiones presentes en el archivo `/etc/fstab`.
+ `-t` *filesystem*: permite aclarar el sistema de archivos con el que se va a montar la partición.
+ `-o` *option/s*: con esta opción podemos añadir cosas extra al montaje, y si se agrega más de una, estas irán separada por comas.
	+ `ro`: monta en modo solo lectura.
	+ `rw`: monta en modo lectura y escritura (*read and write*).
	+ `noexec`: deniega que programa alguno se pueda ejecutar desde la partición.
	+ `nosuid`: deshabilita los *bits* *SUID* y *SGID*.
	+ `nodev`: se van a ignorar los archivos presentes en el sistema de archivos que sean de tipo dispositivo de bloque o *character device*.
	+ `user`: permite que cualquier usuario monte esa partición en ese directorio, pero única y exclusivamente el mismo usuario puede desmontar la partición. Implica también `nosuid`, `nodev`y `noexec`.
	+ `defaults`: incluye las siguientes opciones: `rw`, `suid`, `dev`, `exec`, `auto` (será afectado por el comando `mount -a`), `nouser`, y  `async` (las operaciones de *I/O* no van a darse al mismo tiempo). 
+ `-n`: hace que no se monte automáticamente la partición al iniciar el sistema.
+ `-r`: lo mismo que `-o ro`.
+ `-L` *label*: si quisieramos montar una partición por su etiqueta en vez de por su locación, esta es la opción que se necesitaría.

A partir de este punto, todo lo que añadamos en `/mnt/test` recaerá sobre `sdc1`.
- `umount` *options device*: desmonta el dispositivo especificado.

> [!Important]
> Borrar las particiones no borra los archivos

##### Etiquetas
A los dispositivos montados con un sistema de archivos *ext*, podemos aplicarle el siguiente comando que nos permitirá añadirle una etiqueta a la partición:
- `e2label` *partition label*: la etiqueta puede tener el nombre que queramos.

>[!Important]
> Hay que señalar la partición, no el directorio donde esté montado.

Si no ponemos nada en el campo *label*, el comando mostrará el nombre actual de la etiqueta de la partición, si es que tiene una.
- `fatlabel` *partition table*: lo mismo que el comando anterior, pero para sistemas de archivos *FAT*.

##### Puntos de montaje espejados
Si montamos una partición con el sistema de archivos *btrfs*, una de las (tantas) cosas que nos permite hacer es espejar esa partición en el disco principal de la máquina.
Hagamos de cuenta que conectamos un *pendrive* (`sdb`) a nuestra computadora, y lo montamos la partición (`sdb1`) en `/mnt/pend`, que cuenta con tres subdirectorios: `/mnt/pend/secret`, `/mnt/pend/main`, y `/mnt/pend/stable`, que contienen cierta información.
Para realizar el “espejado”, primero vamos a crear tres subdirectorios en nuestro directorio raíz (`/`): `/stable`, `/main`, y `/all`.
Luego de eso, escribir en la terminal lo siguiente:
`# mount -o nosuid,user,subvol=/main /dev/sdb1 /main`
`# mount -o nosuid,user,subvol=/stable /dev/sdb1 /stable`
`# mount /dev/sdb1 /all`

A estas alturas, si le echamos un vistazo a los directorios en nuestro disco, vamos a ver el contenido del *pendrive* reflejado en los directorios, y en `/all` vamos a ver todo el contenido del *pendrive*. No solo eso, si no que si desde el mismo lugar modificamos, eliminamos, o creamos un archivo cualquiera, si de ahí vamos a `/mnt/pend` y el directorio que sea, se van a poder apreciar los mismos cambios, justamente porque están espejados.

> [!Important]
> Esto no quiere decir que sea muy útil como copia de seguridad, debido a que si se corompe la información de un lado, se va a corromper del otro, no es que una parte vaya a quedar a salvo

Entonces básicamente estamos modificando `sdb1` a través de `sda`, a diferencia de si estuvieramos operando directamente en el directorio `/mnt/pend`

##### Reparando sistemas de archivos
- `fsck` *filesystem*: este comando sirve para verificar el estado y, si se desea y es necesario, reparar el sistema de archivos (en una partición). Sin parámetros, se va a fijar en los sistemas de archivos que haya en `/etc/fstab`. 

> Solo funciona con sistemas de archivos desmontados, de lo contrario va a saltar un error.

##### file system table
El comando `mount` nos permite montar particiones, pero no que se monten automáticamente cuando el sistema arranque. Por eso es que existe el archivo `/etc/fstab`, en el cual, para que por ejemplo se monte siempre `sdd2`, tendríamos que añadir una línea con la siguiente información, todo en una línea, cada cosa separada por un espacio:
`UUID`: (*Unique User ID*) es la manera que tiene Linux de identificar particiones. Si se cambia el sistema de archivos de una partición o se desmonta y vuelve a desmontar, el UUID va a cambiar.
`mountpoint`: aquí va a estar el directorio donde se desee montar la partición.
`filesystem`: el nombre del sistema de archivos con el que va a ser montada la partición.
`options`: una o más de las mismas opciones que hay disponibles con `mount -o`.
`dump`: hay presente o `0` o `1`, señalando si el sistema de archivos va a tener una copia de seguridad o no, siempre y cuando se cuente con el programa `dump`instalado.
`pass`: si el valor es `0`, entonces cuando el sistema arranque, `fsck` no va a fijarse en el sistema de archivos, si tiene un valor de `1` es porque sí va a ser verificado por `fsck`, y no solo eso, sino que va a ser el primero, al estar este valor reservado para el directorio raíz. Un tercer valor posible es `2`, utilizado para el resto de sistemas de archivos que se desee que sean verificados pero que no sean el directorio raíz.

- `blkid`: nos permite conocer los UUID de las diferentes particiones presentes en el sistema.