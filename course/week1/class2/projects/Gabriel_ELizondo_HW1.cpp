//Gabriel Elizondo Maga~a
//find two points with coordenates


//Libraries
#include <iostream>            
#include <fstream>            
#include <math.h>               
#include <vector>               
#include <algorithm>           

using namespace std;

class Pair {
      double x, y;
	public:
        // Constructor
	    Pair() {x = 0; y=0;  }                                      
	    Pair(double x, double y) {
		this->x = x; this->y = y; }       
	  // Destructor
	   ~Pair() {}                                                   
            double   X() const {return x;}                              
	    void  X(double x)  {this->x = x; }                          
	    double   Y() const {return y;}                             
	    void  Y(double y)  {this->y = y; }                          
        // sorts for x
	    static bool sortBy_X(const Pair &pair1, const Pair &pair2) { 
		return pair1.x < pair2.x; }        
	//sorts for y	    
        static bool sortBy_Y(const Pair &pair1, const Pair &pair2) { 
		return pair1.y < pair2.y; }	        

};

double Calc_Distance(double x1, double y1, double x2, double y2);

int main(int argc, char* argv[]){
   
	string Name,Target;
    	double lattitude,longitude,dist;
        vector<Pair> dlist;
        string File = "test_data.data";  
        double latIN = 0;
        double lonIN = 0;
        Target = "none";    
        bool ext = false; 
        bool found = false;  
    
// checking if the arguments are true
if (argc >= 2){
        Target = argv[1];            
        cout<<"\nFile: " << File << "Searching for the neareste Coordenate: \n" << Target;
        ext = true;
       }
       else {
	cerr << "coordenate not found " << endl ;
         }
	//vector preccision
    cout.precision(10);
                       
//open file      
    ifstream myReadFile;
    myReadFile.open(File);

    if (!myReadFile.is_open()) {
        cerr<<"\nError in File: \n"<<File<<"  Provide a valid file name. \n" << endl;
        return 1;        
    }

//taking out the coordenates from search place. 
    if( ext == true ){
	//continue running during EOF its not found.        
	while ( myReadFile.peek() != EOF ) {
            getline(myReadFile,Name,',');                         
            myReadFile>>latIN;
            myReadFile.ignore();
            myReadFile>>lonIN;
            myReadFile.ignore();
            //check if the name its the target
		if ( Name == Target ){
                ext = false;
                break;
                }
         }    

        if( ext == false )
            cout << " ( Lat = " << latIN << ", Lon = " << lonIN << " ) \n" << endl;        
        else{
            cerr << "\nError: " << Target << " was not found. \n" << endl;
            myReadFile.close();
            return 1;        
        }
    }                

//Restart File stream pointer 
    myReadFile.clear();
    myReadFile.seekg(0, ios::beg);

//Add elements to a vector          
    int index=0;
    while ( myReadFile.peek() != EOF ) {           
        getline(myReadFile,Name,',');                         
        myReadFile>>lattitude;
        myReadFile.ignore();
        myReadFile>>longitude;
        myReadFile.ignore();
        dist=Calc_Distance(latIN, lonIN, lattitude, longitude);
       
        if ( Name == Target )
            dist += 7;  
        dlist.push_back( Pair(index++, dist) );          
        } 

//Sorts vector by Distances
    stable_sort( dlist.begin(), dlist.end(), Pair::sortBy_Y);

//Restart File stream pointer 
    myReadFile.clear();
    myReadFile.seekg(0, ios::beg);
    
//Look for the closest    
    int Match = dlist[0].X(); 
    double minDist = dlist[0].Y();       
    int j = 0;
      
    while ( myReadFile.peek() != EOF ) {  
        getline(myReadFile,Name,',');                         
        myReadFile>>lattitude;
        myReadFile.ignore();
        myReadFile>>longitude;
        myReadFile.ignore();
           
        if ( j == Match ){
            found = true;
            break;
            }else
                j++;
        }

    if( found == true ){
        cout << "\nClosest coordinate found is: \n" << Name;
        cout << " ( Lat = " << lattitude << ", Lon = " << longitude << " )" << endl;        
    }else
        cerr << "\nError: " << Target << " was not found. Try Again if you like" <<endl;

    myReadFile.close();
    
return 0;
}

//calculates distance between points
double Calc_Distance(double x1, double y1, double x2, double y2){
    double x = x1 - x2;
    double y = y1 - y2;
    double dist;
    dist = pow(x,2)+pow(y,2);
    dist = sqrt(dist);     
    return dist;
}

