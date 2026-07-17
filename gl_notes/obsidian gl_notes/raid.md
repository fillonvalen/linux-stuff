Un Arreglos Redundante de Discos Independientes, o por sus siglas en inglés, *RAID*, es una tecnología que en Linux se usa para que dos o más discos duros se comporten como uno solo, teniendo sus variantes:
##### Rendimiento
Se le conoce como “Stripping”, o *RAID 0*, el cual une dos o más discos, combinando sus espacios de almacenamiento, comportándose como uno solo. 
Es un nivel de *RAID* bastante usado. Sin embargo, no podemos añadir más discos una vez el *RAID* haya sido armado, sino que hay que formatear el anterior.
##### Redundancia
“Mirroring”, o *RAID 1*, hace justamente eso: espejar dos discos. Exactamente lo mismo que va a uno, va al otro, siendo útil para copias de seguridad, pero eso no significa que si uno se rompe, el otro se mantenga intacto. A pesar de eso, el nivel 1 es más usado incluso que el nivel 0.

##### Rendimiento con paridad
El nivel 5 intenta un equilibrio entre el nivel 0 y 1, resultando algo caro, debido a que si por ejemplo usaramos tres discos unidos con *RAID 0*, tendríamos que tener otros tres discos más para que puedan ser espejados. 

##### Rendimiento con doble paridad
Este nivel, de número 6, ofrece más eficiencia que el *RAID 5*, y sí, eso quiere decir que elegir esta opción te va a salir más caro todavía.
##### RAID 10
Similar al nivel 5, combina Rendimiento y Redundancia. Es la mejor opción, a la vez que la más cara. 

##### multiple disk administration
Para manaejar *RAIDs* en nuestro sistema, hay que disponer del programa `mdadm`, el cual no viene instalado de manera predeterminada en el sistema.

###### Crear un *RAID* (nivel 0)
Para crear uno, hay que ejecutar el siguiente comando:
`# mdadm --create --verbose /dev/md0 --level=0 --raid-devices=2 /dev/sdb /dev/sdc`

`--create`
	`--verbose`: muestra qué está haciendo el comando
	`/dev/md0`: (multiple devices) este va a ser el nombre del dispositivo *RAID*.
`--level=0`: el nivel que se desee, en este caso `0`.
`--raid-devices=0`: cantidad de discos que se van a usar.
	`/dev/sdb /dev/sdc`: seguido de lo anterior van los nombres de los dispositivos a unir. Otra forma de escribir esto sería `/dev/sd{b,c}`.

Luego de haber creado el *RAID*, tenemos que montarlo, por ejemplo en un subdirectorio `/mnt/raidzero`:
`# mount /mnt/raidzero`

A continuación, lo formateamos con un sistema de archivos, por ejemplo *ext4*:
`# mkfs.ext4 /dev/md0`

Como con cualquier dispositivo que se monte, hay que agregarlo a `/etc/fstab` si queremos que el montaje sea automático al encender la máquina. El respectivo UUID lo sacamos con el comando `mdadm` y las opciones `--detail` y `--scan`.
Una vez agregado el *RAID*, para que su arranque sea exitoso, le tenemos que decir al archivo `/etc/mdadm.conf` (si no existe, crearlo) qué tiene que cargar, y eso se logra redireccionando toda la salida del comando anteriormente ejecutado a ese archivo:
`# mdadm --detail --scan >> /etc/mdadm.conf`


###### Eliminar un *RAID*
Si ya no queremos cierto *RAID* en nuestro sistema, primero hay que desmontarlo:
`# umount /dev/md0`

Para después ejecutar lo siguiente:
`# mdadm --stop /dev/md0`

Y esto también, que llena de ceros a los dispositivos involucrados en el *RAID*:
`# mdadm --zero-superblock /dev/sdb /dev/sdc`

Como paso final, vamos a usar `wipefs`, que nos va a permitir borrar todo el sistema de archivos en los mismos dispositivos que estuvieron en el *RAID*, junto a la opción `-a`, que borra toda información del sistema de archivos que haya quedado: 
`# wipefs -a /dev/sd{b,c}`