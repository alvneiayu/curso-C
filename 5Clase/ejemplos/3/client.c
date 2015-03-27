#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>

#define BUFLEN 2048
#define PORT 9999
#define MSGS 5

int main(void)
{
	struct sockaddr_in myaddr, remaddr;
	int fd, i, slen = sizeof(remaddr);
	char *server = "127.0.0.1";
	char buf[BUFLEN];

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Error: Socket()\n");
		return -1;
	}

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("Error: Bind()\n");
		return 0;
	}

	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(PORT);
	if (inet_aton(server, &remaddr.sin_addr) <= 0) {
		printf("Error: Inet_aton()\n");
		exit(1);
	}

	for (i=0; i < MSGS; i++) {
		printf("Enviando mensaje %d a %s puerto %d\n", i, server, PORT);
		sprintf(buf, "Mensaje número %d", i);
		if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr,
			   slen) < 0)
			printf("Error: Mensaje %d\n");
	}

	close(fd);
	return 0;
}
