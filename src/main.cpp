#include "secuencial.h"
#include "paralelo.h"

int main(int argc, char *argv[]) {
    //ScreenSaver saver(640, 480, 50);
    //saver.run();


    int num_threads = 8;  // Puedes establecer un valor predeterminado

    // Si se proporciona un argumento, usarlo como número de hilos
    if (argc > 1) {
        num_threads = std::stoi(argv[1]);
    }

    ParallelScreenSaver saverP(640, 480, 50);
    saverP.setNumThreads(num_threads);
    saverP.run();

    return 0;
}
