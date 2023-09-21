# paralela proyecto Screen Saver

## Authors: Elean Rivas, Diego Ruiz

El proyecto plantea ser un screen saver generado de forma paralela

### Requisitos para compilar:
- compilador GNDU de C++(g++, ninja, etc)
- SDL2
- OpenMP
- Cmake v3.22
- time


### How to run
Para ejecutar el programa solo es necesario ejecutar el script run.sh de la siguiente manera ./run.sh

Esto nos brindará un menú para correr el programa de forma secuencial (1), de forma paralela (2) y salir (3). 
Al elegir correr de forma secuencial y paralela podremos definir el número de círculos.
Al elegir exclusivamente de forma parelal podremos definir el número de threads a utilizar.

### Funcionalidad de los scripts
configure: configuración de Cmake
build: buildea el programa
run: compila y corre el programa usando los scripts configure, build
clean: limpia el build en caso de ser necesario

### Trouble Shooting
En caso de no tener las librerias ejecute los siguientes comandos(Debian)
sudo apt-get install libsdl2-dev libomp-dev
sudo apt install cmake

En caso de no tener permisos para ejecutar los .sh ejecutar los siguientes comandos
chmod +x configure.sh
chmod +x build.sh
chmod +x run.sh
chmod +x clean.sh

### Referencias
https://github.com/denn1s/CC3096
https://documentation.help/SDL/index.html
