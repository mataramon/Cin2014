/*
Homework 2
Authors: Diego Hernandez Ramirez, César López López
*/

#ifndef _SERVER_H_
#define _SERVER_H_
/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
using namespace std;

class Server{  
    private:
         int sockfd;
         int newsockfd;
         int portno;
         socklen_t clilen;
         char buffer[256];
         struct sockaddr_in serv_addr;
         struct sockaddr_in cli_addr;
         int n;
         
         void socketCreate();
         void socketBind();
         void socketListen();
         void socketAccept();
         void socketRead();
         void socketWrite();
         void socketClose();
         void error(const char *msg);   
             
    public:

        Server(int portin){ this->portno=portin; 
                            this->socketCreate();
                            this->socketBind();
                            this->socketListen();
                            this->socketAccept();
                            this->socketRead();
                            this->socketWrite();
                            this->socketClose();       
                          };
};





#endif
