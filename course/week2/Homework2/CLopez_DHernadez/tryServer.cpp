/*
Homework 2
Authors: Diego Hernandez Ramirez, César López López
*/

#include "server.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{   
    if (argc < 2) 
    {
        cerr<<"ERROR, no port provided\n";
        exit(1);
    }
    
    int portin = atoi(argv[1]);
    Server Monarquia(portin);
       
    return 0; 
}
