void Time_Stamp(void)
{
  if (byteGPS != ',')
  {
    dataTimeStamp[k]=byteGPS;
    k++;
  }
  
}

void Validity(void)
{
   if (byteGPS != ',')
  {
    dataValidity=byteGPS;
    k++;
  }
}  
   
void Current_Latitude(void)
{
  if (byteGPS != ',')
  {
    dataCurrentLatitude[k]=byteGPS;
    k++;
  }
}
void North_South(void)
{
  if (byteGPS != ',')
  {
    dataNS=byteGPS;
    k++;
  }
}
void Current_Longitude(void )
{
  if (byteGPS != ',')
  {
    dataCurrentLongitude[k]=byteGPS;
    k++;
  }
}
void East_West(void)
{
  if (byteGPS != ',')
  {
    dataEW=byteGPS;
    k++;
  }
}
void Speed_In_Knots(void)
{
  if (byteGPS != ',')
  {
    dataSpeedknots[k]=byteGPS;
    k++;
  }
}
void True_Course(void)
{
  if (byteGPS != ',')
  {
    dataTrueCurse[k]=byteGPS;
    k++;
  }
}
void Date_Stamp(void)
{
  if (byteGPS != ',')
  {
    dataDateStamp[k]=byteGPS;
    k++;
  }
}
void Variation(void)
{
  if (byteGPS != ',')
  {
    dataVariation[k]=byteGPS;
    k++;
  }
}
void East_West_variation(void)
{
    if (byteGPS != ',')
  {
    dataVariationEW=byteGPS;
    k++;
  }
}
void comas (void)
{
  //Serial.print(bandera_comas);

  if(byteGPS ==',')
  {
    bandera_comas++;
    k=0;
    if (bandera_comas==13)
    {bandera_datos=0;}
  }
 
 switch(bandera_comas)
  {
    case 1: bandera_datos = 1;break;
    case 2: bandera_datos = 2;break;
    case 3: bandera_datos = 3;break;
    case 4: bandera_datos = 4;break;
    case 5: bandera_datos = 5;break;
    case 6: bandera_datos = 6;break;
    case 7: bandera_datos = 7;break;
    case 8: bandera_datos = 8;break;
    case 9: bandera_datos = 9;break;
    case 10: bandera_datos = 10;break;
    case 11: bandera_datos = 11;break;
    case 12: bandera_datos = 12;break;
    default: break;
  } 
}

void Show (void)
{
  if(dataValidity =='V')
  {
    Serial.print("Posicion aun no localizada");
  }
  
  unsigned char p=0;
  //Hora GTM -0 
  Serial.print("\nHora GTM-0 : "); 
  Serial.print(dataTimeStamp[0]);
  Serial.print(dataTimeStamp[1]);
  Serial.print(":");
  Serial.print(dataTimeStamp[2]);
  Serial.print(dataTimeStamp[3]);
  Serial.print(":");
  Serial.print(dataTimeStamp[4]);
  Serial.print(dataTimeStamp[5]);
  Serial.print('\n');
  //Latitud actual
  Serial.print("Latitud: ");
  Serial.print(dataCurrentLatitude[0]);
  Serial.print(dataCurrentLatitude[1]);
  Serial.print("deg. ");
  Serial.print(dataCurrentLatitude[2]);
  Serial.print(dataCurrentLatitude[3]);
  Serial.print(dataCurrentLatitude[4]);
  Serial.print(dataCurrentLatitude[5]);
  Serial.print(dataCurrentLatitude[6]);
  Serial.print(dataCurrentLatitude[7]);
  Serial.print(dataCurrentLatitude[8]);
  Serial.print(dataCurrentLatitude[9]);
  Serial.print(" min ");
  
  Serial.print(dataNS);
   Serial.print('\n');
  //Longitud actual
  Serial.print("Longitud: ");
  Serial.print(dataCurrentLongitude[0]);
  Serial.print(dataCurrentLongitude[1]);
  Serial.print(dataCurrentLongitude[2]);
  Serial.print("deg. ");
  Serial.print(dataCurrentLongitude[3]);
  Serial.print(dataCurrentLongitude[4]);
  Serial.print(dataCurrentLongitude[5]);
  Serial.print(dataCurrentLongitude[6]);
  Serial.print(dataCurrentLongitude[7]);
  Serial.print(dataCurrentLongitude[8]);
  Serial.print(dataCurrentLongitude[9]);
  Serial.print(dataCurrentLongitude[10]);
  Serial.print(" min ");
  
  Serial.print(dataEW);
  Serial.print('\n');
  //Velocidad en nudos
  Serial.print("Velocidad en nudos: ");
  p=0;
   while(dataSpeedknots[p] != '\0')
  {
    Serial.print(dataSpeedknots[p]);
    p++;
  }
  Serial.print('\n');
  //Fecha
  Serial.print("Fecha: ");
  Serial.print(dataDateStamp[0]);
  Serial.print(dataDateStamp[1]);
  Serial.print("/");
  Serial.print(dataDateStamp[2]);
  Serial.print(dataDateStamp[3]);
  Serial.print("/");
  Serial.print(dataDateStamp[4]);
  Serial.print(dataDateStamp[5]);
  Serial.print('\n');
  //Variacion magnetica Polo norte y magnetico
  bandera_datos = 0;
}

