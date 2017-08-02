#include "network_msg.h"

static int is_last_msg(const network_msg_t *msg) {
	int ret;

	if (msg->buffer[msg->length - 1] == END_NETWORK_MSG)
		ret = 1;
	else
		ret = 0;

	return ret;
}

static void save_msg_to_char(network_msg_t *msg, char **total_msg) {
	size_t total_msg_length;

	if (*total_msg == NULL) {
		*total_msg = malloc(msg->length + 1);
		memcpy(msg->buffer, *total_msg, msg->length);
		(*total_msg)[msg->length] = '\0';
	} else {
		total_msg_length = strlen(*total_msg);
		*total_msg = realloc(*total_msg, total_msg_length + msg->length + 1);
		memcpy(msg->buffer, *total_msg + total_msg_length, msg->length);
		total_msg_length += msg->length;
		*total_msg[total_msg_length] = '\0';
	}
}

static int read_cur_msg(const socket_t sock, network_msg_t *msg) {
	int ret;

	ret = 0;

	memset(msg->buffer, 0, MSG_BUFFER_SIZE);
	msg->length = read(sock, msg->buffer, MSG_BUFFER_SIZE);

	if (msg->length == 0)
		ret = -1;

	return ret;
}

char *network_msg_next(const socket_t sock) {
	network_msg_t msg;
	char *ret;

	ret = NULL;

	do {
		read_cur_msg(sock, &msg);
		save_msg_to_char(&msg, &ret);
		memset(msg.buffer, 0, MSG_BUFFER_SIZE);
	} while (!is_last_msg(&msg));

	return ret;
}

int network_msg_send(const socket_t sock, const char *msg) {
	int ret;

	ret = write(sock, msg, strlen(msg));
	if (ret == -1)
		perror("Can't write to socket");
	else {
		ret = write(sock, (char *)(END_NETWORK_MSG), 1);
		if (ret == -1)
			perror("Can't write to socket");
		else
			ret = 0;
	}

	return ret;
}
