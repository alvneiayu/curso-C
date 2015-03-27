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
	int server, client, t, len, n;
	struct sockaddr_un local, remote;
	char str[100];

	if ((server = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		printf("Error: Socket()\n");
		return -1;
	}

	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, SOCK_PATH);
	unlink(local.sun_path);
	len = strlen(local.sun_path) + sizeof(local.sun_family);
	if (bind(server, (struct sockaddr *)&local, len) == -1) {
		printf("Error: Bind()\n");
		return -1;
	}

	if (listen(server, 5) < 0) {
		printf("Error: Listen()\n");
		return -1;
	}

	while(1) {
		printf("Esperando una conexion...\n");
		t = sizeof(remote);
		if ((client = accept(server, (struct sockaddr *)&remote, &t)) < 0) {
			perror("accept");
			exit(1);
		}
		printf("Conectado\n");

		n = recv(client, str, 100, 0);
		if (n < 0) {
			printf("Error: Recv()\n");
			return -1;
		} else if (n > 0) {
			printf("Recibido %d bytes\n", n);
			printf("Mensaje: %s\n", str);
		}

		close(client);
	}

	close(server);
	return 0;
}
