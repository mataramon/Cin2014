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

double Calc_Distance(double x1, double y1, double x2, double y2){
    double x = x1 - x2;
    double y = y1 - y2;
    double dist;
    dist = pow(x,2)+pow(y,2);
    dist = sqrt(dist);     
    return dist;
}

int main()
{
       
    
       string Bot;
       char File[200];
       string Name,Target;
    	double lattitude,longitude,dist;
        vector<Pair> dlist;
        double latIN = 0;
        double lonIN = 0;
        Target = "none";    
        bool ext = true; 
        bool found = false;

       cout<<"Please Enter the Name and Path of the file to open:"<<endl;
       cin>>File;
       cout<<"Enter the Name of the Bot to search:"<<endl;
       cin>>Bot;
                   
    
    ifstream myReadFile;
    myReadFile.open(File);
  
     if (!myReadFile.is_open()) {
        cerr<<"\nError in File: \n"<<File<<"  Provide a valid file name. \n" << endl;
        return 1;        
    }

    else{
	        
	while ( myReadFile.peek() != EOF ) {
            getline(myReadFile,Name,',');                         
            myReadFile>>latIN;
            myReadFile.ignore();
            myReadFile>>lonIN;
            myReadFile.ignore();
           
		if ( Name == Bot ){
                ext = false;
                break;
                }
         }    

        if( ext == false )
            {cout<<"\nBot was found : "<<Bot<<endl;
            cout << "Lat = " << latIN<<endl;
            cout << "Lon = " << lonIN<< endl; }   
        else{
            cerr << "\nError: " << Bot << " was not found. \n" << endl;
            myReadFile.close();
            return 1;        
        }
    }                


    myReadFile.clear();
    myReadFile.seekg(0, ios::beg);

   int index=0;
    while ( myReadFile.peek() != EOF ) {           
        getline(myReadFile,Name,',');                         
        myReadFile>>lattitude;
        myReadFile.ignore();
        myReadFile>>longitude;
        myReadFile.ignore();
        dist=Calc_Distance(latIN, lonIN, lattitude, longitude);
       
        if ( Name == Bot )
            dist += 7;  
        dlist.push_back( Pair(index++, dist) );          
        } 

    stable_sort( dlist.begin(), dlist.end(), Pair::sortBy_Y);

 
    myReadFile.clear();
    myReadFile.seekg(0, ios::beg);
    
   
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
        cout << "\nClosest Bot found is: " << Name<<endl;
        cout << "Lat = " << lattitude <<endl;
        cout << "Lon = " << longitude << endl; 
        cout<<" \n\n";      
    }else
        cerr << "\nError: " << Bot << " was not found" <<endl;

    myReadFile.close();

return 0;
}
