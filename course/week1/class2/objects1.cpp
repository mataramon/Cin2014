#include <iostream>
using namespace std;

// Definition
class Circle {
     private: 
        double radio;
        double pi;
     public:
        Circle(double); // Adquiring resources
       ~Circle(); // Release of resources
        double area();
        double diameter();
};
// End definition

// Implementation
Circle::Circle(double Radio){
     radio = Radio;
     pi    = 3.1415927;
}

Circle::~Circle(){
     // No resource alocated 
}

double Circle::area(){
     return radio*pi*pi; 
}

double Circle::diameter(){
     return 2.0*radio;
}
// End Implementation

// This function helps to start the plotter

int main(){
    cout<<"This is a circle\n";
    Circle OurCircle(10);
    cout<<"Area of the circle "<<OurCircle.area()<<"\n";
    cout<<"Diameter of the circle "<<OurCircle.diameter()<<"\n";
    return 0;
}
