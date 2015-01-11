#include <iostream>
#include <string>

using namespace std;

/* Definition simple class */
class Item {
	private:
		string type;

	public:
	    Item();
	   ~Item();
	    Item(string name);
		virtual void hello();
};

/* Implementation */

Item::Item() : Item("None") {}
Item::~Item(){}

Item::Item(string name) {
	this->type = name;
}

void Item::hello(){
	cout << "Hello from type " << type << "\n";
}

void myFuntion(){
	cout << "Hello from my function\n";
}

extern "C" {
	void myFoo(){
		cout << "This is a classic c function\n";
	}
}

int main(int argc, char* argv[])
{
	auto a = Item();
	auto b = Item("Number");

	a.hello();
	b.hello();

	return 0;
}

