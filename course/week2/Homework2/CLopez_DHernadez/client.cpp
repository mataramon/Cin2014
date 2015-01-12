/*
Homework 2
Authors: Diego Hernandez Ramirez, César López López
*/

#include "client.h"

/*  Body of functions */
Client::Client(){

	sock=-1; //Initialize the 
	port=0;  //Values used in
	address=""; //this function
}

/* Conect to a server on a certain port number */
bool Client::connect_t(string address, int port){

	if(sock==-1){ //Is the socket already created?
		sock = socket(AF_INET , SOCK_STREAM , 0);
		if (sock == -1) {
            perror("<Could not create socket>\n");
        }
        cout<<"<Socket created>\n";
	} 

	if(inet_addr(address.c_str()) == -1){
		struct hostent *he;
        struct in_addr **addr_list;
        //Resolve hostname
        if ( (he = gethostbyname( address.c_str() ) ) == NULL){
        	perror("gethostbyname");
        	cout<<"<Failed to resolve hostname>\n";
        	return 1;
        }
        addr_list=( struct in_addr** ) he->h_addr_list;
        for( int i =0; addr_list[i] !=NULL; i++ ){
        	server.sin_addr=*addr_list[i];
        	cout<<address<<" <resolved to> "<<inet_ntoa(*addr_list[i])<<endl;
        	break;
        }
	}
	else{
		server.sin_addr.s_addr=inet_addr( address.c_str() );
	}

	server.sin_family=AF_INET;
	server.sin_port=htons( port );

	//Connect to remote server
	if(connect(sock, (struct sockaddr *) &server, sizeof(server)) <0 ){
		perror("<Connect failed. Error>\n");
		return 1;
	}
	cout<<"<Connected>\n\n";
	return true;
}

//Send data
bool Client::send_data(string data){

	if( send(sock, data.c_str(), strlen( data.c_str() ) , 0 ) < 0 ){
		perror("<Send failed: >\n");
		return false;
	}
	cout<<"\n<Data send>\n";
	return true;
}

string Client::receive(int size=1024){ //It's a joke, put 128 and works fine :-)
	char buffer[size];
	string reply;

	if( recv(sock, buffer, sizeof(buffer), 0) < 0 ){
		puts("<recv failed>");
	}
	reply=buffer;
	return reply;
}
