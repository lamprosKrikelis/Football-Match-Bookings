#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){

		int clientSocket, ret;
		
		struct sockaddr_in serverAddr;
		
		char buffer[1024];

		clientSocket = socket(AF_INET, SOCK_STREAM, 0);

		if(clientSocket < 0){
			printf("[-]Error in connection.\n");
			exit(1);
		}

		printf("[+]Client Socket is created.\n");

		memset(&serverAddr, '\0', sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(PORT);
		serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
		if(ret < 0){
			printf("[-]Error in connection.\n");
			exit(1);
		}
		printf("[+]Connected to Server.\n");


		while(1){

			printf("If you want tickets for the match please type yes:  \n");
			scanf("%s", &buffer[0]);
			write(clientSocket,buffer,1024);

			if(strcmp(buffer, "Ctrl+C") == 0){
				close(clientSocket);
				printf("[-]Disconnected from server.\n");
				exit(1);
			}else if (strstr(buffer,"yes")){

				bzero(buffer,1024);
				read(clientSocket,buffer,1024);
				printf("%s",buffer);

				bzero(buffer,1024);
				sprintf(buffer,"Thank you Server!\n");
				write(clientSocket,buffer,1024);

			}else{

				bzero(buffer,1024);
				read(clientSocket,buffer,1024);
				printf("%s",buffer);
				
			}

		return 0;
	}


}