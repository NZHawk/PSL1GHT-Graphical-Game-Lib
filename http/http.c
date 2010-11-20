#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include "http.h"
#define PROTOCOL "tcp"
#define SERVICE "http"
#define GET "GET /vers.txt HTTP/1.1\nHost: nzhawk.co.cc\nConnection: close\n\n"
#define USERAGENT "HTMLGET 1.0"

void httpGet(char *ip, char *host, char *path)
{
	int s;
	int bufsize;
	//char host[50];
	char buffer[1024];
	char *getRequest;
	//char *host;
	//strcpy(host, "66.102.11.104");

	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_len = sizeof(server);
	server.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &server.sin_addr);
	server.sin_port = htons(80);

	s = createSock();

	if(connect(s, &server, sizeof(server)) == -1) {
		printf("Error connecting.");
		exit(1);
	}
	char *query;
	char *getpage = path;
	char *tpl = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";
	if(getpage[0] == '/'){
		getpage = getpage + 1;
		fprintf(stderr,"Removing leading \"/\", converting %s to %s\n", path, getpage);
	}
	query = (char *)malloc(strlen(host)+strlen(getpage)+strlen(USERAGENT)+strlen(tpl)-5);
	sprintf(query, tpl, getpage, host, USERAGENT);

	printf(query, "\n\n\n");
	if (send(s, query, strlen(query), 0) == -1) {
		printf("Error sending data.");
		exit(1);
	}

	/* read the socket until its clear then exit */
	while ( (bufsize = read(s, buffer, sizeof(buffer) - 1))) {
		write(1, buffer, bufsize);
		//sprintf(buffer, buffer
	}

	close(s);
}


int createSock()
{
  int sock;
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  return sock;
}




