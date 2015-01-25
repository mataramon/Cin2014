//Sánchez Israel, Raúl Calzada.
//localización general de archivos en el mismo directorio.

#include <iostream>
#include <string>
#include <dirent.h>
using namespace std;


   int main(int argc, char**argv)
   {
 
    struct dirent *punto;  
    DIR *lugar = opendir(".");
 
    if (lugar == NULL)  
    {
        printf("no se pudo abrir el directorio actual" );
        return 0;
    }
    if (argc < 2)
	{
	cout << "indica una opcion de busqueda " << endl;
        return 1;     
        }
    
    while ((punto = readdir(lugar)) != NULL)
	{

            printf("%s\n", punto->d_name);

        }
        closedir(lugar);    
        return 0;
         }

