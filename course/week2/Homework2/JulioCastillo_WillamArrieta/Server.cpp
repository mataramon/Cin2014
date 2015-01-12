//
// 	Project:		Sockets
// 	File:			/home/wambitz/Workspace/SocketsServer/main_server.cpp
//
//	Created on: 	Jan 7, 2015
//  Authors: 		Julio Alfonso Castillo Cruz & William Emilio Arrieta Lopez
//
#include <stdio.h>
#include <iostream>

#include "Socket.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

	int portNumber;
	char buffer[256];

	if (argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}
	
	Socket server;																// Default: Socket server(int domain=AF_INET, int type=SOCK_STREAM, int protocol=0); 
	server.open();
	portNumber = atoi(argv[1]);
	server.portNumber(portNumber);
	server.bindPort();
	server.listenForConnections();
	server.acceptClient();
	server.readMessage(buffer);
	server.writeMessage();												// Default: writeMessage(char* string, )
	// Close connections ~Sockets();
	
	return 0;
}

/* CODE WITH MESSAGES: 
	// first, open socket
	Socket server;
	if (server.open()){ 																// open socket else error
		cout << "Server socket successfully open." << endl;
	}

	// second, bind socket, checks port availability
	portNumber = atoi(argv[1]);
	server.portNumber(portNumber);
	if (server.bindPort()) {															 // bind server on given port else error
		cout << "Server socket successfully bind at port: " << server.portNumber() << endl;
	}

	// listen to connections
	server.listenForConnections();
	// connect server-client
	if (server.acceptClient()) { 														// accept clients else error
		cout << "Connection with client stablished." << endl;
	}

	// Read from client and write to client
	server.readMessage(buffer);
	server.writeMessage();																// writeMessage(char* string, )

	// Close connections ~Sockets();
	*/
