 Para entender mejor cómo funciona el manejo del almacenamiento, podemos echarle un vistazo a la relación entre estos tres conceptos:

***Particionado***      
+ **Crea** las divisiones lógicas en el disco.

***Volúmenes*** 
+ **Representa** un espacio de almacenamiento.
+ Puede abarcar **uno o más** dispositivos físicos, como unidades de estado sólido o particiones.
+ **Organiza y almacena** datos.

***Sistemas de archivos***
 + **Formatea y organiza** el espacio de almacenamiento en cada partición o volumen.

`b` para dispositivo de bloque.
`c` para *character devices*, que representan hardware que se comunica directamente con el sistema, sin intermediario alguno.
##### Comandos
- `lsblk` *options device*: muestra la siguiente información acerca de todos los dispositivos de almacenamiento en el sistema si es que no se especifica uno:
`NAME`: nombre del dispositivo o partición o volumen.
`MAJ:MIN`: (*major:minor*)  el *major number* es usado por Linux para identificar diferentes dispositivos de almacenamiento, mientras que el *minor number* es usado para distinguir entre particiones o diferentes dispositivos manejados por ese dispositivo de almacenamiento.
`RM`: con un valor entre 0 (no) y 1 (sí), aclara si el dispositivo es removible.
`SIZE`: si supieras un poco de inglés…
`RO`: puede haber un 0 o un 1, dictando si el dispositivo está en modo solo lectura o no.
`TYPE`: tipo de dispositivo de bloque, como por ejemplo partición, disco, dispositivo encriptado, etc.
`MOUNTPOINTS`: punto de montaje del dispositivo de bloque.
+ `-o`: con esta opción podemos especificar qué columnas queremos que aparezcan (en mayúsculas). Para ver todas las opciones disponibles hay que usar el comando  `lsblk --help`

- `df` *options*: muestra todos los sistemas de archivos presentes en el sistema, mostrando sus puntos de montaje, su tamaño, y el porcentaje que llevan ocupados.
	+ `-h`: muestra los tamaños de una forma más redactable, oseáse en megas, gigas…

##### Modificando el almacenamiento

> [!Important]
> `fdisk` y `cfdisk` son comandos que sí o sí requieren de permisos de super-usuario (root).

- `fdisk` *options device*: este comando permite crear, modificar o eliminar diferentes sistemas de archivos o particiones de dispositivos de bloque en el sistema. Para usarlo, seguido del comando hay que especificar el dispositivo que queramos.
Llegados a este punto, entramos en el menú del comando, donde hay diferentes opciones que podemos usar, siendo estas las más relevantes:

`d` borra una partición.
`e` cambia el espacio de una partición.
`g` crea una tabla de particiones GPT.
`l` lista los posibles tipos de partición, cada uno con un ID que es un número hexadecimal.
`m` muestra el menú con todas las opciones.
`n` crea una partición.
`t` cambia el tipo de partición.
`p` muestra la tabla de particiones actual, junto a información detallada al respecto.
`w` guarda los cambios hechos.
`q` descarta cualquier cambio.

> [!Warning]
> Es recomendable jugar con este comando en una máquina virtual, añadiéndole discos virtuales a la máquina, y evitar hacer cagadas en la máquina de verdad.

>[!tip]
>Se puede crear un archivo con instrucciones preestablecidas, por ejemplo uno llamado `fd_instructions` que contenga:
>~~~
>g
>w
>q
>~~~
>y luego ejecutar el comando `fdisk /dev/sdb < fd_instructions`, y así formatear el disco.

- `cfdisk` *options device*: se utiliza de la misma manera que `cfdisk`, pero permite un manejo más amigable e intuitivo.

##### Sistemas de archivos
Existen diferentes tipos de sistemas de archivos, cada uno ajustándose a determinadas necesidades.

***extended***
Hoy en día los sistemas de archivos *ext* cuentan con tres versiones: *ext2*, *ext3*, y *ext4*.
*ext4* es la opción más elegida actualmente debido a su gran capacidad de almacenamiento, ofreciendo estabilidad, rendimiento, y una amplia gama de funciones.
*ext3* no es mala elección pero no tiene tanta capacidad y funciones como su predecesor.
*ext2* es usado solamente para sistemas o directorios de una escala pequeña que no necesiten cosas como el *journaling*[^1], que no tiene, a diferencia de sus dos predecesores.

