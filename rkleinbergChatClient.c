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
		

int main(int argc, const char* argv[])
{
	//Query for the desired user name and initialize variables
	printf("Enter desired user name: ");
	char input[100] = "hmm";
	char check[100];
	char rec[1000];
	int boo = 1;	

	fgets(input, 100, stdin);


	printf("Your username is: %s", input);

	printf("\n");
	sleep(1);

	
	//define In_addr which will holds the ip address
	struct in_addr myIn_addr;

	//define sockaddr_in, that holds information that the connect function can use to form a connection
	struct sockaddr_in mySockaddr_in;

	//create the socket
	int mySocket = socket(AF_INET, SOCK_STREAM, 0);

	if(mySocket <= 0){
		printf("Error in socket function, exiting program");
		boo = 0;
	}


	//changes the form of the ip address, stored in myIn_addr, from its standard text representation to its
	//numeric binary form
	int chat = inet_pton(AF_INET, "10.115.20.250", &myIn_addr);

	if(chat <= 0){
		printf("Error in inet_pton function, exiting program");
		boo = 0;
	}

	

	//fill the sockaddr_in with relevant information
	mySockaddr_in.sin_family = AF_INET;
	mySockaddr_in.sin_port = htons(49153);
	mySockaddr_in.sin_addr = myIn_addr;

	
	//form the connection
	int connection = connect(mySocket, (struct sockaddr *) &mySockaddr_in, sizeof(mySockaddr_in));

	if(connection < 0){
		printf("Error in connect function, exiting program");
		boo = 0;
	}

	sleep(1);

	//connection has been formed so send username to server
	int see = send(mySocket, &input, sizeof(input), 0);
	if(see < 0){
		printf("Error in first send function, exiting program");
		boo = 0;
	}

	//clear the input variable
	memset(input,0,strlen(input));


	//query for the desired exit string
	printf("Enter exit string: ");
	
	fgets(check, 100, stdin);

	printf("\n");
	printf("To exit the program, enter your exit string. Now type away! \n");
	


	//loop through so the user can send as many messages as they want
	while(boo){
		sleep(1);
		fgets(input, 100, stdin);

		//if the user has entered the exit string - exit
		if(strcmp(check, input) == 0){
			boo = 0;
		}else{
			
			//error check send function- 
			if(send(mySocket, input, sizeof(input), 0) < 0){
				printf("Error in send function, exiting program");
				boo = 0;
			}else{
				//clear the input string for it has already sent
				memset(input,0,strlen(input));
				printf("\n");

				//try to receive data
				printf("attempting to receive... \n");
				sleep(1);

				int reccheck = recv(mySocket, &rec, 1000, 0);

				//error check the read function and return the received data
				if(reccheck < 0){
					printf("Error in read function, exiting program");
					boo = 0;
				}else{
					printf("%s\n",rec);
					printf("Recv return: %d",reccheck);
					printf("\n");
					printf("\n");
					memset(rec, 0, strlen(rec));	
				}
				
			}
		}
		
		
		
	}
	



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
