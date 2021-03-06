#ifndef SERVER_H
#define SERVER_H

#include "network_msg.h"
#include "pong_event.h"
#include "types.h"
#include <signal.h>

server_t *server_init(const int);
int server_wait_conn(server_t *, const size_t);
int server_send_msg(const server_t *, const char *);
char *server_next_msg(const server_t *);
void server_shutdown(const server_t *);

#endif
