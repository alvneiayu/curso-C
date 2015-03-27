#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <sys/wait.h>

#define PORT 9999
#define BUFSIZE 2048

int main(int argc, char **argv) {
	struct sockaddr_in myaddr;
	struct sockaddr_in remaddr;
	socklen_t addrlen = sizeof(remaddr);
	int recvlen, fd;
	unsigned char buf[BUFSIZE];

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("Error: Socket()\n");
		return 0;
	}

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("Error: Bind()\n");
		return 0;
	}

	while (1) {
		printf("Esperando al puerto %d\n", PORT);
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		printf("Recibido %d bytes\n", recvlen);
		if (recvlen > 0) {
			buf[recvlen] = 0;
			printf("Mensaje recibido: \"%s\"\n", buf);
		}
	}
}
