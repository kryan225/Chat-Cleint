#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//https://www.tutorialspoint.com/c_standard_library/c_function_strcat.htm - strcat documentation
//http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/client.c - to look at how to make a sockaddr_in
//https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/ - scanf documentation



int main(int argc, const char* argv[])
{

	char input[100];


	char fart[] = "\n";
	scanf("%[^\n]%*c", &input);
	strcat(input,fart);

	printf("%s", input);
	printf("\n");


	
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




	char data[] = "lawd he comin \n";

	int see = send(mySocket, &input, sizeof(input), 0);
	int boo = 1;
	while(boo){
		
		scanf("%[^\n]%*c", &input);
		if(sizeof(input) > 0 ){
			if(input == "exit"){
				boo = 0;
			}else{
				strcat(input,fart);
				send(mySocket, input, sizeof(input), 0);
			}
			
		}
		
	}
	



	printf("\n");
	printf( "lawd he comin");
	printf("\n");
	printf("inet_pton function - should be larger than 0: %d",chat);
	printf("\n");
	printf("mySocket - should be larger than 0: %d",mySocket);
	printf("\n");
	printf("Connection formed - should be >= 0: %d",connection);
	printf("\n");
	printf("send function - should not be -1, returns the number of bytes sent: %d",see);
	printf("\n");


	close(mySocket);

}
