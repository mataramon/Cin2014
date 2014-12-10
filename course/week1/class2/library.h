#ifndef LIBRARY_H
#define LIBRARY_H
// Libraries
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
	pi = 3.1415927;
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


#endif
