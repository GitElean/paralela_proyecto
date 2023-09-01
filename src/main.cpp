#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

int main() {
  cout << "Hello World!";
      SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Ventana de ejemplo",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480,
                                          0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 200, 200, 0, 255); // Color de fondo

    SDL_RenderClear(renderer); // Llena la ventana con el color de fondo

    SDL_RenderPresent(renderer); // Muestra el color de fondo en la ventana

        SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                running = 0;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

  return 0;
}