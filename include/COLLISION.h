#pragma once
#include <SDL3/SDL.h>

/* POINT COLLISION WITH FRect */
int PointCollision(const float pointX, const float pointY, const SDL_FRect* collider);

/* BOX COLLISION BETWEEN TWO FRect */
int BoxCollision(const SDL_FRect* collider, const SDL_FRect* other);