/*
Homework 2
Authors: Diego Hernandez Ramirez, César López López
*/

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring> // For strlen
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

class Client{
	private:
		int sock;
		string address;
		int port;
		struct sockaddr_in server;

	public:
		Client();
		bool connect_t(string, int);
		bool send_data(string data);
		string receive(int);
};

#endif
