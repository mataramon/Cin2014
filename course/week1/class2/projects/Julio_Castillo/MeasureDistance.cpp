/* MeasureDistance.cpp */
// =================================================================================================
// Author:   Julio Castillo
// File: 	 MeasureDistance.cpp
// Date:	 December 15, 2014
// =================================================================================================

#include "MeasureDistance.h"

MeasureDistance::MeasureDistance(double originLatitude,  double originLongitude, double pointLatitude, double pointLongitude):
								originLatitude_(originLatitude), originLongitude_(originLongitude), pointLatitude_(pointLatitude),
								pointLongitude_(pointLongitude), distanceDifference_(0) {
}

double MeasureDistance::measure() {  // generally used geo measurement function
	double earthRadius = 6378.137; 																    // Radius of earth in KM
	double latitudeDifference =   this->degreesToRadians(pointLatitude_ - originLatitude_);
	double longitudeDifference =  this->degreesToRadians(pointLongitude_ - originLongitude_);
	double a = sin(latitudeDifference/2) * sin(latitudeDifference/2) + 						\
	   		   cos( this->degreesToRadians(originLatitude_) ) * cos( this->degreesToRadians(pointLatitude_) ) * 		\
	   		   sin(longitudeDifference/2) * sin(longitudeDifference/2) ;
	double c = 2 * atan2(sqrt(a), sqrt(1-a));
	double distanceDifference_ = earthRadius * c;
	return distanceDifference_;
}

double MeasureDistance::degreesToRadians(double degree) {
	double PI = 3.141592;
	return degree * (PI/180);
}




