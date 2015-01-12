//
// 	Project:		Sockets
// 	File:			/home/wambitz/Workspace/SocketsServer/Server.h
//
//	Created on: 	Jan 7, 2015
//  Authors: 		Julio Alfonso Castillo Cruz & William Emilio Arrieta Lopez
//
#include "Socket.h"

Socket::Socket(int domain/*="AF_INET"*/, int type/*="SOCK_STREAM"*/, int protocol/*=0*/):
												domain_(domain), type_(type), protocol_(protocol)
{
	serverDescriptor_ = socket(domain_, type_, protocol_);
}

Socket::~Socket(){
	close(clientDescriptor_);
	close(serverDescriptor_);
}

void error(char* msg) {
	perror(msg);
	exit(1);
}

bool Socket::open(/*int serverDescriptor_*/) {
	if (serverDescriptor_ < 0) {
		error("ERROR opening socket");
	}
	bzero((char *) &serverAddress, sizeof(serverAddress)); // initialize with zeros
	return true;
}

bool Socket::bindPort(/*int portNumber_*/) {
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(portNumber_);
	if ( bind(serverDescriptor_, (struct sockaddr *) &serverAddress, sizeof(serverAddress) ) < 0){
	   error("ERROR on binding");
	}
	return true;
}

void Socket::listenForConnections(int attemps/*=5*/) {
	listen(serverDescriptor_, attemps); // Maximum length of pending connections
	printf("Waiting for client...\n");
}

bool Socket::acceptClient() {
	clientAddressLength = sizeof(clientAddress);
	clientDescriptor_ = accept(serverDescriptor_, (struct sockaddr *) &clientAddress, &clientAddressLength);
	if (clientDescriptor_ < 0) {
		error("ERROR on accept");
	}
	return true;
}

void Socket::readMessage(char* buffer) {
	int messageLenght;
	bzero(buffer, 256);
	messageLenght = read(clientDescriptor_, buffer, 255);
	if (messageLenght < 0) {
		error("ERROR reading from socket");
	}
	printf("Here is the message: %s\n",buffer);
}

void Socket::writeMessage(char* buffer/*="I got your message"*/, int messageLenght/*=18*/ ) {
	messageLenght = write(clientDescriptor_,"I got your message",18);	// sames as read, descrption above
	if (messageLenght < 0) {
		error("ERROR writing to socket");
	}
}

void Socket::writeToHost(char* buffer) {
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	int messageLenght = write(serverDescriptor_, buffer, strlen(buffer));	// sames as read, descrption above
	if (messageLenght < 0) {
		error("ERROR writing to socket");
	}
}

void Socket::readFromHost(char* buffer) {
	bzero(buffer,256);
	int messageLenght = read(serverDescriptor_,buffer,255);
	if (messageLenght < 0){
	   error("ERROR reading from socket");
	}
	printf("%s\n",buffer);
}

void Socket::setConnection(char* hostname) {
	struct hostent *host; // host data, like host name, IPV4, aliases, address, length ...
	host = gethostbyname(hostname);
	if (host == NULL) {
	   fprintf(stderr,"ERROR, no such host\n");
	   exit(0);
	}
	bzero((char *) &serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	bcopy((char *)host->h_addr,
	(char *)&serverAddress.sin_addr.s_addr,
	host->h_length);
	serverAddress.sin_port = htons(portNumber_);
	return;
}

bool Socket::connectToHost() {
	if ( connect(serverDescriptor_, (struct sockaddr *) &serverAddress, sizeof(serverAddress) )  < 0)
		error("ERROR connecting");
	return true;
}



