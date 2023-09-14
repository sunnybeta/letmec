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
	printf("Server Started\n");
	const size_t buffer_size = 1000;
	const char *port_name = "6969";
	const int backlog = 1;
	int server_socket;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	struct addrinfo *results;
	struct addrinfo *record;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(NULL, port_name, &hints, &results) != 0) {
		perror("Failed to translate server socket\n");
		exit(EXIT_FAILURE);
	}
	printf("Server Socket Translated\n");

	for (record = results; record != NULL; record=record->ai_next) {
		server_socket = socket(record->ai_family, record->ai_socktype, record->ai_protocol);
		if (server_socket == -1) continue;
		int enable = 1;
		setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
		if (bind(server_socket, record->ai_addr, record->ai_addrlen) == 0) break;
		close(server_socket);
	}

	if (record == NULL) {
		perror("Failed to create or connect");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(results);
	printf("Client socket created and connected\n");

	if (listen(server_socket, backlog) == -1) {
		perror("Failed to start server");
		exit(EXIT_FAILURE);
	}

	printf("Server started listening\n");

	while (1) {
		printf("Server is still running\n");
		int client_socket;
		struct sockaddr client_address;
		socklen_t client_address_length = sizeof(client_address);

		if ((client_socket = accept(server_socket, &client_address, &client_address_length)) < 0) {
			perror("Failed to accept client\n");
			exit(EXIT_FAILURE);
		}
		printf("Client Socket Accepted\n");
		char buffer[buffer_size];
		if (recv(client_socket, buffer, sizeof(buffer), 0) == -1) {
			perror("Failed to receive message");
			exit(EXIT_FAILURE);
		}
		printf("---------- RECEIVED MESSAGE ----------\n%s\n---------- END OF MESSAGE ----------\n", buffer);
		close(client_socket);
	}

	printf("Socket has been closed");
	return 0;
}
