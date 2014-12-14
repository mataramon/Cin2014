#ifndef DATA_H
#define DATA_H

#include <vector>
#include <iostream>

class Complex{
      private:
          double x;
          double y;

      public:
          Complex();
          Complex(double x, double y){this->x = x; this->y = y;}
         ~Complex(){}

     // Accesors
     double    X()const {return this->x;}
     double    Y()const {return this->y;}     
     
     void      X(double x) {this->x = x;}
     void      Y(double y) {this->y = y;}

     // Operations (Sum, rest, multiplication, and plotting) 
     
     Complex& operator=(const Complex&);
     Complex& operator+(const Complex&) const;
     Complex& operator-(const Complex&) const;
     Complex& operator*(const Complex&) const;
     
};

#endif 
