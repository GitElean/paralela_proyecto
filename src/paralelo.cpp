// paralelo.cpp
#include "paralelo.h"
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <iostream>
#include <random> 
#include <SDL2/SDL.h>
#include "SDL2_gfxPrimitives.h"

ParallelScreenSaver::ParallelScreenSaver(int width, int height, int num_circles) 
    : window_width(width), window_height(height), n(num_circles), num_threads(4) { // Default 4 threads

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Screen Saver",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              window_width, window_height,
                              0);

    renderer = SDL_CreateRenderer(window, -1, 0);

    circles = new Circle[n];
    initializeCircles();
}

ParallelScreenSaver::~ParallelScreenSaver() {
    delete[] circles;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void ParallelScreenSaver::initializeCircles() {
    std::mt19937 gen(static_cast<unsigned long>(time(nullptr)));
    std::uniform_int_distribution<int> dist_pos_x(0, window_width);
    std::uniform_int_distribution<int> dist_pos_y(0, window_height);
    std::uniform_int_distribution<int> dist_radius(0, 50);
    std::uniform_int_distribution<int> dist_velocity(-2, 2);
    std::uniform_int_distribution<int> dist_color(0, 255);

    for (int i = 0; i < n; i++) {
        circles[i].x = dist_pos_x(gen);
        circles[i].y = dist_pos_y(gen);
        circles[i].radius = dist_radius(gen);
        circles[i].velocity_x = dist_velocity(gen);
        circles[i].velocity_y = dist_velocity(gen);
        circles[i].color.r = dist_color(gen);
        circles[i].color.g = dist_color(gen);
        circles[i].color.b = dist_color(gen);
    }
}

void ParallelScreenSaver::setNumThreads(int threads) {
    num_threads = threads;
    omp_set_num_threads(num_threads);
}

Uint32 ParallelScreenSaver::calculateFPS(Uint32 start_time) {
    Uint32 current_time = SDL_GetTicks();
    Uint32 elapsed_time = current_time - start_time;
    return 1000 / elapsed_time;
}

void ParallelScreenSaver::moveCircles() {
    #pragma omp parallel for num_threads(num_threads) default(none) shared(circles, n)
    for (int i = 0; i < n; i++) {
        Circle &currentCircle = circles[i];  // Referencia al círculo actual

        // Prever colisiones en el eje X
        if (currentCircle.x + currentCircle.velocity_x - currentCircle.radius < 0 ||
            currentCircle.x + currentCircle.velocity_x + currentCircle.radius > window_width) {
            currentCircle.velocity_x = -currentCircle.velocity_x;
        }

        // Prever colisiones en el eje Y
        if (currentCircle.y + currentCircle.velocity_y - currentCircle.radius < 0 ||
            currentCircle.y + currentCircle.velocity_y + currentCircle.radius > window_height) {
            currentCircle.velocity_y = -currentCircle.velocity_y;
        }

        // Mover el círculo
        currentCircle.x += currentCircle.velocity_x;
        currentCircle.y += currentCircle.velocity_y;
    }
}

void ParallelScreenSaver::drawCircles() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Set white background color
    SDL_RenderClear(renderer);

    for (int i = 0; i < n; i++) {
        filledCircleRGBA(renderer, circles[i].x, circles[i].y, circles[i].radius, 
                         circles[i].color.r, circles[i].color.g, circles[i].color.b, 255); // <-- Usando SDL2_gfx para dibujar círculos
    }

    SDL_RenderPresent(renderer);
}

void ParallelScreenSaver::run() {
    SDL_Event event;
    int running = 1;
    int frameCount = 0;

    while (running) {
        Uint32 start_time = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        moveCircles();
        drawCircles();

        SDL_Delay(10);
        frameCount++;

        if (frameCount % 100 == 0) {
            Uint32 fps = calculateFPS(start_time);
            std::cout << "FPS: " << fps << std::endl;
        }
    }
}
