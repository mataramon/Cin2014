#include "data.h"

Complex& Complex::operator = (const Complex& b){
      this->x = b.x;
      this->y = b.y;      
      return *this;  
}
   
Complex& Complex::operator+(const Complex& b)const{
      Complex* rt =  new Complex(b.x + x, b.y + y);
      return *rt;
}

Complex& Complex::operator-(const Complex& b)const{
      Complex* rt = new Complex(x - b.x, y - b.y);
      return *rt;
}

Complex& Complex::operator*(const Complex& b)const {
      Complex* rt = new Complex(x*b.x, y*b.y);
      return *rt;
}

