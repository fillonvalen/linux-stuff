PUNTOS DE MONTAJE
     Es la manera que tiene GNU/Linux de asociar un dispositivo de almacenamiento con un directorio, para así poder acceder a los datos del mismo.

PARTICIONADO BÁSICO
     En Linux, por lo general, solamente basta con tener dos puntos de montaje, el primero y el más importante representado con una barra vertical `/`, que viene siendo el llamado directorio raíz, de donde surgen el resto de los directorios. El segundo es para la memoria swap. De todos modos se puede tener más puntos de montaje para tener separados ciertos directorios, como `/boot`, aunque no suele ser del todo necesario.

¿QUÉ HAY EN LA PARTICIÓN `swap`?
     La memoria swap se hace presente cuando la RAM se llena, encargándose de tomar las tareas menos activas, y las lleva al espacio en el disco que swap tiene reservado para sí. Sin embargo, hoy en día pocas computadoras requieren de su servicio gracias a la capacidad que fue ganando la RAM.

¿QUÉ HAY EN LA PARTICIóN `/boot`?
     Aquí se encuentran varios archivos, como el kernel, los archivos necesarios para el inicio del sistema (pero no los que se usan durante el inicio), el gestor de arranque GRUB (Grand Unified Bootloader) ó el EFI, que vendría a ser el antecesor de UEFI.

¿QUÉ HAY EN LA PARTICIÓN `/home`?
     Aquí aparecerán los directorios de los usuarios con sus cosas personales, (excluyendo al super-usuario, que tiene su propio directorio llamado `/root` ubicado directamente en el directorio raíz). Lo normal es que los nombres de los directorios sean el mismo que el del usuario dueño, pudiendo encontrar adentro otros directorios para las descargas, los documentos, las imágenes, etcétera.

¿QUÉ HAY EN LA PARTICIÓN `/usr`?
     Este tiene varias cosas importantes. Primero se encuentra el subdirectorio `/usr/bin`, que contiene una gran parte de los ejecutables del sistema, desde comandos básicos hasta programas. Los demás ejecutables están en `/usr/sbin`, hechos para administrar el sistema, solo pudiéndose usar con permisos de super-usuario. 
     Después está `/usr/lib`, donde yacen las librerías.
     Otro subdirectorio importante es `/usr/share`, cuyo contenido trata sobre información que no depende de la arquitectura, permitiendo ser compartida entre sistemas con diferentes arquitecturas.
     Una más: `/usr/src`, que contiene diferentes códigos del kernel y documentación del mismo.

¿QUÉ HAY EN LA PARTICIÓN `/var`?
     Este directorio contiene información variable en su contenido, como por ejemplo los eventos que van ocurriendo en el sistema desde que este se prendió.
     También encontramos el subdirectorio `/var/backups`, que contiene copias de seguridad de diversos archivos del sistema.
     Otro es `/var/cache`, conteniendo datos que no importa si son borrados ya que son fácilmente recuperables.

¿QUÉ HAY EN LA PARTICIÓN `/etc`?
     Está más que nada para archivos de configuración del sistema, pero también se puede encontrar más que eso, porque etc viene literalmente de etcétera, o sea que en él se guardan cosas que no pertenecen a ningún otro directorio.

¿QUÉ HAY EN LA PARTICIÓN `/tmp`?
     Sencillamente es para almacenamiento con un corto tiempo de vida. Pero claro, también está `/var/tmp`, que ocupa más espacio al contener archivos temporales por mucho más tiempo.

¿QUÉ HAY EN LA PARTICIÓN `/dev`?
     Aquí están los dispositivos de almacenamiento representados como archivos, porque en Linux todo es un archivo, incluyendo tu teclado o el CPU. Esto permite interactuar con el hardware y el kernel sin complicaciones.
     Otra cosa presente son las terminales virtuales.

¿QUÉ HAY EN LA PARTICIÓN `/opt`?
     El directorio está originalmente reservado para programas que no formen parte del sistema perativo, llamados *add-on* en inglés, que vendrían a ser los que instala el mismo usuario.