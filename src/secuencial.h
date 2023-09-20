// secuencial.h
#ifndef SECUENCIAL_H
#define SECUENCIAL_H

#include <SDL2/SDL.h>
#include <iostream>

class ScreenSaver {
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
    ScreenSaver(int width, int height, int num_circles);
    ~ScreenSaver();
    void run();
};

#endif // SECUENCIAL_H
