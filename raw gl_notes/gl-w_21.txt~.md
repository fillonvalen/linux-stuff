21. PROCESOS
     Un proceso es la constancia de un programa en ejecución. Esto quiere
decir que siempre que un programa se ejecute, el kernel crea un proceso para
ese programa. Una buena referencia que leí sobre la diferencia entre un
programa y un proceso es que un programa es una receta, y el proceso es el chef
que sigue la receta.
     Para poder identificarlos y manejarlos, se usan PIDs (Process ID).     
     Otra cosa importante, es que el kernel le da a cada proceso un pedazo de
memoria propio para usar, la cantidad depende de la relevancia del proceso.
     Como se menciona más abajo, todo es un archivo, y los procesos no son
una excepción. Cada uno de los procesos en el sistema lo podemos encontrar
en el directorio "/proc", que si aplicamos "ls -l" vamos a ver los diferentes
PIDs, que son otros directorios con lo necesario para llevar a cabo el proceso.

21.1 HIJOS Y PADRES
     Primero hay que entender lo siguiente: la filosofía de Unix es que todo
es un archivo, todo. Por ejemplo, la shell es un proceso el cual está usando
el archivo que representa la terminal (para la I/O (Input/Output)). Entonces,
cuando se ejecute un comando, como "dir", si el SO arrancaría el proceso desde
cero, este no sabría del archivo de la terminal, teniendo que reabrirlo, y eso
sería repetitivo y consumidor, por eso es que bash, en este caso, lo que va a
hacer es clonarse y tener un proceso "hijo" que hereda todos los archivos que
tiene abiertos el padre, ambos continuando con la ejecución del código a
partir de donde haya quedado. Esto se da gracias a una función en C llamada
"fork()" así, sin parámetros necesarios.
     El problema era que antes fork() copiaba todo lo que había en el proceso
padre, oséase que si requería un 1GB, el proceso hijo y va a pesar 1GB, de
manera que hoy en día se usa un mecanismo de siglas COW (Copy-on-write), 
que en vez de copiar directamente todo al hijo, esa página (bloque) de
memoria la compartía en modo solo lectura por lo menos hasta que el hijo
intentase sobreescribir una de estas páginas, y ahí es cuando se le comparte
solamente esa página, mientras que el resto permanece igual que al principio.
     Ahora bien, resulta que si ejecutacemos por ejempplo "dir", al instante se
va a dejar de ser una copia de la shell y va a reemplazar la memoria por el
programa "dir", gracias a la función "exec()", que toma como parámetro el
comando. El PID no cambia.
     La última etapa es con la función "wait()" por parte del padre,
pausándose hasta que el proceso hijo termine.

21.2 SEÑALES
     Los procesos, con determinados comandos o funciones, pueden recibir una
señal para que entren en determinado estado. Hay una buena cantidad de ellas,
identificadas tanto con un número como con un texto, pero solo vamos a ver
los siguientes:
15 ---> SIGTERM: solicita a un programa que termine, dándole la oportunidad
de un cierre "limpio", o sea que pueda cerrar archivos abiertos, guardar datos,
borrar lo innecesario... 
9  ---> SIGKILL: a diferencia de la anterior, esta señal fuerza al programa a
cerrarse en el momento. 
19 ---> SIGSTOP: detiene un proceso, lo pausa.
2  ---> SIGINT: esta señal se da cuando un programa es terminado por el
teclado, como ctrl-C por ejemplo.
11 ---> SIGSEGV: señal que envía el sistema cuando un programa intenta
acceder a una sección de la memoria que no se le fue asignada.

21.3 IDS
     Cada proceso va a tener cuatro tipos diferentes de IDs:
* PID: es un valor único que tiene cada proceso para poder ser identificado,
siendo reutilizable una vez haya terminado.
* PPID: (Parent Process ID) es el PID del proceso padre. Si se va el proceso
padre antes que el hijo, este último probablemente adquiera un PPID de 1.
* PGID: es equivalente al PID del líder de un grupo. Si el PID es igual al
PGID, entonces es el líder del grupo.
* SID: es el PID del proceso líder de una sesión. Lo mismo, si PID=SID, es el
líder de la sesión.
     Tanto las sesiones como los grupos son formas de manejar un conjunto de
