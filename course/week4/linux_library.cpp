#include <iostream>
#include <string>
using namespace std;

int myFoo(){
    cout<<"Hello I'm your library\n";
    return 1;
}

// Your interface which is c style 
extern "C" {
    int myRealC(){
       myFoo();
       cout<<"I'm your c/c++ function hello!\n";
       return 10;
    }
    
    void Message(int len, char* cool){
        cout<<"Hello :"<<cool<<"\n";
        cout<<"len:"<<len<<"\n";

    }

}

