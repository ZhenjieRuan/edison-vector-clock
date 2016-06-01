#ifndef _VECTOR_CLOCK_H_
#define _VECTOR_CLOCK_H_

#define OP_BIND 0
#define OP_CONNECT 1

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef struct addrinfo addrinfo_t;

int init_receiver();
int init_sender();

#endif /* ifndef _VECTOR_CLOCK_H_ */
