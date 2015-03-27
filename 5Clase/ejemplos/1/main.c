#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<errno.h>
#include<netdb.h>
#include<arpa/inet.h>

int main(int argc, char *argv[])
{
	struct hostent *he;
	struct in_addr **addr_list;
	int i;
	char *hostname = argv[1];
	char ip[100];

	if (argc < 2) {
		printf("Uso: %s hostname\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if ((he = gethostbyname(hostname)) == NULL) {
		printf("Error: gethostbyname\n");
		return 1;
	}

	addr_list = (struct in_addr **) he->h_addr_list;
	for (i = 0; addr_list[i] != NULL; i++)
		strcpy(ip, inet_ntoa(*addr_list[i]));

	printf("%s cuya ip es %s \n", hostname, ip);
	return 0;
}
