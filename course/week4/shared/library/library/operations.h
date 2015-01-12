#ifdef OPERATIONS_EXPORTS
#define OPERATIONS_API __declspec(dllexport)
#else
#define OPERATIONS_API __declspec(dllexport)
#endif

#include "stdafx.h"

using namespace std;

namespace OurFoo{

	class Human{
		private:
			string name;
		public:
			Human();
			Human(string);
		   ~Human();

			string Name(void)const{ return this->name;}
			virtual void hello(void){ cout<<"Hello I'm a human\n";}
	};

	class Mexican : public Human{
		private:
			string nation;
		public:
			 Mexican();
		    ~Mexican();
			string Nation(void) const {return this->nation;}
			void hello(void){ cout<<"Hello I'm a mexican\n";}
	};

	// A regular function
	
}

// to avoid c++ linkage
