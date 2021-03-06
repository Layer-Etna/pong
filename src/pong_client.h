#ifndef PONG_CLIENT
#define PONG_CLIENT

#include "client.h"
#include "pong_msg.h"
#include "types.h"

void pong_client_init(pong_client_t *, const char *, const int);
void pong_client_connect(pong_client_t *);
void pong_client_disconnect(pong_client_t *);
void pong_client_send_key(const pong_client_t *, const enum key);
int pong_client_next_msg(pong_client_t *);

#endif
