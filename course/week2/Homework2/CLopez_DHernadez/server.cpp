/*
Homework 2
Authors: Diego Hernandez Ramirez, César López López
*/


#include "server.h"

void Server::socketCreate()
{
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0) //openSocket
        this->error("ERROR opening socket"); 
    bzero((char *) &this->serv_addr, sizeof(this->serv_addr));
}

void Server::socketBind()
{

    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_addr.s_addr = INADDR_ANY;
    this->serv_addr.sin_port = htons(this->portno);
    
    if (bind(this->sockfd, (struct sockaddr *) &this->serv_addr,
              sizeof(this->serv_addr)) < 0) 
              this->error("ERROR on binding");
}

void Server::socketListen()
{
    listen(this->sockfd,5);
    cout << "<Socket is now listening>\n\n";
}

void Server::socketAccept()
{
    this->clilen = sizeof(this->cli_addr);
    this->newsockfd = accept(this->sockfd, 
                 (struct sockaddr *) &this->cli_addr, 
                 &this->clilen);
    if (this->newsockfd < 0) 
          this->error("ERROR on accept");
     bzero(this->buffer,256);
}

void Server::socketRead()
{
    this->n = read(this->newsockfd,this->buffer,255);
    if (this->n < 0) this->error("ERROR reading from socket\n");
        cout<<"Here is the message: "<< this->buffer<<endl;
}

void Server::socketWrite()
{
     this->n = write(this->newsockfd,"I got your message",18);
     if (this->n < 0) this->error("ERROR writing to socket");
}

void Server::socketClose()
{
    close(this->newsockfd);
    close(this->sockfd);
    cout << "<Socket is now Closed>\n";
}

void Server::error(const char *msg)
{
    perror(msg);
    exit(1);
}
