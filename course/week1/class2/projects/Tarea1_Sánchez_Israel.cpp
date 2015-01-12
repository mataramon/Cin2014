#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

class Pair
{
   double x, y;
   public:
   Pair(){x = 0; y = 0;}
   Pair(double x, double y){this-> x = x; this -> y = y;} 
   ~Pair(){}
   double X() const {return x;}
   void X(double x) {this ->x = x;} 
   double Y() const {return y;}
   void Y(double y) {this ->y = y;}
   static bool type_x(const Pair &pair1, const Pair &pair2){return pair1.x < pair2.x;}
   static bool type_y(const Pair &pair1, const Pair &pair2){return pair1.y < pair2.y;}
};

double path (double x1, double y1, double x2, double y2)
   {
   double x = x1 - x2;
   double y = y1 - y2;
   double dtce;
   dtce = pow(x,2)+pow(y,2);
   dtce = sqrt(dtce);
   return dtce; 
   }

int main (int argc, char* argv[])
  {
  double lat = 0;
  double lon = 0;
  double dtce, x, y;
  bool open = false;
  bool close = false;
  int a = 0;
  int b = 0;
  vector <Pair> one;
  string point, dot;
  string clear = argv[1];
  point = "none";


if ( argc >= 2)
 {
 point = argv[1];
 open = true;
 }


ifstream myfile;
myfile.open("test_data.data");

if(!myfile.is_open())
 {
 cout << "\n no such file, check populate_locate.py\n" << endl;
 return 0;
}


if ( open == true)
{
	while (myfile.peek() != EOF)
      {
	getline(myfile,dot,',');
	myfile>>lat;
	myfile.ignore();
	myfile>>lon;
	myfile.ignore();
        dtce = path (x, y, lat, lon);
        one.push_back(Pair(a, dtce));
        a++;

      if (dot == point)
        {
        open = false;
        break;
        }

      }

      if(open == false)
        {
        x=lat;
        y=lon;
        cout << "La coordenada de " << point << " es:" << endl;
        cout<<"latitude -  "<<lat<<"\n"<<"longitud - "<<lon<<"\n"<< endl;
	
	b = a;
        myfile.clear();
        myfile.seekg(0, ios::beg);
        one.clear();
        a = 0;
        }
}


	       
 
while (myfile.peek() != EOF)
      {
   
	getline(myfile,dot,',');
	myfile>>x;
	myfile.ignore();
	myfile>>y;
	myfile.ignore();
        dtce = path (x, y, lat, lon);
        one.push_back(Pair(a, dtce));
        a++; 
      }

stable_sort(one.begin(), one.end(), Pair::type_y);
myfile.seekg(one[1].Y()+1, ios::beg);

        getline(myfile,dot,',');
	myfile>>lat;
	myfile.ignore();
	myfile>>lon;
	myfile.ignore();
        cout << "El punto más cercano es:"<< endl;
        cout<< "PadtsBot -  " << one[1].X() << endl;
       

return 0;
}
