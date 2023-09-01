#include <iostream>
#include <SDL2/SDL.h>
using namespace std;


typedef struct {
    int r;
    int g;
    int b;
} Color;

int window_width = 640;
int window_height = 480;

int main() {
  cout << "Hello World!";
      SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Ventana de ejemplo",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          window_width, window_height,
                                          0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Color color;
    color.r = 200;
    color.g = 200;
    color.b = 0;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255); // Color de fondo

    SDL_RenderClear(renderer); // Llena la ventana con el color de fondo

    SDL_RenderPresent(renderer); // Muestra el color de fondo en la ventana

    Color circle_color;
    circle_color.r = 255;
    circle_color.g = 0;
    circle_color.b = 0;

    int circle_radius = 50;
    int circle_x = window_width / 2;
    int circle_y = window_height / 2;
    int circle_velocity_x = 20;
    int circle_velocity_y = 20;

    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Move the circle
        circle_x += circle_velocity_x;
        circle_y += circle_velocity_y;

        // Check for collision with the edges of the window
        if (circle_x - circle_radius < 0 || circle_x + circle_radius > window_width) {
            circle_velocity_x = -circle_velocity_x;
        }

        if (circle_y - circle_radius < 0 || circle_y + circle_radius > window_height) {
            circle_velocity_y = -circle_velocity_y;
        }

        // Clear the screen
        //SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 255);
        //SDL_RenderClear(renderer);

        // Draw the circle
        SDL_SetRenderDrawColor(renderer, circle_color.r, circle_color.g, circle_color.b, 255);

        for (int w = 0; w < circle_radius * 2; w++) {
            for (int h = 0; h < circle_radius * 2; h++) {
                int dx = circle_radius - w;
                int dy = circle_radius - h;
                if ((dx*dx + dy*dy) <= (circle_radius * circle_radius)) {
                    SDL_RenderDrawPoint(renderer, circle_x + dx - circle_radius, circle_y + dy - circle_radius);
                }
            }
        }

        // Present the renderer
        SDL_RenderPresent(renderer);

        // Wait for a little bit
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
