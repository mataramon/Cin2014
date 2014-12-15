// ================================================================
// Title: Homework 1
// Author: César López
// Class: C++ / Padts Dec 2014   
// ================================================================
// Description: Find closest coordenate.
// ================================================================

#include <iostream>             // Input/Output streams
#include <fstream>              // Files stream
#include <math.h>               // Math 
#include <vector>               // Vector
#include <algorithm>            // Sort Algorithm

using namespace std;

class Pair {
      double x, y;
	public:
        Pair() {x = 0; y=0;  }                                      // Constructor
	    Pair(double x, double y) {this->x = x; this->y = y; }       // Inicializa datos 
	   ~Pair() {}                                                   // Destructor
        double   X() const {return x;}                              // Accesa dato X
	    void  X(double x)  {this->x = x; }                          // Asigna solo X
	    double   Y() const {return y;}                              // Accesa dato Y
	    void  Y(double y)  {this->y = y; }                          // Asigna dato Y
        static bool sortBy_X(const Pair &pair1, const Pair &pair2) { return pair1.x < pair2.x; }        // Ordena para X	    
        static bool sortBy_Y(const Pair &pair1, const Pair &pair2) { return pair1.y < pair2.y; }	    // Ordena para Y    

};

// Calcular distancia eucludiana entre puntos
double distanceCalc(double x1, double y1, double x2, double y2){
    double x = x1 - x2;
    double y = y1 - y2;
    double dist;
    dist = pow(x,2)+pow(y,2);
    dist = sqrt(dist);     
    return dist;
}

int main(int argc, char* argv[]){
//************** Initialization 
    //Data initialization
    string Name,Target;
    double lat,lon,dist;
    vector<Pair> dlist;
    string File = "test_data.data";
    //Default Values initialization    
    double latIN = 0;
    double lonIN = 0;
    Target = "none";    
    //Counters & Flags
    bool extract = false; 
    bool found = false;  
    
//*************** Checking Arguments 
    if (argc >= 2){
        Target = argv[1];            
        cout<<"\nFile: " << File << "\n\nSearching for the closest coordenate to: \n\t" << Target;
        extract = true;
    }
    else{ 
        cout<<"\nError Missing Target point. \n\t-Please provide argument \"PadtsBot[0-999999]\""<<endl;
        return 1;
    }
    cout.precision(10);
                       
//********** Opening File      
    ifstream myReadFile;
    myReadFile.open(File);

    if (!myReadFile.is_open()) {
        cerr<<"\nError in File: "<<File<<" \n\t-Please enter a valid file."<<endl;
        return 1;        
    }

//*********** Extracting coordenates from Target
    if( extract == true ){
        while ( myReadFile.peek() != EOF ) {  // If EOF flagbit is set during the call, the function returns (EOF) value.         
            getline(myReadFile,Name,',');                         
            myReadFile>>latIN;
            myReadFile.ignore();
            myReadFile>>lonIN;
            myReadFile.ignore();
            
            if ( Name == Target ){
                extract = false;
                break;
                }
            }    

        if( extract == false )
            cout << " ( Lat = " << latIN << ", Lon = " << lonIN << " )" << endl;        
        else{
            cerr << "\nError: " << Target << " was not found. \n\t-Please enter a valid name. " <<endl;
            myReadFile.close();
            return 1;        
        }
    }                

//*************** Restart File stream pointer 
    myReadFile.clear();
    myReadFile.seekg(0, ios::beg);

//***************** AÑADE ELEMENTOS AL VECTOR = (INDEX,DISTANCIA)         
    int index=0;
    while ( myReadFile.peek() != EOF ) {  // If EOF flagbit is set during the call, the function returns (EOF) value.         
        getline(myReadFile,Name,',');                         
        myReadFile>>lat;
        myReadFile.ignore();
        myReadFile>>lon;
        myReadFile.ignore();
        dist=distanceCalc(latIN	,lonIN, lat, lon);
       
        if ( Name == Target )
            dist += 7;  
        //cout<<Name<<":"<<dist<<endl;
        dlist.push_back( Pair(index++, dist) );          
        } 

//**************** ORDENA EL VECTOR POR DISTANCIAS
    stable_sort( dlist.begin(), dlist.end(), Pair::sortBy_Y);

//*************** Restart File stream pointer 
    myReadFile.clear();
    myReadFile.seekg(0, ios::beg);
    
//************** Look for the closest    
    int Match = dlist[0].X(); 
    double minDist = dlist[0].Y();       
    int j = 0;
      
    while ( myReadFile.peek() != EOF ) {  // If EOF flagbit is set during the call, the function returns (EOF) value.         
        getline(myReadFile,Name,',');                         
        myReadFile>>lat;
        myReadFile.ignore();
        myReadFile>>lon;
        myReadFile.ignore();
           
        if ( j == Match ){
            found = true;
            break;
            }else
                j++;
        }

    if( found == true ){
        cout << "\nClosest coordinate found is: \n\t" << Name;
        cout << " ( Lat = " << lat << ", Lon = " << lon << " )" << endl;        
    }else
        cerr << "\nError: " << Target << " was not found. :( Try Again" <<endl;

//*************** Close file
    myReadFile.close();
    
return 0;
}


