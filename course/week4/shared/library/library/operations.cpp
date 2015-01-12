#include "stdafx.h"
#include "operations.h"
#define EOF (-1)


#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

namespace OurFoo{
	// Implementation
	Human::Human(){
		this->name = "None";
	}

	Human::Human(string name){
		this->name = name;
	}

	Human::~Human(){
	
	}

	Mexican::Mexican() : Human("Jose") {
		this->nation = "Mexico";
	}

	Mexican::~Mexican(){
	}

}

   // __declspec(dllexport)    

  __declspec(dllexport) int __cdecl get_item(void){
	  auto value = OurFoo::Human("jolines");
	return 10;
 }

 
#ifdef __cplusplus
}
#endif
