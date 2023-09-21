#include "secuencial.h"
#include "paralelo.h"

int main(int argc, char *argv[]) {
    //ScreenSaver saver(640, 480, 50);
    //saver.run();


    int num_threads = 2;  // Puedes establecer un valor predeterminado

    // Si se proporciona un argumento, usarlo como número de hilos
    if (argc > 1) {
        num_threads = std::stoi(argv[1]);
    }

    ParallelScreenSaver saver(640, 480, 50);
    saver.setNumThreads(num_threads);
    saver.run();

    return 0;
}
