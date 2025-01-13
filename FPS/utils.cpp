#pragma once
#include "utils.h"
#include "SDL.h"
#include <vector>

const SDL_Color BLUE = { 0, 255, 255, 255 };
const SDL_Color YELLOW = { 255, 255, 0, 255 };
const SDL_Color RED = { 255, 0, 0, 255 };
const SDL_Color GREEN = { 0, 255, 0, 255 };
const SDL_Color GREY = { 128, 128, 128, 255 };
const SDL_Color BLACK = { 0, 0, 0, 255 };

const std::vector<SDL_Color> colors = { BLACK, GREY, RED, BLUE, GREEN, YELLOW };