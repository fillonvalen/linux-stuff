
> [!important]
>1. Cuando se trata de un comando que recibe un archivo, hay dos opciones: o se pone el nombre del archivo solo, o se escribe la ubicación exacta del archivo, empezando por el directorio raíz (`/`), o se empieza por el actual. Lo que pasa cuando no se comienza con el directorio raíz, es que estamos poniendo de manera predeterminada el actual, representado por un punto `.`, así que si nos encontraramos en `/home/johnny/Downloads`, y escribimos solo `ls games`, sería lo mismo que poner `ls ./games` (`/home/johnny/Downloads/games`), o si estuvieramos en `/usr/share` y escribiéramos solo `cd fonts`, es lo mismo que `cd ./fonts` (`/usr/share/fonts`).
>2. Si se desea un resumen rápido del uso de cierto comando y sus opciones disponibles, la mayoría cuenta con la opción `-h` o `--help`.

##### Controlando el sistema
- `whoami` *option*: muestra el usuario registrado.
- `pwd` *option*: muestra el actual directorio.
- `su` *options* *-* *user*: cambiar del usuario actuar al usuario "user".
	- `su -`: cambia al super-usuario en una login shell, pidiendo antes la contraseña del mismo.
	+ `su`: así en crudo, permite registrarse como super-usuario (non-login shell) siempre y cuando se sepa la contraseña del mismo.
- `sudo` *cmd*: permite ejecutar cualquier comando que requieran los permisos del usuario *root* (super-usuario).
	+ `sudo su`: cambia al super-usuario en una *non-login shell*, pero usando la contraseña del usuario registrado (esto es útil para instalaciones en las que no es solicitada una contraseña específica para el super-usuario).
- `logout`: salir de la sesión de la *login shell*.
- `exit`: se utiliza para salir de la sesión del usuario en la shell.
- `poweroff` *options*: apaga el sistema enseguida.
- `shutdown` *options* *time*: apaga el sistema. El parámetro predeterminado de *time* es `+1`, siendo la cantidad de minutos en la que apagará el sistema.
	+ `shutdown now`: lo mismo que shutdown +0.
	+ `shutdown` *hh:mm*: el sistema se va a apagar a la hora indicada (en formato de 24h) (reemplazar *hh:mm* por horas y minutos).
	+ `-r`: lo mismo que el comando reboot.
- `reboot` *options*: reinicia el sistema.
- `uname` *options*: muestra información del sistema.
	+ `-a`: imprime toda la información.
	+ `-m`: imprime la arquitectura (*x86_64* quiere decir "extensión de arquitectura de 64 bits del grupo de instrucciones x86"), oséase amd64.
	+ `-n`: imprime el nombre de la computadora (hostname).
	+ `-o`: imprime el nombre del sistema operativo.
	+ `-r`: imprime la versión actual del kernel usado.
	+ `-s`: imprime el nombre del kernel.
	+ `-v`: imprime información más detallada de la versión del kernel, como la fecha de lanzamiento.

##### Navegando y explorando directorios
* `cd` *options* *directory*: la terminal se ubicará en el directorio especificado.
	+ `cd -`: esta opción dirige al usuario al directorio en el que estuvo anteriormente.
	+ `cd ~`: dirigirá al usuario a su correspondiente directorio dentro de `/home`, si existe. En caso del super-usuario, lo dirigirá a `/root`.
- `pushd` *option  +N | -N | dir*:
- `popd` *option +N | -N*:
* `dirs` *options +N -N*: 
- `stat` *filename*: muestra el estado e información detallada de *filename*.
- `ls` *options* *directory | file*: lista el contenido en varias columnas del directorio dir. Sin parámetros es lo mismo que `ls .`.
	+ `-1`: lista el contenido de manera vertical.
	+ `-l`: similar a `ls -1` pero mostrando información más detallada de los ficheros, por ejemplo:
	~~~
	$ ls -l
	total 32
	drwxrwxr-x 2 laquid laquid 4096 Feb 5 13:01 Desktop
	drwxrwxr-x 2 laquid laquid 4096 Feb 5 13:01 Documents
	drwxrwxr-x 2 laquid laquid 4096 Feb 5 13:01 Downloads
	drwxrwxr-x 2 laquid laquid 4096 Feb 5 13:01 Music
	drwxrwxr-x 2 laquid laquid 4096 Feb 5 13:01 Pictures
	drwxrwxr-x 2 laquid laquid 4096 Feb 5 13:01 Public
	drwxrwxr-x 2 laquid laquid 4096 Feb 5 13:01 Templates
	drwxrwxr-x 2 laquid laquid 4096 Feb 5 13:01 Videos
	~~~
  (A)(          B         )(C)(      D       )(     E       )(    F   )(             G             )(         H         )
