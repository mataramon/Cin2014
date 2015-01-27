#pragma once
#include "Riffile.h"
#include "wave.h"
#include <string>


using namespace std;
class CWorkspace
{

	
public:
	CWorkspace(void);
	~CWorkspace(void);
public:
	
	WaveFile* pWave; 
	char * filename;
	void LoadSLOW(const char* FileName);
	void LoadECO(const char* FileName);
	void LoadTREMOLO(const char* FileName);
	
	
};

