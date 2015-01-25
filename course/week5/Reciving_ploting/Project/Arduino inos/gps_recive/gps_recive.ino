#include <SoftwareSerial.h>
#include "driver.h"

#define rxPin 8
#define txPin 7
int k = 0;
int i = 0;
int j = 0;
int NMEA;
unsigned char bandera_datos = 0;
unsigned char bandera_current = 0;
unsigned char bandera_comas = 0;
char byteGPS;
char beaconGPS[]={"$GPRMC"};
//variables de informacion
char dataTimeStamp[10];
char dataValidity;
char dataCurrentLatitude[20];
char dataNS;
char dataCurrentLongitude[20];
char dataEW;
char dataSpeedknots[20];
char dataTrueCurse[10];
char dataDateStamp[10];
char dataVariation[10];
char dataVariationEW;

// configura un nuevo puerto serie
SoftwareSerial gps =  SoftwareSerial(rxPin, txPin);

void setup()  {
  // configura el modo de los pines para tx, rx:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  // configura el ratio de datos para el puerto SoftwareSerial
  gps.begin(9600);
  Serial.begin(9600);
}
void loop()
{
   if (gps.available()>0)
   {
     byteGPS = gps.read(); //lee el primer byte de informacion
   //Serial.print(byteGPS);
   
   //Parte del debugueo para aislar un renglon de informacion
   if(beaconGPS[i]==byteGPS)
   {
    i++;
   }  
   j++;
   
   if(i != j)
   {i=0;
   j=0;}
   
   if(bandera_datos > 0)
   {comas();}
   
   switch (bandera_datos)
   {
   case 1: Time_Stamp();break;
   case 2: Validity();break;
   case 3: Current_Latitude();break;
   case 4: North_South();break;
   case 5: Current_Longitude();break;
   case 6: East_West();break;
   case 7: Speed_In_Knots();break;
   case 8: True_Course();break;
   case 9: Date_Stamp();break;
   case 10: Variation();break;
   case 11: East_West_variation();break;
   case 12: Show();
   }
   
   //Serial.print(byteGPS);
   
   if(i==j && i==6)
   {
     Serial.print("\nCadena GPRMC encontrada \a");
     bandera_datos=1;
     //Serial.print(" Comas encontradas: ");
     //Serial.print(bandera_comas);
     //Serial.print('\n');
     bandera_comas=0;
   }
   
 }
}