> **A**: El primer carácter de esta sección da a entender de qué clase de objeto se trata (en este caso la “d” es de directorio).
> **B**: Los permisos.
> **C**: Aquí se expresan la cantidad de hardlinks que tiene el objeto.
> **D**: Usuario al que le pertenece el objeto.
> **E**: Grupo al que le pertenece el objeto.
> **F**: Espacio que ocupa (en bytes).
> **G**: Última vez que se accedió o modificó el directorio o archivo, en formato *Mes día_del_mes hh:mm*.
> **H**: Nombre del objeto.
+ `-a`: muestra los archivos ocultos (aquellos que comienzan con ".")
	+ `-s`: muestra el tamaño de los archivos en kilobytes.
		+ `-sh`: lo mismo que `ls -s`, pero más inteligible para los humanos.
	+ `-t`: ordena los ficheros de manera cronológica según la fecha de acceso o modificación (primero el más reciente).
	+ `-R`: lista de manera recursiva, oseáse no lista solo los directorios, si no sus contenidos.
	+ `-d`: en vez de listar el contenido del directorio, lista el contenido en sí (más útil resulta combinado con otras opciones, como `ls -dl`, por ejemplo).
	+ `-C`: si redirigimos la salida de ls a un archivo, al imprimirlo aparecerá todo en una sola columna, pero si se usa esta opción, la salida será con la cantidad original de columnas.
	+ `-b`: esto permite expresar los caracteres no gráficos (caracteres que no tienen una forma simbólica, como el espacio, o el Enter) en los nombres de archivos y directorios a caracteres gráficos. Por ejemplo, si un archivo contiene una tabulación (ej.: `my    file`), en vez de imprimirse en crudo, aparecerá como `my/tfile`. O si tiene un espacio (ej.: `my dir`), será expresado como `my\ dir/`.
- `dir` *options directory | file*: básicamente lo mismo que `ls`, pero con los parámetros `-C`, y `-b` (`ls -Cb`).
- `file` *options file*: imprime qué tipo de archivo es *file*.

##### Manipulando archivos
- `clear` *options* limpia la terminal.
- `touch` *options file*: en caso de existir el archivo *file*, modificará la fecha de acceso, y en caso contrario creará uno con el nombre filename. Si no se especifica directorio alguno, el archivo será modificado (si existe) o creado en el directorio actual.
- `cat` *options file*: imprime el contenido que haya en `file`. 
	+ `-E`: representa los caracteres `/n` (newline) (Enter) como `$`.
	+ `-n`: antes de cada línea, muestra su respectivo número.
	+ `-T`: expresa las tabulaciones como `^I`.
	+ `-v`: imprime los caracteres no imprimibles, a excepción de la tabulación.
	+ `-A`: lo mismo que `cat -vET`.
- `echo` *options* *text*: imprime lo que sea que se haya escrito en *text*, ignorando las comillas dobles (`“”`), o las simples (`‘’`), siempre y cuando estén cerradas.
	- `-e`: si esta opción no se usa, el comando va a interpretar de manera literal a los caracteres de escape como `\t` o `\n` o `\e`.
	- `-n`: automáticamente, este comando imprime una nueva línea después de cada texto, y esta opción deshabilita eso.
	
- `rm` *options file*: elimina el archivo *file*.
	+ `-r` *directory*: lo mismo que `rmdir`, solo funcionando si el directorio aclarado está vacío.
	+ `-f` *directory*: junto a la opción `-r` eliminará el directorio esté vacío o no.
- `mkdir` *options dir*ectory: crea un directorio con el nombre especificado.
	+ `-p` *dir1/dir2/.../dirN*: crea los directorios necesarios para llegar a *dirN* (creará *dir1*, dentro de éste creará *dir2*, y así).
