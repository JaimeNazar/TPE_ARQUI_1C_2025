## **Manual**

### Dependencias  

Para poder compilar el kernel basado en **x64BareBones** es necesario tener instalados los siguientes programas: **gcc**, **make,** y **ld.** Ya sea en linux corriendo localmente o en una máquina virtual. Opcionalmente, se puede utilizar **docker** para poder compilar utilizando un contenedor con la imagen con la que fue compilado el kernel durante el desarrollo(agodio/itba-so:2.0), viene con las dependencias pre-instaladas.

### Instalación  

Primero, clonar el repositorio de github con el siguiente comando:
```
git clone https://github.com/JaimeNazar/TPE\_ARQUI\_1C\_2025
```
o simplemente usando la aplicación de escritorio de git o alguna de sus variantes. Debe estar en un directorio visible para el contenedor de docker en caso de que se haya elegido esa opción.

### Compilación  

En caso de estar corriendo linux localmente, simplemente se debe ejecutar el comando **make** en el directorio clonado anteriormente. En caso de estar usando docker:

```
docker start $NAME
docker exec \-it $NAME make clean \-C /root/Toolchain/  
docker exec \-it $NAME make clean \-C /root/  
docker exec \-it $NAME make \-C /root/Toolchain/  
docker exec \-it $NAME make \-C /root/
```

Donde **$NAME** es el nombre del contenedor, notar que en este ejemplo se requieren de permisos root, pero es posible configurar un usuario dentro del contenedor para poder ejecutar como usuario normal.

### Modo de uso  

El proyecto puede ser probado tanto en un emulador(qemu, virtualBox) o en hardware real. Por ejemplo, para correrlo con qemu: 

```
qemu-system-x86\_64 \-hda Image/x64BareBonesImage.qcow2 \-m 512
```

Puede ocurrir que el sonido no funcione, en ese caso agregar los argumentos: **\-audiodev sdl,id=audio0 \-machine pcspk-audiodev=audio0,** el comando quedaría de la siguiente manera: 

```
qemu-system-x86\_64 \-hda Image/x64BareBonesImage.qcow2 \-m 512 \-audiodev sdl,id=audio0 \-machine pcspk-audiodev=audio0
```

Por otro lado, si se quiere probar en hardware, se deberá crear una memoria USB booteable y tener disponible una computadora que soporte BIOS o legacy(compatibilidad con CSM). Por ejemplo, en linux: 

```
sudo dd if=./x64BareBonesImage.img of=/dev/sdd status=progress
```

Creará una memoria USB ejecutable con la imagen compilada anteriormente, en este caso el USB esta en **/dev/sdd**, se puede obtener en que **/dev/**  esta una memoria usb con el siguiente comando:  

```
sudo fdisk \-l
```

### Lista de Comandos

los siguientes comandos están implementados en la terminal miniShell:

| Comandos | Cantidad de argumentos válidos |
| ----- | ----- |
| **help** | **0** |
| **clear** | **0** |
| **sleep** | **1** |
| **game** | **1** |
| **time** | **0** |
| **beep** | **2** |
| **ticks** | **0** |
| **echo** | **máximo 15** |
| **registers** | **0** |
| **font-size** | **1** |
| **zero-division** | **0** |
| **undefined-op-code** | **0** |

Como se muestra en la tabla, cada comando implementado tiene una cantidad de argumentos válidos, si no se escriben la cantidad necesaria, la terminal mostrará un error en pantalla. Además para el correcto llamado de estos comandos es necesario escribirlos como se muestran, ya que que la terminal es “case sensitive”.

 A continuación se detallaran los comandos. Tener en cuenta que los argumentos se separan con la tecla espacio (“ ”).

### Instructivo de Comandos

**help**: Muestra en pantalla un listado de todos los comandos junto con una breve descripción de los mismos.

**clear**: Limpia todos los caracteres de la terminal.

**sleep**: Pone al sistema a dormir por una cantidad de ticks marcada por el usuario.

**game**: Comienza el juego, escribir como argumento 1 o 2 dependiendo de la cantidad de jugadores con los que se quiera jugar.

**time**: Muestra en pantalla el horario actual de la zona horaria de Argentina con el formato “Current time: HORAS : MINUTOS : SEGUNDOS”

**beep**: Emite un sonido con una frecuencia y duración, en ticks, marcada por el usuario.

**ticks**: Muestra en pantalla los ticks que sucedieron desde el inicio del programa. 

**echo:** Muestra en pantalla los argumentos que escribió el usuario, hasta un máximo de 15 argumentos.

**registers:** Muestra en pantalla los valores de los registros del procesador a la hora de escribir el comando.

**font-size:** Cambia el tamaño de letra de la terminal, el tamaño pasado como argumento tendrá que ser un número mayor o igual 8 y menor que 25\.

**zero-division:** Muestra en pantalla la excepción que ocurre cuando se divide un número por 0\.

**undefined-op-code:** Muestra en pantalla la excepción que ocurre cuando un código de operación es invalido.

### Errores Posibles:

Pueden haber tres posibles errores al escribir un comando:

1. Comando invalido: El comando no esta implementado  
2. Cantidad de argumentos invalida: Faltan o sobran argumentos.  
3. Argumento invalido: El o los argumentos no son aceptados.

### Pongis In Space:

Para poder jugar al Pongis In Space, se tendrá que ejecutar el comando “game”, con un “1” o un “2” como argumento dependiendo de la cantidad de jugadores que se quiera tener.

Para mover al jugador 1 se usan los controles WASD y para el jugador 2 se usa IJKL. Cada jugador tendrá 5 vidas y cada vez que le den un golpe a la pelota, el jugador perderá una vida.

Para ganar, se necesitara meter el meteorito al agujero negro antes de que cualquiera de los jugadores se quede sin vida. Una vez que algún jugador se quede sin vidas, el meteorito se tendrá que quedar quieto para que termine la partida en un game over. 

Para salir del juego, se necesita ganar/perder la partida o al apretar la tecla backspace. También, al apretar la tecla r se mostrarán los registros del procesador en pantalla

### Ejemplos de comandos:

`help`

`game 1`

`font-size 20`

`ticks`

`echo Hola mundo!`

`beep 400 50`
