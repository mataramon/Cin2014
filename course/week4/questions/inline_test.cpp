#include <iostream>

using namespace std;

inline int square(int a, int b) { 
  return (a*a + b*b);
}


int main(){
  square(10,11);
  square(14,43);
  square(43,10);
 
  return 0;
}

