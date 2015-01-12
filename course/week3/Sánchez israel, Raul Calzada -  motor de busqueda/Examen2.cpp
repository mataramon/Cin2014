//Sánchez Israel y Raul Calzada
//localización general de archivos en el mismo directorio.



#include <iostream>
#include <string>
#include <dirent.h>
using namespace std;


int main(void)
{
    struct dirent *de;  
    DIR *dr = opendir(".");
 
    if (dr == NULL)  
    {
        printf("Could not open current directory" );
        return 0;
    }
 
    
    while ((de = readdir(dr)) != NULL)
            printf("%s\n", de->d_name);
 
    closedir(dr);    
    return 0;
}
