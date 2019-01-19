#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main()
{

	struct in_addr inaddr;

	int chat = inet_pton(AF_INET, "10.115.20.150", &inaddr);

	printf( "lawd he comin");
	printf("%d",chat);
}