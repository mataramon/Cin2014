// =================================================================================================
// Author: 	 Julio Castillo
// File: 	 NearPointFinder.cpp
// Date:	 December 15th 2014
// =================================================================================================
#include <iostream>					// Input/Output stream
#include <fstream> 					// File management
#include <string>					// String class
#include <vector>					// Collection  template
#include <algorithm>				// Sorting and manipulation collections

#include "MeasureDistance.h"
#include "FindPoint.h"
#include "Point.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::sort;

//bool sortDistances(Point& point1, Point& point2) {
//	return point1.distanceToOrigin() < point1.distanceToOrigin();
//}

int main(int argc, char* argv[]){

	double pointLatitude = 0;  		// near point changing variables
	double pointLongitude = 0; 		// near point changing variables
	string tempTag;
	string originTag = argv[1]; 		// PadtsBot0
	string file = argv[2];				// test_data.data
	vector<Point> points;
	FindPoint origin(originTag, file);
	origin.findCoordinates();

	ifstream fileHandler (file.c_str());
	while ( fileHandler.peek() != EOF ) {
		getline( fileHandler, tempTag, ',' );
		fileHandler >> pointLatitude;
		fileHandler.ignore();
		fileHandler >> pointLongitude;
		fileHandler.ignore();
		MeasureDistance distanceToOrigin(origin.latitude(), origin.longitude(), pointLatitude, pointLongitude);  // measureDistance(PatdsBot0, PadtsBot1)
		points.push_back( Point( tempTag, pointLatitude, pointLongitude, distanceToOrigin.measure() ) );
		//distances.push_back(distance.measure());
	}
	fileHandler.close();
	sort(points.begin(), points.end());

	cout << "Data file: " << file  << endl;
	cout << "Nearest point data 	-> Tag: " << points[1].tag() << ", Latitude: " << points[1].latitude() << ", Longitude: "
		 << points[1].longitude()  << ", Distance to Origin: " << points[1].distanceToOrigin() << " km" << endl;
	cout << "Origin location data 	-> Tag: " << originTag << ", \tLatitude: " << origin.latitude() << ", Longitude: "
		 << origin.longitude() << endl;

	return 0;
}
