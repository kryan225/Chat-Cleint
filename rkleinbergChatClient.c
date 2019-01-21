#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc, const char* argv[])
{
	//http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/client.c - to look at how to make a sockaddr_in

	
	//define In_addr which will holds the ip address
	struct in_addr myIn_addr;

	//define sockaddr_in, that holds information that the connect function can use to form a connection
	struct sockaddr_in mySockaddr_in;

	//create the socket
	int mySocket = socket(AF_INET, SOCK_STREAM, 0);

	//changes the form of the ip address, stored in myIn_addr, from its standard text representation to its
	//numeric binary form
	int chat = inet_pton(AF_INET, "10.115.20.250", &myIn_addr);
	

	//fill the sockaddr_in with relevant information
	mySockaddr_in.sin_family = AF_INET;
	mySockaddr_in.sin_port = htons(49153);
	mySockaddr_in.sin_addr = myIn_addr;

	
	//form the connection
	int connection = connect(mySocket, (struct sockaddr *) &mySockaddr_in, sizeof(mySockaddr_in));


	printf( "lawd he comin");
	printf("\n");
	printf("%d",chat);
	printf("\n");
	printf("%d",mySocket);
	printf("\n");
	printf("%d",connection);

	close(mySocket);

}
