#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>

using namespace std;

class Sort {
	private:
		string Word;
		string SortedWord;
	public:
		Sort(); // Constructor
	  ~Sort(); // Destructor
		string Sorting (string WordIn);
};
