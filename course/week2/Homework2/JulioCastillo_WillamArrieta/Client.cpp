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
	char *hostName;

	if (argc < 3) {
		 fprintf(stderr,"usage %s hostname port\n", argv[0]);
	     exit(0);	// exit false
	}

	Socket client;
	if (client.open()){ 																// open socket else error
			cout << "Server socket successfully open." << endl;
	}
	portNumber = atoi(argv[2]);
	hostName = argv[1];
	client.portNumber(portNumber);
	client.setConnection(hostName);
	client.connectToHost();
	 cout << "Please enter the message: ";
	 client.writeToHost(buffer);
	 client.readFromHost(buffer);
	 // Close connections ~Sockets();

	 return 0;
}

/*
	 Socket client;
	 client.open();
	 portNumber = atoi(argv[2]);
	 hostName = argv[1];
	 client.portNumber(portNumber);
	 client.setConnection(hostName);
	 client.connectToHost();
	 cout << "Please enter the message: ";
	 client.writeToHost(buffer);
	 client.readFromHost(buffer);
	 // Close connections ~Sockets();
*/


