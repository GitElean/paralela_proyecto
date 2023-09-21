#include "secuencial.h"
#include "paralelo.h"
#include <iostream>

int main(int argc, char *argv[]) {


    char answer;
    int circles;
    int num_threads = 8;
    bool verf = false;

    while (answer!='3') {
    std::cout << "Elija una opción: \n 1. Ejecutar programa secuencial. \n 2. Ejecutar programa paralelo \n 3. Salir" << std::endl;
    std::cin >> answer;
    if (answer=='1') {
        verf = false;
        while(verf == false){
            std::cout << "Ingrese la cantidad de círculos" << std::endl;
            std::cin >> circles;
                // Comprobar si la entrada fue válida y si el número es positivo
            if (std::cin.fail() || circles <= 0) {
                std::cout << "¡Entrada no válida! Por favor, introduce un entero positivo." << std::endl;
            } else {
                    ScreenSaver saver(640, 480, circles);
                    saver.run();
                    verf = true;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        }
    } else if (answer=='2') {
        verf = false;
        while(verf == false){
            std::cout << "Ingrese la cantidad de círculos" << std::endl;
            std::cin >> circles;
                // Comprobar si la entrada fue válida y si el número es positivo
            if (std::cin.fail() || circles <= 0) {
                std::cout << "¡Entrada no válida! Por favor, introduce un entero positivo." << std::endl;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Ingrese la cantidad de threads" << std::endl;
            std::cin >> num_threads;
            if (std::cin.fail() || num_threads <= 0) {
                std::cout << "¡Entrada no válida! Por favor, introduce un entero positivo." << std::endl;
            }else{
                    ParallelScreenSaver saverP(640, 480, 50);
                    saverP.setNumThreads(num_threads);
                    saverP.run();
                    verf = true;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
        }
    } else if (answer=='3'){
        std::cout << "Gracias por usar el sistema" << std::endl;
        exit(0);
    } else{
        std::cout << "Escoja una opción válida" << std::endl;
    }
}


    return 0;
}
