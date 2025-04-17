/* USE CALLBACKS INSTEAD OF MAIN FUNCTION */
#define SDL_MAIN_USE_CALLBACKS 1

#include "../include/COLLISION.h"
#include "../include/DISTANCE.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 720;

static SDL_Window* WINDOW = NULL;
static SDL_Renderer* RENDERER = NULL;

static float MOUSE_X = 0.0f;
static float MOUSE_Y = 0.0f;

static SDL_FRect* rectA = NULL;
static SDL_FRect* rectB = NULL;

static int rectSize = 125;
static int isColliding = 0;
static int isFollowingMouse = 1;

static int rectACenterX = 0;
static int rectACenterY = 0;
static int rectBCenterX = 0;
static int rectBCenterY = 0;

static float DISTANCE_XD = 0.0f;
static float DISTANCE_YD = 0.0f;

static float DISTANCE_MOUSE = 0.0f;
static float DISTANCE_FRect = 0.0f;

static float TEXT_OFFSET_X = 50.0f;

/* THIS FUNCTION RUNS ONCE AT START UP */
SDL_AppResult SDL_AppInit(void** appState, int argc, char* argv[]) {

	/* START SDL VIDEO */
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialze SDL: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	/* CREATE WINDOW AND RENDERER */
	if (!SDL_CreateWindowAndRenderer("CollisionDistanceSDL", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &WINDOW, &RENDERER)) {
		SDL_Log("Could not create window/renderer SDL: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	/* ALLOCATE MEMORY FOR rectA AND rectB */
	rectA = malloc(sizeof(SDL_FRect));
	rectB = malloc(sizeof(SDL_FRect));
	if (!rectA || !rectB) {
		SDL_Log("Could not allocate FRect\n");
		return SDL_APP_FAILURE;
	}

	// INITIALIZE rectA PROPERTIES
	rectA->x = (WINDOW_WIDTH * 0.5f) - (rectSize * 0.5f);
	rectA->y = (WINDOW_HEIGHT * 0.5f) - (rectSize * 0.5f);
	rectA->w = rectSize;
	rectA->h = rectSize;

	// INITIALIZE rectB PROPERTIES
	rectB->x = MOUSE_X;
	rectB->y = MOUSE_Y;
	rectB->w = rectSize;
	rectB->h = rectSize;

	/* CONTINUE PROGRAM */
	return SDL_APP_CONTINUE;
}

/* THIS FUNCTION RUNS ONCE PER FRAME */
SDL_AppResult SDL_AppIterate(void* appState) {

	/* SET BACKGROUND COLOR: BLACK */
	SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 255);

	/* DRAW BACKGROUND */
	SDL_RenderClear(RENDERER);

	/* rectA CENTER X AND Y POSITION */
	rectACenterX = rectA->x + (rectA->w * 0.5f);
	rectACenterY = rectA->y + (rectA->h * 0.5f);

	/* rectB CENTER X AND Y POSITION */
	rectBCenterX = rectB->x + (rectB->w * 0.5f);
	rectBCenterY = rectB->y + (rectB->h * 0.5f);

	/* UPDATE DISTANCE BETWEEN MOUSE AND rectA */
	DISTANCE_MOUSE = DistanceBetweenPoints(MOUSE_X, MOUSE_Y, rectACenterX, rectACenterY);

	/* UPDATE DISTANCE BETWEEN rectA AND rectB */
	DISTANCE_FRect = DistanceBetweenFRect(rectA, rectB);

	/* ASSIGN rectB POSITION TO MOUSE POSITION */
	if (isFollowingMouse) {
		rectB->x = (int)MOUSE_X - (rectB->w * 0.5f);
		rectB->y = (int)MOUSE_Y - (rectB->h * 0.5f);
	}

	/* UPDATE COLLISION */
	isColliding = PointCollision(MOUSE_X, MOUSE_Y, rectA) || BoxCollision(rectA, rectB);

	/* SET rectA COLOR (BASED ON COLLISION): GREEN OR RED */
	if (isColliding) {
		SDL_SetRenderDrawColor(RENDERER, 0, 255, 0, 255);
	}
	else {
		SDL_SetRenderDrawColor(RENDERER, 255, 0, 0, 255);
	}

	/* DRAW rectA */
	SDL_RenderFillRect(RENDERER, rectA);

	/* SET rectB COLOR: BLUE */
	SDL_SetRenderDrawColor(RENDERER, 0, 0, 255, 255);

	/* DRAW rectB */
	SDL_RenderFillRect(RENDERER, rectB);

	/* SET LINE COLOR: WHITE */
	SDL_SetRenderDrawColor(RENDERER, 255, 255, 255, 255);

	/* DRAW LINE BETWEEN rectA AND rectB */
	SDL_RenderLine(RENDERER, rectACenterX, rectACenterY, rectBCenterX, rectBCenterY);

	/* DRAW LINE BETWEEN MOUSE AND rectA */
	SDL_RenderLine(RENDERER, MOUSE_X, MOUSE_Y, rectACenterX, rectACenterY);

	/* DRAW TEXT: TITLE */
	SDL_RenderDebugTextFormat(RENDERER, TEXT_OFFSET_X, WINDOW_HEIGHT * 0.05f, "SDL COLLISION & DISTANCE");

	/* DRAW TEXT: CREDIT */
	SDL_RenderDebugTextFormat(RENDERER, TEXT_OFFSET_X, WINDOW_HEIGHT * 0.07f, "BY RUBEN RONQUILLO");

	/* DRAW TEXT: COLLISION STATUS */
	SDL_RenderDebugTextFormat(RENDERER, TEXT_OFFSET_X, WINDOW_HEIGHT * 0.15f, "> COLLISION: %d", isColliding);

	/* DRAW TEXT: DISTANCE FROM MOUSE TO rectA */
	SDL_RenderDebugTextFormat(RENDERER, TEXT_OFFSET_X, WINDOW_HEIGHT * 0.2f, "> DISTANCE MOUSE: %d", (int)DISTANCE_MOUSE);

	/* DRAW TEXT: DISTRANCE FROM rectA TO rectB */
	SDL_RenderDebugTextFormat(RENDERER, TEXT_OFFSET_X, WINDOW_HEIGHT * 0.25f, "> DISTANCE RECT: %d", (int)DISTANCE_FRect);

	/* DRAW TEXT: TOGGLE rectB PARENT TO MOUSE */
	SDL_RenderDebugTextFormat(RENDERER, TEXT_OFFSET_X, WINDOW_HEIGHT * 0.9f, "CLICK [MOUSE LEFT] TO TOGGLE MOUSE FOLLOW: %d", isFollowingMouse);

	/* DRAW TEXT: CLOSE PROGRAM */
	SDL_RenderDebugTextFormat(RENDERER, TEXT_OFFSET_X, WINDOW_HEIGHT * 0.95f, "PRESS [ESCAPE] TO CLOSE PROGRAM");

	/* DRAW FRAME */
	SDL_RenderPresent(RENDERER);

	/* CONTINUE PROGRAM */
	return SDL_APP_CONTINUE;
}

/* THIS FUNCTION RUNS WHEN A NEW INPUT EVENT OCCURS */
SDL_AppResult SDL_AppEvent(void* appState, SDL_Event* event) {

	/* PROGRAM CLOSED */
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}

	/* MOUSE MOTION INPUT */
	else if (event->type == SDL_EVENT_MOUSE_MOTION) {

		/* UPDATE MOUSE X MOTION */
		MOUSE_X = event->motion.x;

		/* UPDATE MOUSE Y MOTION */
		MOUSE_Y = event->motion.y;
	}
	
	/* MOUSE BUTTON INPUT */
	else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		
		/* MOUSE BUTTONS */
		switch (event->button.button) {
			case SDL_BUTTON_LEFT:
				/* TOGGLE rectB FOLLOW MOUSE */
				isFollowingMouse = isFollowingMouse ? 0 : 1;
				break;
		}
	}

	/* KEY DOWN INPUT */
	else if (event->type == SDL_EVENT_KEY_DOWN) {

		/* KEYS */
		switch (event->key.key) {
			case SDLK_ESCAPE:
				/* CLOSE PROGRAM */
				return SDL_APP_SUCCESS;
		}
	}

	/* CONTINUE PROGRAM */
	return SDL_APP_CONTINUE;
}

/* THIS FUNCTION RUNS ONCE AT SHUTDOWN */
void SDL_AppQuit(void* appState, SDL_AppResult result) {

	/* DEALLOCATE rectA and rectB */
	free(rectA);
	free(rectB);
	
	/* END SDL */
	SDL_Quit();
}