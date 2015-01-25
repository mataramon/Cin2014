#ifndef GPS_stuff_h
#define GPS_stuff_h

#include "Arduino.h"

class GPS_stuff{
private:
	int _rxPin;
	int _txPin;
	int commaCount = 0;
	int byteCount=0;
	char beaconGPS[6]={'$GPRMC'};
public:
	bool data_Available=0;
	//variables de informacion
	char dataBeacon[6];
	char dataTimeStamp[6];
	char dataValidity;
	char dataCurrentLatitude[8];
	char dataNS;
	char dataCurrentLongitude[8];
	char dataEW;
	char dataSpeedknots[6];
	char dataTrueCurse[6];
	char dataDateStamp[6];
	char dataVariation[6];
	char dataVariationEW;

	GPS_stuff();
	~GPS_stuff();
	void receive(char byteGPS);
};

void GPS_stuff::receive(char byteGPS){
		byteCount++;
		if(byteGPS == ','){
			byteCount=0;
			if(data_Available) commaCount++;
		}
		switch (commaCount) {
		    case 0: dataBeacon[byteCount-1]=byteGPS; break;
		    case 1: dataTimeStamp[byteCount-1]=byteGPS; break;
		    case 2: dataValidity=byteGPS; break;
		    case 3: dataCurrentLatitude[byteCount-1]=byteGPS; break;
		    case 4: dataNS=byteGPS; break;
		    case 5: dataCurrentLongitude[byteCount-1]=byteGPS; break;
		    case 6: dataEW=byteGPS; break;
		    case 7: dataSpeedknots[byteCount-1]=byteGPS; break;
		    case 8: dataTrueCurse[byteCount-1]=byteGPS; break;
		    case 9: dataDateStamp[byteCount-1]=byteGPS; break;
		    case 10: dataVariation[byteCount-1]=byteGPS; break;
		    case 11: dataVariationEW=byteGPS; break;
		    case 12: dataBeacon[5]=' ';
                     dataValidity=' ';
					 commaCount=0;
                     break;
		}
		if(dataBeacon==beaconGPS) data_Available=1;
}

GPS_stuff::GPS_stuff(){

}

GPS_stuff::~GPS_stuff(){
	
}

#endif
