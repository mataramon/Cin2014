#include <iostream>
#include "data.h"

using namespace std;

int main(){
    cout<<"Compilation example\n";
    Complex a(3.3, 9.9);
    Complex z = a*a;
    cout<<z.X()<<" - "<<z.Y()<<"\n";
}
