/* FindOrigin.h */
// =================================================================================================
// Author: 	 Julio Castillo
// File: 	 FindOrigin.h
// Date:	 December 15th 2014
// =================================================================================================
#include <string>

#ifndef FINDPOINT_H_
#define FINDPOINT_H_

class FindPoint {
private:
	std::string tag_;
	std::string file_;
	double latitude_;
	double longitude_;

public:
	FindPoint(std::string tag, std::string file);
	void findCoordinates();
	double latitude() { return latitude_; }
	double longitude() {return longitude_; }
	std::string tag() { return tag_; }

};


#endif /* FINDPOINT_H_ */
