/* MeasureDistance.h */
// =================================================================================================
// Author:   Julio Castillo
// File: 	 MeasureDistance.cpp
// Date:	 December 15, 2014
// =================================================================================================

#include <iostream>
#include <math.h>

#ifndef MEASUREDISTANCE_H_
#define MEASUREDISTANCE_H_

class MeasureDistance {
private:
	double originLatitude_;
	double originLongitude_;
	double pointLatitude_;
	double pointLongitude_;
	double distanceDifference_;
	double degreesToRadians(double degree);
public:
	MeasureDistance(double originLatitude,  double originLongitude, double pointLatitude, double pointLongitude);
	double measure();
};

#endif /* MEASUREDISTANCE_H_ */
