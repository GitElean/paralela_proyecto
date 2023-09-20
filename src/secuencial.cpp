// secuencial.cpp
#include "secuencial.h"
#include <stdlib.h>
#include <time.h>

ScreenSaver::ScreenSaver(int width, int height, int num_circles) 
    : window_width(width), window_height(height), n(num_circles) {

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

ScreenSaver::~ScreenSaver() {
    delete[] circles;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void ScreenSaver::initializeCircles() {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        circles[i].x = rand() % window_width;
        circles[i].y = rand() % window_height;
        circles[i].radius = rand() % 50;
        circles[i].velocity_x = rand() % 5 - 2;
        circles[i].velocity_y = rand() % 5 - 2;
        circles[i].color.r = rand() % 256;
        circles[i].color.g = rand() % 256;
        circles[i].color.b = rand() % 256;
    }
}

Uint32 ScreenSaver::calculateFPS(Uint32 start_time) {
    Uint32 current_time = SDL_GetTicks();
    Uint32 elapsed_time = current_time - start_time;
    return 1000 / elapsed_time;
}

void ScreenSaver::moveCircles() {
    for (int i = 0; i < n; i++) {
        circles[i].x += circles[i].velocity_x;
        circles[i].y += circles[i].velocity_y;

        // Comprobar si el círculo choca con los bordes de la ventana
        if (circles[i].x - circles[i].radius < 0 || circles[i].x + circles[i].radius > window_width) {
            circles[i].velocity_x = -circles[i].velocity_x;
        }

        if (circles[i].y - circles[i].radius < 0 || circles[i].y + circles[i].radius > window_height) {
            circles[i].velocity_y = -circles[i].velocity_y;
        }
    }
}
void ScreenSaver::drawCircles() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Color de fondo blanco
    SDL_RenderClear(renderer);

    for (int i = 0; i < n; i++) {
        SDL_SetRenderDrawColor(renderer, circles[i].color.r, circles[i].color.g, circles[i].color.b, 255);

        for (int w = 0; w < circles[i].radius * 2; w++) {
            for (int h = 0; h < circles[i].radius * 2; h++) {
                int dx = circles[i].radius - w;
                int dy = circles[i].radius - h;
                if ((dx*dx + dy*dy) <= (circles[i].radius * circles[i].radius)) {
                    SDL_RenderDrawPoint(renderer, circles[i].x + dx - circles[i].radius, circles[i].y + dy - circles[i].radius);
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
}


void ScreenSaver::run() {
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
