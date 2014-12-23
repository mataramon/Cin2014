/*================================================================
## Title:           C++ Code fo compare the distance between
##                  two points
## File:            Homework1_AntonioAltamirano.cpp
##================================================================
## Description:     Nearest point 
##================================================================
## Author:          Altamirano Cornejo Antonio Martin 
##==============================================================*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

class MyBot{
	private:
		string GotName;
	public:
		MyBot(string Name){
			getName(Name);
		}

		void getName(string InName){
			GotName = InName;
		}
		~MyBot(){}
		string showName(){
			return GotName;
		}
		void showError(string errName){
		cout << "-E-: " << errName << " : no such name in the list" <<endl;
		exit(1);
		}
};

class DataProcess{
	private:
		string NearestBot; // to store the closest bot name
		double Long;	   // stores the argument respective longitude
		double Lat;	   // stores the argument respective latitude
		double CLong;      // stores de current longitude
		double CLat;	   // stores the current latitude
		double Dist;       // stores the calculated distance
		double NLong;	   // Stores the nearest longitude
		double NLat;	   // stores the nearest latitude
	public:
		void ReferenceCapture( double x, double y ){
			CLat    = x;
			CLong   = y;
		}	
		//~DataProcess(){}      //destructor
		void ComputingDist(double ref_x, double ref_y){		
			Lat   = CLat-ref_x;
			Long  = CLong-ref_y;
			Dist  = pow(Lat,2) + pow(Long,2);
			Dist  = sqrt(Dist); 
		}

		void NearestData(string NName, double Nearlat, double Nearlong ){
			NLat       = Nearlat;
			NLong      = Nearlong;
			NearestBot = NName;
		}
		void ShowResults(){
			cout<<"-I-: Nearest point Bot is: " << NearestBot << " Lat = " << NLat << " Long = " << NLong << endl;
		}
		// DEBUGGING METHODS!!!!-----
		double ShowDist(){ //show the nearest distance
			return Dist;
		}			
		double ShowNearLong(){ //show the near bot longitude
			return NLong;
		}
		double ShowNearLat(){  //show the near bot latitude
			return NLat;
		}
		string ShowNearName(){ //show the near bot name
			return NearestBot;
		}
};
//-------------- MAIN FUNCTION -------------------//
int main(int argc,char *argv[]){
	string	Name;  //string name capture
	string  sLat;  //string latitude capture
	string  sLong; //string longitude capture
	double  dLong=0;
	double  dLat=0;
	double  LowerDistInit=0;
	bool   	BotFound_flag=false;
	bool 	comp=false;
	Name = "empty";
	if (argc == 1){  //if there is not an argument written by the user...
		cerr<<"-E-: You should provide a Bot name"<<endl;
		exit(1);
	}
	MyBot GetBot(argv[1]);
	cout.precision(10);
	//cout<<"-D-: bot name is: "<<GetBot.showName()<<endl;
	DataProcess GetCoords;
	// trying opening the file
	ifstream MyFile;               // object of the file to access
	MyFile.open("test_data.data"); // opening the file
	// Check if the file exist
	if (MyFile.fail()){
		cerr << "-E-: not an existing file\n"; // no such file error
		exit(1);	
	}
	cout << "-I-: Searching...." << endl;
	//while ( !MyFile.eof() ){ //while is not the end of the file..
	while (MyFile.peek() != EOF){	
		getline(MyFile, Name, ','); //read the line until find a comma	

		getline(MyFile, sLat, ',');
		dLat= stod(sLat.c_str());

		getline(MyFile, sLong, '\n');
		dLong= stod(sLong.c_str());
          	if ( (Name  == GetBot.showName()) && (BotFound_flag == false)){
			cout << "-I-: Provided point Bot  : "<<Name<<" " << "Lat = " << dLat << " Long = " << dLong << endl;
			GetCoords.ReferenceCapture(dLat, dLong);
			BotFound_flag=true;
			break;
 		} else {
			//do nothing
		}
	}
	if (BotFound_flag == false){
		cout << "-E-: The bot provided does not exist" << endl;
		exit(1);
	}
	MyFile.clear();
        MyFile.seekg(0, ios::beg);
	cout << "-I-: Comparing...." << endl;
	while (MyFile.peek() != EOF){	
		getline(MyFile, Name, ','); //read the line until find a comma	

		getline(MyFile, sLat, ',');
		dLat= stod(sLat.c_str());

		getline(MyFile, sLong, '\n');
		dLong= stod(sLong.c_str());
		if (Name == GetBot.showName()){
			//ignores it
		} else {
			if(comp==false){
				GetCoords.ComputingDist(dLat, dLong);
				LowerDistInit=GetCoords.ShowDist();
				GetCoords.NearestData( Name, dLat, dLong );
				// uncomment below to see debugging info
				//cout<<GetCoords.ShowDist()<<endl;
				//GetCoords.ShowResults();
				comp=true;
			} else {
				GetCoords.ComputingDist(dLat, dLong);
				if( LowerDistInit > GetCoords.ShowDist() ){
					LowerDistInit=GetCoords.ShowDist();
					GetCoords.NearestData( Name, dLat, dLong );
					// uncomment below to see debugging info
					//cout<<GetCoords.ShowDist()<<endl;
					//GetCoords.ShowResults();
				} else {
					// do nothing
				}
			}
		}
	}
	MyFile.close();
	GetCoords.ShowResults();
	return 0;
}
