#include "SDL.h"
#include "utils.h"
#include "input.h"

// gets direction from keyboard
Vector2 getDirection(const Uint8* keyState) {
    Vector2 dir = { 0, 0 };
    if (keyState[SDL_SCANCODE_W]) {
        dir.y = -1;
    }
    if (keyState[SDL_SCANCODE_S] && !keyState[SDL_SCANCODE_W]) {
        dir.y = 1;
    }
    if (keyState[SDL_SCANCODE_A]) {
        dir.x = -1;
    }
    if (keyState[SDL_SCANCODE_D] && !keyState[SDL_SCANCODE_A]) {
        dir.x = 1;
    }

    return dir;
}

float getRotation(const Uint8* keyState) {
    if (keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_RIGHT]) {
        return -rotSpeed;
    }
    else if (!keyState[SDL_SCANCODE_LEFT] && keyState[SDL_SCANCODE_RIGHT]) {
        return rotSpeed;
    }
    else {
        return 0;
    }
}