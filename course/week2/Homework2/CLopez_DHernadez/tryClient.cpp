/*
Homework 2
Authors: Diego Hernandez Ramirez, César López López
*/

#include "client.h"

int main( int argc, char *argv[] ){
	// Construct the fucking object
	Client Dinero;
	string aprende_algo_dinero;
	int portno;
	string server;

	if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       return 0;
    }

    portno = atoi(argv[2]);
    server = (argv[1]);
    Dinero.connect_t(server, portno);

    cout<<"Please enter the mensaje: ";
    cin>>aprende_algo_dinero;
    Dinero.send_data(aprende_algo_dinero);
    Dinero.receive(1024);

    return 0;
}
