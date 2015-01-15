/* Pregunta diferencia de malloc y new en c++ */
#include <iostream>

using namespace std;

class Padts{
   
   public:
       static int counter;
       Padts(){
          cout<<"Calling the constructor\n"; 
          counter++; 
          a=0; 
          b=0;
       }
       Padts(int a, int b){ 
         this->a=a;
         this->b=b;
         counter++;
       }
      ~Padts(){
         cout<<"Good bye awful word\n";
         counter--;
       }
       int multiply(){return a*b; }
       
   private:
       int a;
       int b;
};

// Starting the statics
int Padts::counter = 0;

int main(){
  
  // C++
  auto array   = new Padts[3];
  auto element = new Padts(10,4);
  
  cout << "Total:" << Padts::counter << "\n";  

  // C Raw memory
  
  Padts* element_c = (Padts*)malloc(sizeof(Padts));
  //new (element_c) Padts(3,4);

  cout << "Total:" << Padts::counter << "\n";
  
  // Release
  // element_c->~Padts();
  delete element;
  delete [] array;
  free(element_c);
  
  return 0;
}