***xfs***
Este sistema de archivos, el predeterminado en la familia de los sistemas RHEL, ofrece una interesante capacidad de almacenamiento, siendo robusto y rápido; sin embargo, en lo que respecta a funciones avanzadas, es bastante simple, y no siempre es seguro, ya que a veces tiende a padecer errores silenciosos en el disco.

***btrfs***
Es un sistema rico en funciones avanzadas, incluso más que *ext4*, como por ejemplo la corrección automática de errores de datos, o el mecanismo *COW* ([[processes#^4d8d05]]).
>Hoy en día este sistema se considera algo inestable, porque sigue un desarrollo activo al día de la fecha. 

***zfs***
Con una capacidad casi infinita (más de un billón de TB, oséase más de 1 000 000 000 000 000 GB), posee una eficiente compresión de datos, una buena protección contra la corrupción de información, utiliza el mecanismo *COW*, *snapshots* [^2] , y demás.
>Por estas razones es que este sistema está hecho con el propósito de ser usado con hardware potente y un contexto que requiera de las funciones que ofrece, ergo no es recomendable para sistemas pequeños.

***FAT***
Sistema de archivos bastante viejo desarrollado por Microsoft, usado para dispositivos de almacenamiento en dispositivos pequeños como USBs, debido a su compatibilidad con otros sistemas operativos. Cuenta con variantes como *FAT12*,*FAT16*, *FAT32* (esos números siendo los *bits*), y *exFAT*. En el sistema operativo Void Linux, por ejemplo, recomienda montar la partición `/boot/efi` con un sistema de archivos *FAT32*.

***ntfs***
También desarrollado por Microsoft, cuenta con varias características que lo hacen el sistema de archivos usado para diferentes versiones de Windows actuales, como el cifrado de datos, *journaling*, gran capacidad, poder detectar automáticamente los errores y repararlos sin tener que desmontar nada. También ofrece compatibilidad con sistemas basados en GNU/Linux, y BSD. 

##### Comandos

> [!Warning]
> * Recomendable jugar con esto en una máquina virtual para evitar agarrarse de los pelos más tarde después de haber formateado todo tu directorio del sistema.
> * Para poder montar un sistema de archivos en donde sea, la partición ***NO*** debe estar montada, de lo contrario los comandos mostrarán un error.

Existe una herramienta de nombre `mkfs` la cual nos permite incorporar cierto sistema de archivos especificado a una partición. Entre varias opciones, estos son algunos ejemplos:
- `mkfs.ext2` *device*
- `mkfs.ext3` *device*
- `mkfs.ext4` *device*
- `mkfs.xfs` *device*
- `mkfs.btrfs` *device*
- `mkfs.fat` *device*: (lo mismo que `mkdosfs`) este es un ejemplo en el que podemos crear un sistema de archivos *FAT32* en la partición `/boot/efi`, usando este comando junto a la opción `-F` con el valor `32`:
`# mkfs.fat -F32 /boot/efi`

- `mkfs.ntfs` *device*

> [!tip]
> * Para todos los comandos, si la partición tiene ya montado un sistema de archivos y quisieramos formatearla con otro, entonces, sea el sistema de archivos que eligamos, hay que usar la opción `-f`, o desmontar la partición.
> * Hay que tener en cuenta que cada sistema de archivos requiere que la partición tenga deterninada capacidad de almacenamiento mínima.

Para poder identificar qué sistema de archivos está presente en una partición, podemos usar el comando `file` junto a la opción `-s` seguido de la partición, o con el comando `df` junto a la opción `-T`.

[^1]: Es una característica de ciertos sistemas de archivos en el cual se consta de una estructura de datos de nombre *journal* (diario), donde se van guardando cambios que todavía no hayan sido “escritos” en el sistema de archivos, resultando en una herramienta muy útil en caso de que la máquina sufra algún error o se apague involuntariamente.

[^2]: copia de solo lectura (*read-only*) de un sistema de archivos congelado en un momento específico (empleando el mecanismo *COW*), permitiendo copias de seguridad y la recuperación de datos en caso de pérdida.
