/* Code belongs to EndianTribe
 * <https://github.com/EndianTribe/Network-Socket-in-C>
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
	printf("Client Started\n");
	const char *host_name = "127.0.0.1";
	const char *port_name = "6969";
	int client_socket;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	struct addrinfo *results;
	struct addrinfo *record;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(host_name, port_name, &hints, &results) != 0) {
		perror("Failed to translate client socket;");
		exit(EXIT_FAILURE);
	}
	printf("Client Socket Translated\n");

	for (record = results; record != NULL; record=record->ai_next) {
		client_socket = socket(record->ai_family, record->ai_socktype, record->ai_protocol);
		if (client_socket == -1) continue;
		if (connect(client_socket, record->ai_addr, record->ai_addrlen) != -1) break;
		close(client_socket);
	}

	if (record == NULL) {
		perror("Failed to create or connect");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(results);
	printf("Client socket created and connected\n");

	char *message = "Hello Socket World";

	if (send(client_socket, message, strlen(message),0) == -1) {
		printf("Oops Ho Gaya");
		perror("Failed");
		exit(EXIT_FAILURE);
	}
	else {
		printf("Bomb has been planted ~ CSGO reference\n");
	}

	close(client_socket);
	printf("Socket has been closed");
}
