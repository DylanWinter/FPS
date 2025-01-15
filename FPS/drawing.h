#pragma once
#include "SDL.h"
#include "utils.h"
#include "map.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int TOPDOWN_WIDTH = 400; 
const int TOPDOWN_HEIGHT = 400;

void drawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius, SDL_Color color, bool filled = true);
void drawWall(SDL_Renderer* renderer, int x, int height, SDL_Color color);
void drawTopDown(SDL_Renderer* renderer, Player player);