#include <iostream>
#include <string>

using namespace std;

struct SCoordenada{
       long latitude;
       long longitude;
};


class Coordenada{
	double latitude;
	double longitude;
	string Name;
	public:
	    Coordenada();
	    Coordenada(string);
	   ~Coordenada();
	  // Accessors
	  double Latitude(){return latitude;}
	  void Latitude(double lat){latitude = lat;}
};

Coordenada::Coordenada(){ 
       cout<<latitude<<"\n";
       cout<<longitude<<"\n";
       latitude  = 0;
       longitude = 0;
}

Coordenada::Coordenada(string Name){
       this->Name = Name;
}

Coordenada::~Coordenada(){ 
       cout<<"Adios mundo cruel\n";
       cout<<Name<<"\n";
}

int main(){
   cout<<"Hola padts\n";
   SCoordenada padts1;
   padts1.latitude = long(1.200202);
   {
     Coordenada padts3("Torito");
   }
     
   Coordenada padts2("Diego");
   padts2.Latitude(2.20099999);
   cout<<padts2.Latitude()<<"\n";

   return 1;
}

