#include <iostream>
#include <string>

using namespace std;

struct SCoordenada{
       long latitude;
       long longitude;
};


class Coordenada{
	long latitude;
	long longitude;
};

int main(){
   cout<<"Hola padts\n";
   SCoordenada padts1;
   padts1.latitude = long(1.200202);

   Coordenada padts2;

   return 1;
}

