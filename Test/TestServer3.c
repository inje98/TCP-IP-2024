#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

char webpage[] = "HTTP/1.1 200 OK\r\n"
       "Server:Linux Web Server\r\n"
       "Content-Type: text/html; charset=UTF-8\r\n\r\n"
       "<!DOCTYPE html>\r\n"
       "<html><head><title> My Web Page </title>\r\n"
       "<style>body {background-color: #FFFF00 }</style></head>\r\n"
       "<body><center><h1>Hello world!!</h1><br>\r\n"
       "<img src=\"game.jpg\"><\center></body></thml>\r\n";

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;
	char buf[BUF_SIZE];

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(10001);

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
		error_handling("bind() error");

	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	clnt_addr_size = sizeof(clnt_addr);

	while(1)
	{
		printf("Waiting for connections ...\n");

		clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr, &clnt_addr_size);
		if(clnt_sock == -1)
			error_handling("accept error");

		read(clnt_sock, buf, sizeof(buf));
		printf("Received requewt: \n%s\n", buf);

		if(strncmp(buf, "GET", 3) == 0)
		{
			write(clnt_sock, webpage, sizeof(webpage)-1);
		}
		close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
