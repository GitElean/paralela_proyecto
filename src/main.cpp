#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int r;
    int g;
    int b;
} Color;

typedef struct {
    int x;
    int y;
    int radius;
    int velocity_x;
    int velocity_y;
    Color color;
} Circle;

    int window_width = 640;
    int window_height = 480;

int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);



    SDL_Window *window = SDL_CreateWindow("Screen Saver",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          window_width, window_height,
                                          0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Color background_color;
    background_color.r = 255;
    background_color.g = 255;
    background_color.b = 255;

    int n = 5; // Número de círculos
    Circle circles[n];

    // Inicializar la semilla de números aleatorios
    srand(time(NULL));

    // Inicializar los círculos con posiciones, velocidades y colores aleatorios
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

    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Mover y dibujar cada círculo
        for (int i = 0; i < n; i++) {
            // Mover el círculo
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

        // Limpiar la pantalla
        SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 255);
        SDL_RenderClear(renderer);

        // Dibujar cada círculo
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

        // Presentar el renderer
        SDL_RenderPresent(renderer);

        // Esperar un poco
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