procesos como una sola unidad. Lo que pasa es que así como todos los miembros
de un grupo pertenecen a la misma sesión, una sesión puede tener varios
grupos de procesos.

21.4 ESTADOS
     Cada servicio se va a encontrar en uno de estos estados:
* Running (R): el CPU está ejecutándolo.
* Sleeping (S): el proceso está esperando a que el usuario ingrese
información, o a que pase cierto evento, o a que algún recurso esté
disponible.
* Disk Sleep (D): es un proceso ininterrumpible a diferencia de los que están
en "S", y significa que está esperando a que el kernel (que maneja el
hardware) termine ciertas operaciones.
* Stopped (T): el proceso se detuvo, dándole más que nada por una señal.
* Zombie (Z): el proceso hijo, al cumplir su tarea, espera a la función Wait()
de su padre para obtener el código de salida de su hijo, pero si el padre no
usa Wait(), el proceso hijo queda en este estado, significando que está
ocupando un pequeño espacio de memoria. En otras palabras, es cuando el
proceso padre no termina de reconocer bien el hecho de que un proceso hijo
terminó.
* Dead (X): un estado puesto justo antes de que un proceso se desactive por
completo.
* Idle (I): quiere decir que es un proceso inactivo del kernel.
     Estos estados pueden estar acompañados de otros símbolos:
* < indica que el proceso es de alta prioridad.
* N indica lo contrario a "<".
* L 
* s
* l 

21.5 COMANDOS
- ps [options] [pattern]: lista los procesos del sistema con información
adicional dividida en columnas. De manera predeterminada solo lista los
procesos asociados al usuario y a su terminal (no tiene en cuenta a los
procesos hijos).
     A continuación van a ver opciones que no tienen el "-" detrás, y eso
está bien, pero si la queremos usar en una sola línea, hay que usarlas por
separado, con esto quiero decir que si por ejemplo queremos usar "a" y "-H",
vamos a tener que escribir:
$ ps a -H

 (Ambos estilos no siempre son combinables)

+  a: lista todos los procesos asociados a una terminal (tty).
+  u: es como la opción anterior, pero con más detalles sobre los procesos.
+  x: lista todos los procesos asociados con el usuario registrado.
+ -e: lista todos los procesos del sistema.
+ --forest: ordena los procesos según su jerarquía, en formato árbol.
+ -o [format]: nos permite listar los procesos con el formato que queramos.
Varias de las opciones totales pueden ser:
* %mem: uso de memoria.
* %cpu: qué tanto CPU está utilizando.
* comm: muestra el nombre del ejecutable del proceso.
* args: parecido al anterior, pero también muestra los argumentos usados.
* cputime: cuánto tiempo el proceso lleva en el CPU en formato "hh:mm:ss".
* pid: bueno, no sé qué va a mostrar.
* ppid: el PID del proceso padre.
* stat: el estado del proceso.
* pri el número de prioridad que tiene el proceso (más abajo está
explicado).
* tty: terminal bajo la cual está el proceso.
* user: el usuario que llevó a cabo el proceso.
+ -p [pid]: imprime el proceso con el pid especificado. 
+ -u [user/s]: imprime los procesos llevados a cabo por el o los usuarios
especificados (separados por ","). 
- pstree [options] [user/pid]: lista los procesos en forma jerárquica. De
manera predeterminada, los procesos hijos repetidos, aparecerán como uno solo,
entre corchetes, llaves, y acompañado de un número y el signo "*" según la
cantidad.
+ -c: desactiva el formato anteriormente mencionado.
+ -p: muestra los PIDs. También desactiva el formato de "n*[{process}]".
+ -s [pid]: muestra cada proceso padre del proceso especificado, hasta llegar
al primer proceso del sistema.
- kill [options] [pid]: termina el proceso que tenga el pid escrito.
+ -l 'signal': si ponemos un valor (numérico o textual) que corresponda a una
señal, muestra su equivalente. A secas lista todas las posibles señales.
+ -'signal': (o "-s 'signal'") aclara la señal a usar con el proceso, ya sea su
valor numérico o textual (sacando SIG) (valor predeterminado: 15 (SIGTERM)).
     Este comando admite un PID especial de un valor de -1, diciéndole que
acabe con todos los procesos que pueda, a excepción del init y el proceso en
sí.
- pkill [options] pattern: elimina los procesos que coincidan con el patrón.
     Al igual que el comando "kill", la señal predeterminada es SIGTERM,
