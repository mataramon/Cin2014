#include <iostream> // Input/Output streams
#include <fstream> // Files stream
#include <math.h> // Math
#include <vector> // Vector
#include <algorithm> // Sort Algorithm

using namespace std;

class Pair
{

	public:
	double x, y;
	
	Pair()
	{	x = 0; y = 0; } // Constructor
	Pair(double x, double y)
	{	this->x = x; this->y = y; 
		//Name = new char()
	} // Inicializa datos
	~Pair() {} // Destructor
	double X() const 
	{	return x;} // Accesa dato X
	void X(double x)
	{	this->x = x; } // Asigna solo X
	double Y() const
	{	return y;} // Accesa dato Y
	void Y(double y)
	{	this->y = y; } // Asigna dato Y
	static bool sortBy_X(const Pair &pair1, const Pair &pair2)
	{ 	return pair1.x 	< pair2.x; } // Ordena para X
	static bool sortBy_Y(const Pair &pair1, const Pair &pair2)
	{ 	return pair1.y < pair2.y; } // Ordena para Y
};

// Calcular distancia eucludiana entre puntos
double distanceCalc(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2;
	double y = y1 - y2;
	double dist;
	dist = pow(x,2)+pow(y,2);
	dist = sqrt(dist);
	return dist;
}

int main(int argc, char* argv[])
{
	//************** Initialization
	string Name, Target;
	double lat, lon, dist;
	vector<Pair> dlist;
	char *File = {"test_data.data"};
	//Default Values initialization
	double latIN = 0;
	double lonIN = 0;
	double minDist = 10000000000000;	// Da distancia minima inicial muy grande
	int i_found = 0;	// indice del elemento mas cercano
	Target = "none";
	//Counters & Flags
	bool found = false, ok_name = false;

	//*************** Checking Arguments
	if (argc >= 2)
	{
		Target = argv[1];
		cout<<"\nFile: " << File << "\n\nSearching for the closest point to: \n" << Target;
	}
	else
		cout<<"\nError Missing Target point. \n\t-Please provide argument \"PadtsBot[0-999999]\""<<endl;
	
	cout.precision(10);
	//********** Opening File
	ifstream myReadFile;
	myReadFile.open(File);
	if (!myReadFile.is_open())
	{
		cerr<<"\nError in File: "<<File<<" \n\t-Please enter a valid file."<<endl;
		return 1;
	}
	
	//*********** Extracting coordenates from Target
	while ( myReadFile.peek() != EOF )
	{ 	// If EOF flagbit is set during the call, the function returns (EOF)	value.
		getline(myReadFile,Name,',');
		myReadFile>>latIN;
		myReadFile.ignore();
		myReadFile>>lonIN;
		myReadFile.ignore();
		if ( Name == Target )
		{
			ok_name = true;
			break;
		}	
	}
		
	if( ok_name == true )
		cout << " ( Lat = " << latIN << ", Lon = " << lonIN << " )" << endl;
	else
	{
		cerr << "\nError: " << Target << " was not found. \n-Please enter a valid name. " <<endl;
		myReadFile.close();
		return 1;
	}

	//*************** Restart File stream pointer
	myReadFile.clear();
	myReadFile.seekg(0, ios::beg);

	//***************** LEE DATOS lat & lon DEL ARCHIVO Y LOS AÑADE AL VECTOR = (INDEX,DISTANCIA)
	int index = 0;
	while ( myReadFile.peek() != EOF )
	{ // If EOF flagbit is set during the call, the function returns (EOF) value.
		getline(myReadFile,Name,',');
		myReadFile>>lat;
		myReadFile.ignore();
		myReadFile>>lon;
		myReadFile.ignore();
		if( Name != Target )
		{	
			dist = (latIN-lat)*(latIN-lat) + (lonIN-lon)*(lonIN-lon);
			if(minDist > dist)
			{
				i_found = index;
				minDist = dist;
			}
			dlist.push_back( Pair(lat, lon) );
			index++;
		}

		//cout<<Name<<":"<<dist<<endl;
	}

	if( minDist != 10000000000000 )
	{
		cout << "\nClosest coordinate found is: \n";// << dlist[i_found].Name;
		cout << " ( Lat = " << dlist[i_found].x << ", Lon = " << dlist[i_found].y << " )" << endl;
	}
	else
		cerr << "\nError: " << Target << " not found. Try Again" <<endl;
	//*************** Close file
	myReadFile.close();
	return 0;
}
