##### ¿Qué es particionar?
Es básicamente como **cortar un pastel** (el dispositivo físico de almacenamiento que sea) en varias partes en las que se va a guardar cierta información. Esto sirve para varias cosas, como que los datos estén más organizados, o instalar más de un sistema operativo en una misma computadora, recuperación de datos, y más. Por ejemplo, en Windows, la unidad C: es una partición, y en Linux no encontramos con sda o nvme0n1.

###### Tipos de particiones
* **Primarias**: son las particiones que **arrancan el sistema**. Por eso, si hay más de un sistema operativo, la máquina se dirige a un gestor de arranque, o **BIOS** (Basic I/O System) para poder elegir qué sistema operativo iniciar.
* **Extendidas**: estas se pueden subdividir en particiones lógicas, que es solamente otra partición más. Pero ninguna de las dos son reconocidas por el BIOS, ya que más que nada sirven para **organizar datos**.

###### Esquema de particiones MBR y GPT
Antes de las particiones, están los esquemas de particiones. Hoy en día los más conocidos son MBR (Master Boot Record) y uno mucho más nuevo: GPT (GUID Partition Table).
Resulta que MBR solo permite 4 particiones primarias, o 3 primarias y una extendida. Es vieja (de los 80's), y por eso es funcional con sistemas operativos antiguos y BIOS (solamente BIOS). y tiene una limitación de 2 TB.
GPT arrasa a MBR al permitir un número ilimitado de particiones y soportar una muchísimo mayor capacidad que 2 TB. También cabe destacar que es compatible con el gestor de arranque UEFI (Unified Extensible Firmware Interface) que reemplaza al antiguo BIOS.

###### ¿Qué es un sistema de archivos (*filesystem*)?
Cada partición, sea primaria, extendida, o lógica, cuenta sí o sí con un sistema de archivos, que vendría a ser el conjunto de **reglas y estructuras** que permiten **organizar y manipular la información** que sea que haya en el almacenamiento.

###### ¿Por qué existen diferentes *filesystem*?
Porque cada uno está hecho para cumplir ciertas necesidades. Algunos se centran en la rápidez, otros en la robustez y la seguridad, otros en la capacidad de almacenamiento, y así. Hay una buena cantidad también debido a que cada sistema operativo tiene sus propios filesystems.
