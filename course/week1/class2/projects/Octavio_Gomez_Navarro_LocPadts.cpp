/*
Author: Octavio Gómez Navarro
Homework 1 C++ PadtsBot Finder
This program works with 1 parameter, the name of the PadtsBot# to find. Please use file, containing Bots, named test_data.data in the same folder.
*/
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
// Pairs Coord, taken from vector_example.cpp.
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
        static bool sortBy_X(const Pair &pair1, const Pair &pair2) { return pair1.x < pair2.x; }
        static bool sortBy_Y(const Pair &pair1, const Pair &pair2) { return pair1.y < pair2.y; }
};
// Distance
double CalcDist(double x1, double y1, double x2, double y2){
    double x = x1 - x2;
    double y = y1 - y2;
    double distance;
    distance = pow(x,2)+pow(y,2);
    distance = sqrt(distance);     
    return distance;
}
int main (int argc, char* argv[]){
	double latitude, longitude, distance;
	double latitudeH = 0;
	double longitudeH = 0;
	int index = 0;
	string helpname = "none";
	string name = "none";
	string findname = argv[1];
	vector<Pair> listV;
	bool found = false;
	bool notfound = false;
	int LocVec = 0;
	ifstream file;
	file.open("test_data.data");
	if (!file.is_open()) {
		cerr<<"\n\tError... no such file or directory (test_data.data)\n"<<endl;
		return 0;
		}
	while (!file.eof()){
		getline(file,helpname,',');
		file>>latitude;
		file.ignore();
		file>>longitude;
		file.ignore();
		if ((helpname == findname) && (found == false)){
			latitudeH = latitude;
			longitudeH = longitude;
			cout << "\nTarget: " << helpname << "\nLatitude: " << latitudeH << ", Longitude: " << longitudeH << "\n";
			LocVec = index;
			file.clear(); //Starting to reset values for next iteration.
			file.seekg(0, ios::beg);
			listV.clear();
			index = 0;
			found = true;
			continue;
			}
		distance = CalcDist(latitudeH, longitudeH, latitude, longitude);
		listV.push_back(Pair(index, distance)); //Making vector (index, distance from target).
		index++;
		}
	if (found == false){cout << "Try a different name with format like (PadtsBot#)";}
	stable_sort( listV.begin(), listV.end(), Pair::sortBy_Y);
	file.seekg(listV[1].Y()+1, ios::beg); // Seeks line matching the closest index.
	getline(file, helpname, ',');
	file>>latitude;
	file.ignore();
	file>>longitude;
	file.ignore();
	cout << "\nClosest to " << findname << "\nPadtsBot" << listV[1].X() << "\nLatitude: " << latitude << ", Longitude: " << longitude << "\n";
return 0;
}
