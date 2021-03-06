#ifndef TYPES_H
#define TYPES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define END_NETWORK_MSG "_END"

#define BALL_NETWORK_MSG_PREFIX "b_"
#define SPADDLE_NETWORK_MSG_PREFIX "sp_"
#define CPADDLE_NETWORK_MSG_PREFIX "cp_"
#define KEY_NETWORK_MSG_PREFIX "k_"
#define KEY_DOWN_NETWORK_MSG "down"
#define KEY_UP_NETWORK_MSG "up"
#define LOST_NETWORK_MSG "lost"
#define WON_NETWORK_MSG "won"
#define NETWORK_TRANSMISSION_END "END_TRANSMISSION"

#define SDL_ERROR fprintf(stderr, "SDL Error: %s", SDL_GetError())

#define TICK_INTERVAL 20;

typedef struct server server_t;
typedef struct client client_t;
typedef struct pong_ball pong_ball_t;
typedef struct pong_paddle pong_paddle_t;
typedef struct pong_window pong_window_t;
typedef struct color color_t;
typedef struct pong_client pong_client_t;
typedef struct pong_server pong_server_t;
typedef struct pong_score pong_score_t;
typedef struct pong_opt_client pong_opt_client_t;
typedef struct pong_opt_server pong_opt_server_t;
typedef struct pong_field pong_field_t;

enum key {
	DOWN_KEY,
	UP_KEY
};

enum info_type {
	PADDLE,
	BALL
};

typedef int socket_t;

struct client {
	socket_t sock;
	char *ip;
	int port;
};

struct server {
	socket_t sock;
	socket_t sock_client;
	int port;
};

struct color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
};

struct pong_window {
	SDL_Window *win;
	SDL_Renderer *ren;
	color_t bg_color;
	size_t height;
	size_t width;
};

struct pong_paddle {
	pong_window_t *window;
	size_t velocity;
	color_t color;
	SDL_Rect rect;
};

struct pong_ball {
	size_t size;
	size_t angle;
	SDL_Rect rect;
	color_t color;
	float velocityX;
	float velocityY;
	float x;
	float y;
	pong_score_t *score;
};

struct pong_client {
	client_t *client;
	pong_ball_t *ball;
	pong_paddle_t *paddle;
	pong_paddle_t *paddle_s;
};

struct pong_server {
	server_t *server;
	pong_ball_t *ball;
	pong_paddle_t *paddle;
	pong_paddle_t *paddle_c;
};

struct pong_field {
	color_t color;
	SDL_Rect rect;
	int nbCube;
	int middle;
};

struct sdl_button {
	char *text;
	SDL_Rect rect;
};

struct pong_score {
	color_t color;
	TTF_Font *text;
	SDL_Rect rect;
	int player1;
	int player2;
};

struct pong_opt_client {
	char *ip;
	int port;
};

struct pong_opt_server {
	int port;
};

enum pong_type {
	server,
	client
};

#endif