- `rmdir` *options directory*: borra el directorio especificado, siempre y cuando esté vacío.
- `cp` *options file file_copy_name*: copiará el archivo especificado con el nombre establecido.
	- `-r` *directory  directory_copy_name*: lo mismo pero para los directorios.
- `mv` *options file destination*: moverá el archivo *file* o el directorio a *destination*, ya sea con el mismo nombre o con otro.
	- `-r` *directory destination*: esta opción hay que usarla si queremos cambiar un directorio y todo su contenido a otra locación.
- `less` *options file*: visor de texto simple pero útil, utilizando una forma de navegación a través del contenido del archivo similar a Vim.
- `nano` *options file*: editor de texto simple e intuitivo, ideal para usuarios nuevos en Linux a la hora de editar archivos en la terminal.

##### Rangos
Bash nos permite utilizar rangos a la hora de manipular archivos. Por ejemplo, si quisieramos crear treinta archivos, cada uno en el rango del 1 al 30, habría que escribir en la terminal
`$ touch file{1..30}.txt`

Si quisieramos eliminarlos, simplemente hay que cambiar `touch` por `rm`. Los rangos también funcionan alfabéticamente, siendo, por ejemplo `touch {a..h}` un comando válido que va a crear 8 archivos, cada uno con una letra del abecedario.	 A la inversa (poniendo primero el número/letra de mayor valor y luego el/la de menor valor) también funciona.

##### Caracteres comodínes
- `*`: reemplaza cualquier cantidad y tipo de caracteres que le sigan a la anterior secuencia de caracteres hasta llegar a la siguiente.

**Ejemplos**:
 `ls *.c` 
Listará solo los archivos que terminen en *.c*, sin importar la cantidad de caracteres que haya antes.
 
 `ls a*.txt`
Listará solo los archivos que empiecen con *a* y terminen con *.txt*, ignorando la cantidad de caracteres que haya en el medio.
 `rm fi*`
Borrará todos los archivos que comiencen por *fi*, sin tener en cuenta la cantidad de caracteres que le sigan

- `{}`: permite la manipulación de varios archivos en una misma línea.

**Ejemplos**:
 `mkdir /home/user{1,2,3}`
Creará los subdirectorios *user1*, *user2*, y *user3* en el directorio `/home`.

 `touch /home/user1/Documents/doc{1,2,3}.odt`
Creará los archivos *doc1.odt*, *doc2.odt*, y *doc3.odt* en el directorio `/home/user1/Documents/`.

- `?`: similar al comodín `*`, pero este sí tiene en cuenta la cantidad.

**Ejemplo:**
 `ls -lsh b???.c`
Imprimirá una lista detallada de los archivos que comiencen con *b*, que le sigan otros tres caracteres cualquieras, y que finalize con *.c*.

- `[a-b]` ó `[ab]`: este comodín tiene en cuenta el caracter (uno solo) que esté en un rango alfabético o númerico si es que hay una línea media de por medio (`-`). En caso contrario, se tendrán en cuenta solo los caracteres dentro de los corchetes.

**Ejemplos:**
 `rm [bdz]ash`
Borrará aquellos archivos cuyo primer carácter sea o *b*, o *d*, o *z*, y sigan con *ash*.

 `ls -l file[0-9]`
Listará todos los archivos que comiencen con *file* y el siguiente carácter sea un número entre el 0 y el 9.

> [!warning]
>No todos los comodines van a funcionar igual con todos los comandos. Por ejemplo, el comando `touch mytext[0-9].txt` creará el archivo
>`mytext[0-9].txt` literalmente.

##### Concatenando comandos
Cuando ejecutamos un comando sin problemas, el estado de salida será `0`. Pero, por ejemplo, cuando ejecutamos ls nos dice que no encontró el archivo
que le especificamos, el estado de salida será `2` u otro número. Esto lo podemos saber gracias a cierta variable de nombre `$?`. Así que si quisieramos
saber el estado de salida del último comando ejecutado, tendríamos que imprimir dicha variable con el comando `echo`.