teniendo que usar "-" o "-s" seguido de una señal si es que queremos cambiarla.
 
21.6 BACKGROUND
     Muchísimos procesos se ejecutan en segundo plano para que el usuario
pueda hacer sus tareas tranquilamente. Un proceso en primer plano, o
"foreground", es por ejemplo "find", pero si al final del comando y sus
parámetros añadimos "&", se va ejecutar en segundo plano.
     También, cuando aplicamos Ctrl-Z a cierto comando, este se detiene y
queda en segundo plano.
- bg [pid]: resume el proceso especificado que fuedetenido con Ctrl-Z pero lo
deja en segundo plano. Sin un PID aclarado, toma el último proceso que fue
detenido.
- fg [pid]: lleva un proceso de segundo a primer plano. También toma el
último proceso si no se especifica un PID.
- jobs: lista los procesos puestos en segundo plano en la actual sesión de
la shell. Podemos notar que si hacemos por ejemplo algo como:
$ sleep 120 &

     y lo repetimos tres veces, al usar este comando vamos a ver que los
procesos listados, delante del número, o hay un "+", o un "-", o nada. Si hay
un "+" significa que ese proceso va a ser tomado por "fg" o bg" si no se
especifica ningún PID, mientras que "-" sería el penúltimo.

21.7 PRIVILEGIO
     Los procesos siempre van a tener cierto nivel de privilegio. permitiendo
que el kernel sepa a cuál darle más recursos. Los niveles van desde el -20
(mayor prioridad) hasta el 19 (menor prioridad) ¿Por qué un número negativo
indica la prioridad más alta? Porque tenían ganas de romper los huevos un
rato.

- nice -n [cmd]: sirve para iniciar un nuevo proceso con una prioridad
determinada. El número "n" va a estar si o sí antecedido de un guión medio
"-", y si es negativo, nomás añadís otro. 
- renice -n 'priority' [options]: cambia la prioridad de un proceso ya en
ejecución.
+ -p [pid]: solamente cambia el proceso con el PID especificado.
+ -g [gid]: tiene en cuenta los procesos que formen parte del grupo con el GID
puesto.
+ -u [uid]: afecta a los procesos pertenecientes al usuario con UID aclarado.
	
     En realidad no termina acá, de hecho se complica un poco. En Linux hay
dos tipos de procesos: los de tiempo real (realtime) y los normales. Los de
tiempo real tienen mucha más prioridad que los normales ya que son procesos
que requieren ejecución inmediata, como el de los controladores, por ejemplo.
Linux tiene una escala de permisos que va desde 0 a 139, dejando el pedazo de
100 a 139 para los normales (notar que es el mismo rango anteriormente
mencionado pero con 120 sumados). Resulta que no solo existe el valor nice,
sino que cada proceso tiene más de un tipo de prioridad que linux combina con
nice para después ahí obtener el "verdadero" nivel de prioridad. Pero ahora
solo vamos a enfocarnos en dos: NI y PR.
     Lo primero que hay que saber es que los procesos en tiempo real, mientras
mayor el valor de NI, mayor la propiedad, todo lo contrario a los procesos
normales.
     PR, en los procesos normales, es el resultado de 20 + NI (NI es nice).
Mientras que en los de tiempo real, PR = -1 - real_time_priority (de 1 a 99).
     Si quisieramos ver el valor de real_time_priority, con el comando "ps", la
opción "-o" permite un argumento llamado "rtprio".
     Asi que al ejecutar el comando de la siguiente sección, PR está entre
0 y 39, es un proceso normal, pero si por ejemplo tiene un valor de -51, o rt,
(que es lo mismo que -100) es de tiempo real.
     Entonces, en general, PR va a tener un valor de entre -100 y 39, y
mientras menor el número, más prioridad.

21.4.1 COMANDO TOP
- top [options]: este comando muestra en tiempo real a los procesos y sus
características, pudiendo manejarlos y modificarlos. 
     Cuando estemos en el programa, hay ciertas teclas que al presionarlas nos
van a permitir aplicar ciertos filtros, tanto mayúsculas como minúsculas.
     Explicar todo lo que puede hacer es un poco al pedo ya que si presionamos
"h" va a aparecer un menú de ayuda bastante fácil de entender.
