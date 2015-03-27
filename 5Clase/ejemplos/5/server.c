#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <ev.h>

#define PORTNUM 9999
#define BUFFER_SIZE 1024

int total_clients;

void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
	char buffer[BUFFER_SIZE];
	ssize_t read;

	if(EV_ERROR & revents) {
		printf("Invalid Event\n");
		return;
	}

	read = recv(watcher->fd, buffer, BUFFER_SIZE, 0);
	if (read < 0) {
		perror("Error: recv()\n");
		return;
	}

	if(read == 0) {
		ev_io_stop(loop, watcher);
		free(watcher);
		perror("Desconectando el cliente\n");
		total_clients --;
		printf("%d clientes conectados.\n", total_clients);
		return;
	} else {
		printf("Mensaje: %s\n",buffer);
	}

	send(watcher->fd, buffer, read, 0);
	bzero(buffer, read);
}

void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	int client_sd;
	struct ev_io *w_client = (struct ev_io*) malloc (sizeof(struct ev_io));

	if(EV_ERROR & revents) {
		printf("Invalid Event\n");
		return;
	}

	client_sd = accept(watcher->fd, (struct sockaddr *)&client_addr, &client_len);
	if (client_sd < 0) {
		printf("Error: accept()\n");
		return;
	}

	total_clients ++;
	printf("Conexión satisfactoria con el cliente\n");
	printf("%d clientes conectados.\n", total_clients);

	ev_io_init(w_client, read_cb, client_sd, EV_READ);
	ev_io_start(loop, w_client);
}

int main(int argc, char *argv[])
{
	struct ev_loop *loop = ev_default_loop(0);
	struct sockaddr_in dest;
	struct sockaddr_in serv;
	int server;
	struct ev_io w_accept;
	socklen_t socksize;

	socksize = sizeof(struct sockaddr_in);
	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(PORTNUM);

	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server < 0) {
		printf("Error: Socket()\n");
		return -1;
	}

	bind(server, (struct sockaddr *)&serv, sizeof(struct sockaddr));
	listen(server, 1);

	ev_io_init(&w_accept, accept_cb, server, EV_READ);
	ev_io_start(loop, &w_accept);

	while (1) {
		ev_loop(loop, 0);
	}

	return 0;
}
