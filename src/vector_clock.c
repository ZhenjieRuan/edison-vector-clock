/* simple vector clock implementation to coordinate imu readings from several edisons */
#include "../include/vector_clock.h"

int main(int argc, char *argv[])
{
	int peers[argc - 2]; /* num of peers */
	return 0;
}

/* 
 * Setting up socket for receiving peer's vectors
 * Listening port 3000
 * @params: None
 * @return: 0 if successful, -1 otherwise
 *
 */
int init_receiver() {
	int status;
	addrinfo_t hints;
	addrinfo_t *receiver;

	/* for debug use */
	char ip4[INET_ADDRSTRLEN];
	struct sockaddr_in *sa;
	
	memset(&hints, 0, sizeof(hints)); /* make sure the hint if empty */

	hints.ai_family = AF_INET; /* IPv4 addr */
	hints.ai_socktype = SOCK_DGRAM; /* use UDP */
	hints.ai_flags = AI_PASSIVE; /* returned struct if intended to use for bind() */

	if ((status = getaddrinfo(NULL, "3000", &hints, &receiver)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		return -1;
	}

	sa = (struct sockaddr_in *)receiver->ai_addr;

	inet_ntop(AF_INET, &(sa->sin_addr), ip4, INET_ADDRSTRLEN);

	printf("The IPv4 address is: %s\n", ip4);

	return 0;
}

