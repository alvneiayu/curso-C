#include <stdio.h>
#include <netinet/in.h>
#include <string.h>

#define PORT_NO 9999
#define BUFFER_SIZE 1024

int main()
{
	int client;
	struct sockaddr_in addr;
	int addr_len = sizeof(addr);
	char buffer[BUFFER_SIZE] = "";

	if((client = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error: Socket()\n");
		return -1;
	}

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_NO);
	addr.sin_addr.s_addr =  htonl(INADDR_ANY);

	if(connect(client, (struct sockaddr *)&addr, sizeof addr) < 0) {
		perror("Error: Connect()\n");
		return -1;
	}

	while (strcmp(buffer, "q") != 0) {
		gets(buffer);
		send(client, buffer, strlen(buffer), 0);

		recv(client, buffer, BUFFER_SIZE, 0);
		printf("Mensaje: %s\n", buffer);
	}

	close(client);
	return 0;
}
