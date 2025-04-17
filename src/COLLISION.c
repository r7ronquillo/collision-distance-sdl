#include "../include/COLLISION.h"

/* POINT COLLISION WITH FRect */
int PointCollision(const float pointX, const float pointY, const SDL_FRect* collider) {
	if ((pointX >= collider->x) &&
		(pointX <= (collider->x + collider->w)) &&
		(pointY >= collider->y) &&
		(pointY <= (collider->y + collider->h))) {
		return 1;
	}
	return 0;
}

/* BOX COLLISION BETWEEN TWO FRect */
int BoxCollision(const SDL_FRect* collider, const SDL_FRect* other) {
	if (((other->x + other->w) >= collider->x) &&
		(other->x <= (collider->x + collider->w)) &&
		((other->y + other->h) >= collider->y) &&
		(other->y <= (collider->y + collider->h))) {
		return 1;
	}
	return 0;
}