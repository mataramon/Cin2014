//
// 	Project:		Sockets
// 	File:			/home/wambitz/Workspace/SocketsServer/Server.h
//
//	Created on: 	Jan 7, 2015
//  Authors: 		Julio Alfonso Castillo Cruz & William Emilio Arrieta Lopez
//

#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdio.h>						// Standar input/ouput
#include <stdlib.h>						// Standar library
#include <string.h>						// Strings library
#include <unistd.h>
#include <sys/types.h> 					// This header contains definitions of data types used in system calls.
#include <sys/socket.h>					// The header file socket.h includes of definitions of structures needed for sockets
#include <netinet/in.h>					// Library for client, hostent struct definition inside
#include <netdb.h> 						// The variable host is a pointer to structure type hostent.
										// This structure is defined in the header file netdb.h

class Socket {

	private:
		// cost int AF_INET = 2;
		// const int SOCK_STREAM = 1;
		// protocol = 0 ; If  0 is specified, caller does not specify a protocol and service provider will choose the one to use.
		struct sockaddr_in serverAddress, clientAddress;
		socklen_t clientAddressLength;
		int serverDescriptor_;
		int clientDescriptor_;
		int portNumber_;
		int domain_;
		int type_;
		int protocol_;

	public:
		Socket(int domain=AF_INET, int type=SOCK_STREAM, int protocol=0); 	// constants defined in <sys/socket.h>
		~Socket();
		int portNumber() { return portNumber_; }
		void portNumber(int portNumber) { this-> portNumber_ = portNumber; }
		bool open(); 														// int serverDescriptor_*/
		bool bindPort();													// int serverDescriptor_, struct sockadder* &serverAddress, int portNumber_
		void listenForConnections(int attemps=5);
		bool acceptClient(); 												// int serverDescriptor_, struct sockadder* &clientAddress, int sizeof(clienAddress);
		void readMessage(char* buffer);
		void writeMessage(char* buffer="I got your message", int messageLenght=18);
		void setConnection(char* string);
		bool connectToHost();
		void writeToHost(char* buffer);
		void readFromHost(char* buffer);
};

#endif /* SOCKET_H_ */

