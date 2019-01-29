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
//https://stackoverflow.com/questions/8107826/proper-way-to-empty-a-c-string - memset function
//tanner told us to use sleep

int main(int argc, const char* argv[])
{
	printf("Enter desired user name: ");
	char input[100] = "hmm";

	char fart[] = "\n";
	fgets(input, 100, stdin);
	//strcat(input,fart);

	printf("%s", input);
	printf("\n");
	sleep(1);

	
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


	sleep(1);

	char data[] = "lawd he comin \n";

	int see = send(mySocket, &input, sizeof(input), 0);

	memset(input,0,strlen(input));
	int boo = 1;

	printf("Enter exit string: ");
	char check[100];
	fgets(check, 100, stdin);

	printf("Enter recieve string: ");
	char recString[100];
	fgets(recString, 100, stdin);

	char rec[1000];

	while(boo){
		sleep(1);
		fgets(input, 100, stdin);

		if(strcmp(check, input) == 0){
			boo = 0;
		}else if(strcmp(recString, input) == 0){//breaks when receive is called twice in a row

			printf("attempting to receive... \n");
			printf("Do not run this functino twice in a row or the program will break");
			sleep(1);
			int reccheck = read(mySocket, &rec, 1000);
			printf("%s\n",rec);
			printf("Recv return: %d",reccheck);
			printf("\n");
			memset(rec, 0, strlen(rec));
			
		}else{
			//strcat(input,fart); - 
			send(mySocket, input, sizeof(input), 0);
			memset(input,0,strlen(input));
			printf("attempting to receive... \n");
			sleep(1);
			int reccheck = read(mySocket, &rec, 1000);
			printf("%s\n",rec);
			printf("Recv return: %d",reccheck);
			printf("\n");
			memset(rec, 0, strlen(rec));
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

/*
can append newline by doing: str[len(str)] = "\n"]
							   str[len(str) + 1] = 0

char *name = malloc(80) better way of initializing strings
bxero(name, sizeof(name)); - clears out string
bcopy(src, dest,numberofcharacters); - copy a string
*/
