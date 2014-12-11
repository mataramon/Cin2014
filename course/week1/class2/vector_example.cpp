#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>


using namespace std;


class Pair {
      int x, y;
	public:
            Pair() {x = 0; y=0;}
	    Pair(int x, int y) {this->x = x; this->y = y;}
	   ~Pair() {}
            int   X() const {return x;}
	    void  X(int x)  {this->x = x; }
	    int   Y() const {return y;}
	    void  Y(int y)  {this->y = y; }
};


int main(int argc, char* argv[]){
     // Numero de elementos en el vector
     int items = 10; 

     cout<<"====================================\n";
     cout<<" EXAMPLE WORKING WITH VECTOR\n";
     cout<<"=====================================\n";
     cout<<"Working with the following parameters "<<argc<<"\n";
     for (int i=0; i<argc;i++){
          cout<<" [ "<<argv[i]<<" ]\n";
     }

     // Conversion del segundo parametro 
     if (argc >= 2){
     	try {
            items = atoi(argv[1]);
            if (!items){
	       items = 10;
	       cout<<"Error: cannot convert "<<argv[1]<<" to int\n";
	    }

     	}catch(...){
            cout<<"Error: exception in conversion";
     	}
     }
     
     // Lista de elementos en pares
     vector<Pair> list;
     cout<<"items:"<<items<<endl;
     // añadiendo elementos al vector     
     for (int i = 0; i < items ;i++){
         list.push_back(Pair(i+1,i*i));
     }
     
     // Iterando c++98
     for (vector<Pair>::iterator i = list.begin(); i != list.end(); i++){
          cout<<"->  "<<i->X()<<"-"<<i->Y()<<"\n";  
     }

     // Si agregan la flag -std=c++11 al g++ vector_example.cpp -o outputfile, al compilar 
     // y descomenten los fors del siguiente bloque
     /*
         for (auto i = list.begin(); i != list.end(); i++)
	     cout<<"->  "<<i->X()<<"-"<<i->Y()<<"\n";
         
	 for (auto& i : list)
	     cout<<"->  "<<i.X()<<"-"<<i.Y()<<"\n";

     */


    return 0;
}
