#pragma once
#include <vector>
#include <SDL.h> 

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    Vector2 position;
    float angle;
} Player;

extern const SDL_Color BLUE;
extern const SDL_Color YELLOW;
extern const SDL_Color RED;
extern const SDL_Color GREEN;
extern const SDL_Color GREY;
extern const SDL_Color BLACK;

extern const std::vector<SDL_Color> colors;