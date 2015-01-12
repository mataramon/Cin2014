#include "sort.h"

Sort::Sort() {}  // Constructor
Sort::~Sort() {} // Destructor

string Sort::Sorting (string WordIn){
	std::string SortedWord = WordIn;
	std::sort(SortedWord.begin(), SortedWord.end());
	SortedWord.erase(unique(SortedWord.begin(), SortedWord.end()),SortedWord.end());
	return SortedWord;
}

int main() {
	
	bool Found = false;	
	string Word_1, Word_2,Word_3;
	string myArray[11];
	cout << "Enter a name of a animal: " << endl;
	cin >> Word_1;	

	// Creating Objects
	Sort FirstWord = Sort();
	Sort SecondWord = Sort();

	ifstream file("animals.txt");
    if(file.is_open())
    {	
      for(int i = 0; i < 11; ++i) 
		{ 
		
			file >> myArray[i]; 
			if ((strcmp((FirstWord.Sorting(Word_1)).c_str(), (SecondWord.Sorting(myArray[i])).c_str()) == 0 ))
			{
				Word_2 = myArray[i];
				Found = true;
			}
		
			else 
			{
				std::string Recorted = (FirstWord.Sorting(Word_1)).substr (0,2);
				std::string Recorted_0 = (SecondWord.Sorting(myArray[i])).substr (0,2);
				if ((strcmp(Recorted.c_str(), Recorted_0.c_str()) == 0 ))
				{
					Word_2 = myArray[i];
					Found = true;
				}
			}
		}
    }
	if ( Found == true )
		cout << "Searching...\nPerhaps you mean: " << Word_2 << endl;
	else
      cout <<"Searching...\nNot animals named like that found" << endl;

    return 0;
}
