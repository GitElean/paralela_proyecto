// paralelo.h
#ifndef PARALELO_H
#define PARALELO_H

#include <SDL2/SDL.h>

class ParallelScreenSaver {
private:
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

    int num_threads;
    int window_width;
    int window_height;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Circle *circles;
    int n;

    Uint32 calculateFPS(Uint32 start_time);
    void initializeCircles();
    void moveCircles();
    void drawCircles();

public:
    ParallelScreenSaver(int width, int height, int num_circles);
    ~ParallelScreenSaver();
    void run();
    void setNumThreads(int threads);
};

#endif // PARALELO_H
