/******************************************************************************************
*TODO:                                                                                    *
*Needed Protocol Strings:                                                                 *
*pa-  to play again                                                                       *
*Need to get the play again working.                                                      *
*Test for ties.                                                                           *
*Messing up somewhere after the win.                                                      *
*Optional:                                                                                *
*MSG-to send a string (chat)                                                              *
******************************************************************************************/
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cctype>

#include "tictactoe.cpp"

using namespace std;

void startServer(int port);
void handleConnection(int clisock);
void enterClientMode(char message[1024], int sockfd, int msgSize, char output[1024]);
void enterClientModeFromServer(int clisock, bool first = true);
void playerMakeMove(int clisock, TicTacToe* ttt);
 
int main(int argc, char* argv[]) 
{
        int sockfd;
        struct sockaddr_in server_addr;
        int port;
        char output[1024]; // Output message from server.
        struct hostent* hent;
        memset(output, '\0', 1024); // Clear the buffer.

        // Check for correct commandline input.
        if(argc < 3) 
        {
                cerr << "Usage: ./tictactoe [server name] [port]" << endl;
                exit(1);
        }
        
        port = atoi(argv[2]);
        
        // Error check the port number.
        if(port < 10000) 
        {
                cerr << "Port >= 10000 required." << endl;
                exit(1);
        }
        
        // Error check the server name.
        if((hent=gethostbyname(argv[1])) == NULL) 
        {
                cerr << "Invalid host name." << endl;
                exit(1);
        }
        
        // Create the client socket.
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        {
                cerr << "Socket error." << endl;
                exit(1);
        }
        
        memset((void *) &server_addr, 0, sizeof(server_addr)); // Clear the server address structure.
        
        // Set up the server address structure.
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr = *((struct in_addr *)hent->h_addr);
        server_addr.sin_port = htons(port);

        if(connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
        {
                cerr << "Connect error." << endl;
                startServer(port);
        }
        else
        {
                enterClientModeFromServer(sockfd);
        }
        close(sockfd);
        exit(1);
}


void handleConnection(int clisock) 
{
        char buffer[1016]; // 
        memset(buffer, '\0', 1016); // Clear the buffer.
        
        /*if((msgSize = recv(clisock, buffer, 1015, 0)) < 0) 
        {
                cerr << "Receive error." << endl;
        }
        
        cout << "Message received from client: " << buffer<<endl;
        char response[1024];
        sprintf(response, "Server: I received the following message:  %s", buffer);
        
        if((msgSize = send(clisock, response, strlen(response), 0)) < 0) 
        {
                cerr << "Send error." << endl;
        }
        */
        printf("Connection Created: Entering Client Mode.\n");
        enterClientModeFromServer(clisock, false);
        //close(clisock);
}

void closeSocket(int clisock)
{
   close(clisock);
}

bool sendMessage(char resp[4], int clisock)
{
   int msgSize;
   if((msgSize = send(clisock, resp, strlen(resp), 0)) < 0)
   {
      cerr << "Send Error." << endl;
      return false;
   }
   return true;
}

void enterClientModeFromServer(int clisock, bool first)
{
   printf("Inside Client mode from server.\n");
   int msgSize;
   char buffer[4];
   char pieces[2] = {'X', 'O'};
   memset(buffer, '\0', 3);
   bool play = true;
  	char piece = 'X';
   char resp[2];
   int index = 1;
	if(first == false)
	{
		piece = 'O';
      index = 0;
	}
	TicTacToe ttt(piece);
	//printf("%c\n", ttt.playerPiece);
   ttt.initBoard();
   ttt.showBoard();
   while(play)
   {
      printf("Inside While Statement.");
      if(first == false)
      {
         if((msgSize = recv(clisock, buffer, 3, 0)) < 0)
         {
            cerr <<"Receive error." << endl;
         }
         else
         {
            printf("Receiving response.\n");
            if((buffer[0] == 'w') && (buffer[1] == 'p'))
            {
               printf("I want to play.");
            }
            else if(buffer[0] == 'm')
            {
               printf("Move: %c, %c.\n", buffer[1], buffer[2]);
               ttt.placeMove((int)buffer[1] - 48, (int)buffer[2] - 48, pieces[index]);
               ttt.showBoard();
					playerMakeMove(clisock, &ttt);
            }
            else if(buffer[0] == 'w')
            {
               ttt.placeMove((int)buffer[1] - 48, (int)buffer[2] - 48, pieces[index]);
               ttt.showBoard();
               printf("%c has won. Would you like to play again? ", pieces[index]);
               scanf("%s", resp);
               if(resp[0] == 'y')
               {
                  printf("resp = y");
                  play = true;
               }
               else
               {
                  play = false;
               }
               //Getting here.
               printf("play = %s.\n", (play ? "True" : "False"));
               //Not getting here
               printf("test");
            }
				else if(buffer[0] == 'q')
				{
					printf("Quit Command Received. Exiting.");
					closeSocket(clisock);
					exit(1);
				}
            else
            {
               printf("Invalid command received.\n");
            }
            
         }
      }
      else
      {
         first = false;
         playerMakeMove(clisock, &ttt);
      }
      printf("Not sure where this is.");
   }
   printf("Outside while statment.");
   closeSocket(clisock);
   printf("Exiting Client Mode");
}

void startServer(int port)
{
   // Set up the socket.
   printf("Inside server.\n");


   int sockfd, newsockfd;
   unsigned int clilen;

   // Structures for client and server addresses.
   struct sockaddr_in server_addr, cli_addr;
       
   // Create the server socket.
   if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
   {
      cerr << "Socket error." << endl;
      exit(1);
   }
        
   memset((void *) &server_addr, 0, sizeof(server_addr)); // Clear the server address structure.
        
   // Set up the server address structure.
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   server_addr.sin_port = htons(port);
       
   // Bind the socket to the server address and port.
   if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) 
   {
   cerr << "Bind error.";
   exit(1);
   }

   // Listen on the socket, queue 5 incoming connections.
   listen(sockfd, 10);
        
   // Loop forever, handling connections.
   while(1) 
   {
      clilen = sizeof(cli_addr);
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
      if(newsockfd < 0) 
      {
         cerr << "Accept error." << endl;
         exit(1);
      }
      handleConnection(newsockfd);
   }
}

void playerMakeMove(int clisock, TicTacToe* ttt)
{
   char buffer[4];
   
   ttt->makeMove(buffer);
   //Allows for safe disconnect.
	if(buffer[0] == 'q')
	{
		printf("Message Sent, Closing Socket and Exiting!");
		sendMessage(buffer,clisock);
      closeSocket(clisock);
		exit(1);
	}
   else
      sendMessage(buffer, clisock);
	
	
}

void enterClientMode(char message[1024], int sockfd, int msgSize, char output[1024])
{
   cout <<"What message to send: ";
   cin.getline(message,1024);
   if((msgSize = send(sockfd, message, strlen(message), 0)) < 0) 
   {
      cerr << "Send error." << endl;
   }
  
   // Wait to receive response.
   if((msgSize = recv(sockfd, output, 1023, 0)) < 0) 
   {
      cerr << "Receive error." << endl;
   }

   cout << output << endl;
}