*cmd1* `&&` *cmd2* **(and)**: *cmd2* solo se ejecutará si, y solo si *cmd1* tiene un estado de salida 0.
*cmd1* `||` *cmd2* **(or)**: *cmd2* solo se va a ejecutar si, y solo si *cmd1* tiene un estado de salida que no sea `0`.
*cmd1* `;` *cmd2* **(separator)**: *cmd2* va a ejecutarse independientemente del estado de salida de *cmd1*.
*cmd* `\` : permite alargar las opciones de un comando hasta que se deje de poner la barra invertida después de la opción. Ejemplo de uso:

`$ mkdir Downloads Documents Pictures Music \`
`> Videos Public Desktop Templates \`
`> Phone Projects Studies Writings`

> [!note]
>Tener en cuenta que los operadores lógicos son concatenables.
>Algo como *cmd1* `&&` *cmd2* `||` *cmd3* es completamente válido.

##### EN BUSCA DEL TESORO
- `whereis` *options cmd*: este permite buscar binarios (y solo binarios), o sea comandos, y la ubicación de sus respectivos manuales.
- `which` *options cmd*: lo mismo que `whereis`, pero solo muestra la ubicación del binario.
- `find` *directory_where_to_look_for options value_to_match*: permite encontrar cualquier clase de archivos o directorios que cumplan con ciertas condiciones.

**EJEMPLOS:**
 `find /dev -name sd*`
Imprimiría una lista de todos los archivos que comienzen con *sd* en el directorio `/dev`.

 `find . -type d`
Va a imprimir una lista de solamente los subdirectorios en el directorio actual, que vendría a ser `.`.

 `find /etc -name *.conf -size +1M`
Permite imprimir una lista de los archivos en /etc que terminen en *.conf* y ocupen un tamaño mayor a 1 mega. 

 `find / -atime -7`
Hará una lista de todos los archivos del sistema a los que se haya accedido en los últimos 7 días.

 `find /home -mmin +30 -name *.pdf`
Imprimirá una lista de los archivos en el directorio `/home` que hayan sido modificados hace más de 30 minutos y cuyos nombres finalizen en *.pdf*.
 
 `find /home -name test* -delete`
Esta opción borrará todos los archivos en /home que comiencen con “test”.
 
 `find ~/Pictures -iname abc* -exec mv {} ~/Documents`
Moverá todos (`{}` quiere decir “todos los archivos que encuentres”) los archivos encontrados en `~/Pictures` que empiecen con *abc*, pero en caso insensitivo (esto quiere decir que no discrimina entre mayúsculas y minúsculas, asi que los archivos que comiecen con  *AbC*, por ejemplo, serán validos por igual) a `~/Documents`.

 `find / -size +100M 2>/dev/null`
Permite listar todos los archivos en el directorio raíz que pesen más de 100 megas, y cualquier error (por ejemplo cuando el usuario no tiene permitido acceder a `/root`) (revisar la sección de operadores lógicos) será dirigido a `/dev/null`, que básicamente vendría a ser una especie de agujero negro digital, borrando los mensajes de error.

`find /var -name *.gz 1>~/vargz1.txt`
Hace que todo lo que encuentre que termine con *.gz* lo mande al archivo *vargz1.txt* ubicado en `/home/johnny/` (`~`), a excepción de los errores (fijarse que hay un `1` en vez de un `2`).

##### Y esto, ¿cómo lo uso?
- `man` *options section command*: mostrará el manual de *command*. Todos están en `/usr/share/man/`, donde hay varios subdirectorios (secciones), desde `man1` hasta `man9`:
**1** para programas ejecutables o comandos del shell.
**2** para llamadas del sistema (funciones del kernel).
**3** para las funciones de las librerías de C.
**4** para los dispositivos y archivos especiales (lo normal es que estén en /dev).
**5** para los detalles de archivos de configuración y del sistema como `/etc/passwd` o `/etc/fstab`. Por ejemplo, para poder entender la estructura y el funcionamiento del archivo `/etc/passwd` se debería usar el comando
`man 5 passwd`, ya que también existe un comando llamado `passwd`.
**6** para juegos.
**7** para varios.
**8** para las herramientas de administración del sistema y demonios, comandos más que nada usados por el superusuario.
**9** para las rutinas del kernel (no estándar).
- `whatis` *options command*: imprime un breve resumen de la función del comando cmd, dando a conocer en qué grupo se encuentra el manual de dicho comando.
- `apropos` *options keyword*: muestra tanto los comandos como las descripciones (de `whatis`) que contengan lo escrito en *keyword*.
- `type` *options command*: muestra cómo la shell interpreta al comando *command*, identificando si es un programa incorporado en la shell, si es un ejecutable (un binario) regular, o un alias.