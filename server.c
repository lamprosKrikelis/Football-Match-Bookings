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

typedef struct {
    
    int id;
    int team1;
    int team2;
    int avail_tickets; 
    float price;
     
} Match;

Match anymatch;

int main(){
	
	int sockfd, b;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

   	int count_new=0;

	char buffer[1024];
	pid_t childpid;
	
                           // Sock stream stand for tcp/ip protocol 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}

	printf("[+]Server Socket is created.\n");
   
   	//memset sets the first count bytes of destination to the value c
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

   	//Returns the binding of the socket 
	b = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(b < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", PORT);

	if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}


	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0 || newSocket > 10){
			exit(1);
		}

		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
		
		count_new ++; 
		
		if((childpid = fork()) == 0){
			close(sockfd);

			while (1){

				srand(time(NULL));

				int football_match[]= {1,2,3,4,5,6,7,8,9,10};

				int random_match = (rand() % 10) + 1; 
				int tickets ; 
				anymatch.avail_tickets; 
				do {

					anymatch.avail_tickets = (rand() % 5) + 1 ;
				
					tickets = (rand() % 3) + 1 ; 

				} while (anymatch.avail_tickets < tickets); 
				
				int new_avail = anymatch.avail_tickets - tickets ; 

						while(1)
						{
							
							read(newSocket, buffer, 1024);
							//printf("Client %d: %s\n", count_new, buffer);

							if(strcmp(buffer, "Ctrl+C") == 0){
								printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
								break;
							}else if (strstr(buffer,"yes")){

								bzero(buffer,1024);
								sprintf(buffer,"Here is your match\nYou will watch the:%d match!\nYou have:%d available tickets for the match\nYou have reserved:%d tickets\n%d ticket/s have been left\n",football_match[random_match], anymatch.avail_tickets, tickets, new_avail);
								write(newSocket,buffer, 1024);
								bzero(buffer,1024);
								read(newSocket,buffer,1024);

									if ( strcmp(buffer,"Ctrl+C")!=0 ){
										printf("Client %d says: %s",count_new,buffer);
				
									}else {
										printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
										break;	
									}
							}else{

							bzero(buffer,1024);
							sprintf(buffer,"Pls try again\n"); 
							write(newSocket,buffer,1024);

							}
						}

				anymatch.avail_tickets == new_avail;
			}

			close(newSocket);

			return 0;
		}
	}
}