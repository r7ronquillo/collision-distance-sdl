#include "../include/DISTANCE.h"
#include <math.h>

/* DISTANCE BETWEEN TWO POINTS */
float DistanceBetweenPoints(float xA, float yA, float xB, float yB) {

	/* DIFFERENCE BETWEEN X's AND Y's POSITION */
	float xd = xA - xB;
	float xy = yA - yB;

	/* RETURN HYPOTENUSE */
	return sqrt(xd * xd + xy * xy);
}

/* DISTANCE BETWEEN TWO FRect */
float DistanceBetweenFRect(const SDL_FRect* rectA, const SDL_FRect* rectB) {

	/* rectA CENTER X AND Y POSITION */
	float rectACenterX = rectA->x + (rectA->w * 0.5f);
	float rectACenterY = rectA->y + (rectA->h * 0.5f);

	/* rectB CENTER X AND Y POSITION */
	float rectBCenterX = rectB->x + (rectB->w * 0.5f);
	float rectBCenterY = rectB->y + (rectB->h * 0.5f);

	/* DIFFERENCE BETWEEN X's AND Y's POSITION */
	float xd = rectACenterX - rectBCenterX;
	float yd = rectACenterY - rectBCenterY;

	/* RETURN HYPOTENUSE */
	return sqrt(xd * xd + yd * yd);
}