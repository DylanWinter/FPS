#pragma once
#include "SDL.h"
#include "utils.h"

const float moveSpeed = 0.1f;
const float rotSpeed = 0.05f;

Vector2 getDirection(const Uint8* keyState);
float getRotation(const Uint8* keyState);

