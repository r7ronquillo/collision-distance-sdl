#pragma once
#include <SDL3/SDL.h>

/* DISTANCE BETWEEN TWO POINTS */
float DistanceBetweenPoints(float xA, float yA, float xB, float yB);

/* DISTANCE BETWEEN TWO FRect */
float DistanceBetweenFRect(const SDL_FRect* rectA, const SDL_FRect* rectB);