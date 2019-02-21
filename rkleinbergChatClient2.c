#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>

#define SERVER "10.115.20.250"
#define PORT 49153
#define BUFSIZE 1024

int connect2v4stream(char * srv, int port){
	int ret, sockd;
	struct in_addr myIn_addr;
	struct sockaddr_in mySockaddr_in;

	if( (sockd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		printf("ERROR: Error creating socket. errno = %d\n", errno);
		exit(errno);
	}
	if( (ret = inet_pton(AF_INET, "10.115.20.250", &myIn_addr)) <= 0){
		printf("ERROR: trouble converting using inet_pton. return value = %d, errno = %d\n", ret, errno);
		exit(errno);
	
}
	mySockaddr_in.sin_family = AF_INET;
	mySockaddr_in.sin_port = htons(49153);
	mySockaddr_in.sin_addr = myIn_addr;

	if( (connect(sockd, (struct sockaddr *) &mySockaddr_in, sizeof(mySockaddr_in))) == -1){
		printf("ERROR: trouble cocnnecting to server, errno = %d\n", errno);
		exit(errno);
	}
	return sockd;
}

int sendout(int fd, char *msg){

	int ret;
	ret = send(fd, msg, strlen(msg), 0);
	if( ret == -1 ){
		printf("ERROR: trouble sending. errno = %d\n", errno);
		exit(errno);
	}
	return strlen(msg);
}

void recvandprint(int fd, char *buff) {

	int ret;

	for(;;) {
		buff = malloc(BUFSIZE+1);
		ret = recv(fd, buff, BUFSIZE,0);
		if(ret==-1) {
			if(errno = EAGAIN){
				break; // do it again
			} else {
				printf("ERROR: error receiveing. errno = %d\n", errno);
				exit(errno);
			}
		} else if(ret == 0 ){
			exit(0);
		} else {
			buff[ret] = 0;
			printf("%s", buff);
		}
		free(buff);
	}
}
	

int main(int argc, char * argv[]) {
	int fd, len;
	char *name, *buffer, *origbuffer;
	struct timeval timev;

	printf("Enter desired user name: ");
	char input[100] = "hmm";
	char check[100];
	char rec[1000];
	int boo = 1;	

	fgets(input, 100, stdin);


	printf("Your username is: %s", input);
	printf("\n");

	fd = connect2v4stream( SERVER, PORT );

	//Setupt recv timeout for .5 seconds
	timev.tv_sec = 0;
	timev.tv_usec = 1000 * 500;
	setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timev, sizeof(timev));

	//set name based on arguments
	if(argc < 2) {
		printf("Usage: chat client <screenname>\n");
		exit(1);
	}
	name = argv[1];
	len = strlen(name);
	name[len] = '\n';
	name[len+1] = '\0';
	sendout(fd, name);

	int is_done = 0;
	while( ! is_done ) {
		recvandprint(fd, buffer);
		//printf("We ran");

		len = BUFSIZE;
		buffer = malloc(len+1);
		origbuffer = buffer;
		if( getline(&buffer, (size_t *) &len,stdin) > 1){
			sendout(fd, buffer);
		}
		is_done = (strcmp (buffer, "quit\n") == 0);
		free(origbuffer);
	}
}