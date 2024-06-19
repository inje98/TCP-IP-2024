#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1

char webpage[] = "HTTP/1.1 200 OK\r\n"
				"Server:Linux Web Server\r\n"
				"Content-Type: text/html; charset=UTF-8\r\n\r\n"
				"<!DOCTYPE html>\r\n"
				"<html><head><title> My Web Page </title>\r\n"
				"<style>body {background-color: #062180 }</style></head>\r\n"
				"<body><center><h1>Hello world!!</h1><br>\r\n"
				"<img src=\"cat.jpg\"></center></body></html>\r\n";  // 수정된 부분: <\center> -> </center>

int main(int argc, char* argv[])
{
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t sin_len = sizeof(clnt_addr);
	int serv_sock, clnt_sock;
	char buf[2048];
	int fdimg, img_size;
	int option = TRUE;
	char img_buf[700000];

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);

	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		perror("bind() error!");
	if (listen(serv_sock, 5) == -1)
		perror("listen() error!");

	while (1)
	{
		puts("New client connection.....");

		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &sin_len);
		if (clnt_sock == -1) {
			perror("accept() error");
			continue;
		}

		read(clnt_sock, buf, 2047);
		printf("%s\n", buf);

		if (strstr(buf, "GET /cat.jpg") != NULL)
		{
			fdimg = open("cat.jpg", O_RDONLY);
			if (fdimg == -1) {
				perror("open() error");
				close(clnt_sock);
				continue;
			}

			if ((img_size = read(fdimg, img_buf, sizeof(img_buf))) == -1) {
				perror("read() error");
				close(fdimg);
				close(clnt_sock);
				continue;
			}
			close(fdimg);

			sprintf(buf, "HTTP/1.1 200 OK\r\n"
				"Server: Linux Web Server\r\n"
				"Content-Type: image/jpeg\r\n"
				"Content-Length: %d\r\n\r\n", img_size);  // %ld -> %d로 수정

			if (write(clnt_sock, buf, strlen(buf)) < 0) {
				perror("header write error");
				close(clnt_sock);
				continue;
			}

			if (write(clnt_sock, img_buf, img_size) < 0) {
				perror("image write error");
				close(clnt_sock);
				continue;
			}
			close(clnt_sock);
		}
		else
		{
			if (write(clnt_sock, webpage, sizeof(webpage) - 1) == -1) {  // sizeof(webpage)에서 -1 추가
				perror("webpage write error");
			}
			puts("closing......");
			close(clnt_sock);
		}
	}

	close(serv_sock);
	return 0;
}
