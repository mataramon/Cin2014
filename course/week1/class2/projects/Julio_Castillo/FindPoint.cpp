/* FindOrigin.cpp */
// =================================================================================================
// Author: 	 Julio Castillo
// File: 	 FindOrigin.cpp
// Date:	 December 15th 2014
// =================================================================================================

#include <fstream>
#include <string>

#include "FindPoint.h"

using std::string;
using std::ifstream;


FindPoint::FindPoint(std::string tag, std::string file): tag_(tag), file_(file), latitude_(0), longitude_(0) {
}

void FindPoint::findCoordinates() {
	double tempLatitude = 0;
	double tempLongitude = 0;
	string tempTag;
	ifstream fileHandler (file_.c_str());
		while ( fileHandler.peek() != EOF ) {
			getline( fileHandler, tempTag, ',' );
			fileHandler >> tempLatitude;
			fileHandler.ignore();
			fileHandler >> tempLongitude;
			fileHandler.ignore();
			if ( tag_ == tempTag  ) {
				latitude_ = tempLatitude;
				longitude_ = tempLongitude;
				break;
			}
		}
		fileHandler.close();
}


