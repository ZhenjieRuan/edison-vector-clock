/* simple vector clock implementation to coordinate imu readings from several edisons */
#include "vector_clock.h"

int main(int argc, char *argv[])
{
	int peers[argc - 1]; /* IP addresses in dot format of peers */
	printf("listening on socket %d\n", init_receiver());
	return 0;
}

/**
 * Setting up socket for specific address and port
 * @params: char *address, char *port, op (connect or bind)
 * @return: sockfd on successful, -1 otherwise
 */
int init_socket(char* addr, char* port, int op)
{
	int status, sockfd;
	addrinfo_t hints;
	addrinfo_t *res;

	/* for debug use */
	char ip4[INET_ADDRSTRLEN];
	struct sockaddr_in *sa;
	
	memset(&hints, 0, sizeof(hints)); /* make sure the hint if empty */

	hints.ai_family = AF_INET; /* IPv4 addr */
	hints.ai_socktype = SOCK_DGRAM; /* use UDP */
	hints.ai_flags = op == OP_BIND ? AI_PASSIVE: AI_DEFAULT; /* returned struct if intended to use for bind() */

	if ((status = getaddrinfo(addr, port, &hints, &res)) != 0)
	{
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		return -1;
	}

	sa = (struct sockaddr_in *)res->ai_addr;

	inet_ntop(AF_INET, &(sa->sin_addr), ip4, INET_ADDRSTRLEN);

	printf("The IPv4 address of this board is: %s\n", ip4);

	/* creating socket and bind the socket */
	if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
	{
		fprintf(stderr, "Error creating socket: %s\n", strerror(errno));
		return -1;
	}

	switch (op) {
		case OP_BIND:
			if (bind(sockfd, res->ai_addr, res->ai_addrlen))
			{
				fprintf(stderr, "Error binding socket: %s\n", strerror(errno));
				return -1;
			}

			if (listen(sockfd, 20))
			{
				fprintf(stderr, "Error listening to sockfd %d: %s\n", sockfd, strerror(errno));
				return -1;
			}

			break;
		case OP_CONNECT:
			if (connect(sockfd, res->ai_addr, res->ai_addrlen))
			{
				fprintf(stderr, "Error connecting to sockfd %d: %s\n", sockfd, strerror(errno));
				return -1;
			}

			break;
	}


	return sockfd;
}

/**
 * Setting up socket for receiving peer's vectors
 * Listening port 3000
 * @params: None
 * @return: sockfd listening to if successful, -1 otherwise
 */
int init_receiver()
{
	int sockfd;

	if ((sockfd = init_socket(NULL, "3000", OP_BIND)) == -1)
	{
		fprintf(stderr, "Error getting socket for receiver\n");
		return -1;
	}

	return sockfd;
}

/**
 * Setting up socket for sending vector clock to peers
 * @params: char* addr(peer IP), char* port (port must be greater than 1024 and can't be 3000)
 * @return: sockfd for sending if successful, -1 otherwise
 */
int init_sender(char *addr, char *port)
{
	int sockfd;

	if ((sockfd = init_socket(addr, port, OP_CONNECT)) == -1)
	{
		fprintf(stderr, "Error getting sending socket for peer %s\n", addr);
		return -1;
	}

	return sockfd;
}

