//**************************************************************************************************************
// File:        Project_1
// Description: Give a specific name of coordenada and the program will shearch the nearest ubication 
// Author:      Jose Antonio Valdez Rodriguez
//**************************************************************************************************************

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

class Coordenada{

	public:
		double x,y;
		Coordenada(){ x = 0; y = 0; } // Constructor
		Coordenada(double x, double y){ this->x = x; this->y = y;}
	  ~Coordenada(){};// Destructor
		double X() const { return x; }
		double Y() const { return y; }
		static bool sortBy_X(const Coordenada &coordenada1, const Coordenada &coordenada2){ return coordenada1.x < coordenada2.x; }
		static bool sortBy_Y(const Coordenada &coordenada1, const Coordenada &coordenada2){ return coordenada1.y < coordenada2.y; }
};

int main(){

	string Location,Name,FinalName;
	double InitLat	 = 0;
	double InitLong = 0;
	int    Iterator = 0;
	double InitDist = 1000000000;
	double Latitude, Longitude, Distance;
	int    Index = 0;
	bool   LocationFound = false;
	fstream File;
	vector<Coordenada> DistancesList;
	

	cout << "Give the name location you want to know" << endl;
	cin >> Location;

	//Open the File
	File.open("test_data.data", ios::in);
	//File >> texto;
	while (!File.eof())
	{
		getline(File,Name,',');
		File >> InitLat;
		File.ignore();
		File >> InitLong;
		File.ignore();
		if( Name == Location )
		{
			LocationFound = true;	
			break;	
		}
	}

	if( LocationFound == true )
		cout << Name << "-> ( Latitude = " << InitLat << ", Longitude = " << InitLong << " )\n" << endl;
	else
	{
		cerr << "Error: " << Location << " was not found. \n-Please enter a valid name. " << endl;
		File.close();
	}

	while (!File.eof())
	{
		getline(File,Name,',');
		File >> Latitude;
		File.ignore();
		File >> Longitude;
		File.ignore();
		if( Name != Location )
		{
			Distance = ( InitLat - Latitude )*( InitLat - Latitude ) + ( InitLong - Longitude )*( InitLong - Longitude );
				if( InitDist > Distance )
				{
					Index = Iterator;
					InitDist = Distance;
					FinalName = Name;
				}
				DistancesList.push_back( Coordenada(Latitude, Longitude) );
				Iterator ++;
		}
	}


	if( InitDist != 1000000000 )
	{
		cout << "Closest Location Found:" << endl;
		cout << FinalName << " ( Latitude = " << DistancesList[Index].x << ", Longitude = " << DistancesList[Index].y << " )" << endl;
	}
	else
		cerr << "Error" << endl;

	File.close();
	return 0;
}
