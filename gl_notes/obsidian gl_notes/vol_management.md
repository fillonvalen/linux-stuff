A la hora de administrar sistemas de almacenamiento grandes y complejos, una herramienta muy útil es Logical Volume Manager 2 o *LVM2*, que permite la creación de los llamados volúmenes lógicos, que vendrían a ser uno o más volúmenes físicos, otorgando la posibilidad de administrar, redimensionar o combinar el espacio de estos volúmenes lógicos en caliente, sin riesgo de perder ningún dato. También puede realizar *snapshots*, migración y reubicación de datos, y más…

>El programa, llamado `lvm2`, hay que instalarlo. 

##### Crear un lvm 
En un caso hipotético en el que tenemos dos discos: `sdb`, de 5G, y `sdc`, de 10G, para crear un volumen lógico primero tenemos que ejecutar el comando:
`# pvcreate /dev/sd{b,c}`

Que inicializa uno o más dispositivos físicos como un solo volumen físico.
A continuación, con el comando:
`# vgcreate vol_group /dev/sd{b,c}`

Creamos un espacio (de cualquier nombre) que abarca un grupo de volúmenes lógicos que podemos crear con el comando:
`# lvcreate -L 2G -n log_vol vol_group`

Donde la opción `-L` nos permite especificar el tamaño del volumen y `-n` el nombre. Por último va el nombre del grupo de volúmenes en el que vamos a crear el volumen lógico.

##### Información de los volúmenes
Para ver los volúmenes físicos en el sistema, se emplea el comando `pvs`, `vgs` para los grupos de volúmenes, y `lvs` para los volúmenes lógicos. Si se desea información más detallada, existe la opción `-o` para los tres comandos, que va seguida de las diferentes columnas que queremos que muestre el comando (==revisar los manuales para saber qué columnas están disponibles==). Si no, existen también los comandos `pvdisplay`, `vgdisplay` y `lvdisplay`.

> [!Important]
> Los volumenes lógicos creados van a aparecer en el directorio `/dev/mapper` con el nombre del grupo, un guión medio `-`, y el nombre del volumen.

##### Aumentar o reducir tamaños

`lvextend -L 5G /dev/mapper`  
`lvreduce`









