#include <SoftwareSerial.h>
#include "GPS_stuff.h"

#define rxPin 9
#define txPin 8

char serialByte;
char byteGPS;

SoftwareSerial gps =  SoftwareSerial(rxPin, txPin);
GPS_stuff SuperGPS;

void setup()  {
  //GPS configuration
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  gps.begin(9600);
  //Serial config
  Serial.begin(9600);
}
void loop(){
	if(gps.available()){
		byteGPS=gps.read();
    	//Serial.print(byteGPS);
    	SuperGPS.receive(byteGPS);
    }
    if(Serial.available()>0){
		serialByte=Serial.read();
		if(serialByte=='D'){
        	Serial.print(SuperGPS.dataTimeStamp);
	        Serial.print(",");
	        Serial.print(SuperGPS.dataCurrentLatitude);
	        Serial.print(",");
	        Serial.print(SuperGPS.dataNS);
	        Serial.print(",");
	        Serial.print(SuperGPS.dataCurrentLongitude);
	        Serial.print(",");
	        Serial.print(SuperGPS.dataEW);
	        Serial.print(",");
	        Serial.print(SuperGPS.dataDateStamp);
	        Serial.print("\n");
	    }
	}
}
