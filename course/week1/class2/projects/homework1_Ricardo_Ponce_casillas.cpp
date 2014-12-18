#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

class Pair {
      
	public:
            double x, y;
            Pair() {x = 0; y=0;}
	    Pair(double x, double y) {this->x = x; this->y = y;}
	   ~Pair() {}
            double   X() const {return x;}
	    void  X(double x)  {this->x = x; }
	    double   Y() const {return y;}
	    void  Y(double y)  {this->y = y; }
            static bool sortBy_X(const Pair &pair1, const Pair &pair2) { return pair1.x < pair2.x; }        
            static bool sortBy_Y(const Pair &pair1, const Pair &pair2) { return pair1.y < pair2.y; }	  
};


double pitagoras(double PointX, double PointY, double X, double Y);


int main(int argc, char* argv[]){
 
  cout.precision(12);

  bool flagEx=false;
  string Target = "noname";  
  string Part;
  string name_found = "nono";
  double latitude = 0;
  double longitude = 0;
  double lat =0;
  double lon=0;
  vector<Pair>list;
  int index=0;
  int found=0;
  double distance =0;
  double compare = 100000000;


  ifstream myfile;
  myfile.open("test_data.data");



  if (!myfile.is_open()) {
     cerr<<"\nError in File: "<<"test_data.data"<<" \n\t-Please enter a valid file."<<endl;
     return 1;        
  }
 
  if (argc >= 2){
     Target = argv[1];            
     cout<<"\nCoordenate: \n\t" << Target;
     flagEx = true;
  }
  else{ 
     cout<<"\nError Missing Target. \n\t-Please provide argument \"PadtsBot[0-999999]\""<<endl;
     return 1;
  }

  if( flagEx == true ){
    while ( myfile.peek() != EOF ) {        
          getline(myfile,Part,',');                         
          myfile>>latitude;
          myfile.ignore();
          myfile>>longitude;
          myfile.ignore();
            
            if ( Part == Target ){
                flagEx = false;
                break;
                }
            }    

        if( flagEx == false )
            cout << " ( Latitude = " << latitude << ", Longitude = " << longitude << " )" << endl;        
        else{
            cerr << "\nError: " << Target << " was not found. \n\t-Please enter a valid name. " <<endl;
            myfile.close();
            return 1;        
        }
    }     

    myfile.clear();
    myfile.seekg(0, ios::beg);

    while ( myfile.peek() != EOF ) {        
          getline(myfile,Part,',');                         
          myfile>>lat;
          myfile.ignore();
          myfile>>lon;
          myfile.ignore();
          if( Part != Target )
	   {
             distance = pitagoras(latitude,longitude,lat,lon);
             if(compare > distance)
             {            			
                found = index;
	        compare = distance;
                name_found=Part;               

             }
          list.push_back( Pair(lat, lon) );
	  index++;
           }

    }
    if( compare != 100000000 ){
     cout << "\nClosest coordinate found is: \n";
     cout <<"\t"<< name_found <<" ( Latitude = " << list[found].x << ", Longitude = " << list[found].y << " )" << endl;
	}
	else
		cerr << "\nError: " << Target << " not found. Try Again" <<endl;

	myfile.close();
	return 0;
}

double pitagoras(double PointX, double PointY, double X, double Y){

    double x = PointX - X;
    double y = PointY - Y;
    double D;
    D = pow(x,2)+pow(y,2);
    D = sqrt(D);     
    return D;

}



