#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "echo_socket"

int main(void)
{
	int client, t, len;
	struct sockaddr_un remote;
	char str[] = "Hola Mundo";

	if ((client = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	printf("Intentando conectar...\n");

	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH);
	len = strlen(remote.sun_path) + sizeof(remote.sun_family);
	if (connect(client, (struct sockaddr *)&remote, len) < 0) {
		printf("Error: connect()\n");
		return -1;
	}

	printf("Conectado.\n");
	if (send(client, str, strlen(str), 0) < 0) {
		printf("Error: send()\n");
		return -1;
	}

	close(client);
	return 0;
}
