/* Point.h */
#include <string>

#ifndef POINT_H_
#define POINT_H_

class Point {
private:
	std::string tag_;
	double latitude_;
	double longitude_;
	double distanceToOrigin_;
public:
	Point(std::string tag, double latitude, double longitude, double distanceToOrigin): tag_(tag), latitude_(latitude), longitude_(longitude),
																	  distanceToOrigin_(distanceToOrigin) {
	}
	std::string tag() { return tag_; }
	double latitude() { return latitude_; }
	double longitude() { return longitude_; }
	double distanceToOrigin() { return distanceToOrigin_; }
	bool operator<(const Point& point) const { return distanceToOrigin_ < point.distanceToOrigin_; }
};

#endif /* POINT_H_ */
