// Reproductor_Wav_VC12.cpp: define el punto de entrada de la aplicación de consola.
//

//#include "stdafx.h"

//#include "reproductor_WAV.h"
#include "soundhandler.h"
#include <iostream>
#include <string.h>

// GT_HelloWorldWin32.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

//#include <windows.h>
#include <stdlib.h>
#include <string.h>
//#include <tchar.h>

using namespace std;


int main(int argc, char* argv[])
{
	SoundStereo* stereo = nullptr;	// Stereo
    Sound* sound = nullptr;			// Mono
    
    //string location = "gtr.wav"; // Mono
    string location = "init.wav"; // stereo
    
    auto file = load_wavefile(location);

	//PlaySound( (LPCWSTR)"init.wav", NULL, SND_FILENAME | SND_ASYNC);
	//getchar();
    
    if (file != nullptr)
	{
        //file->display();
        
        sound = get_vectors(file);
        if (sound == nullptr)
		{
            cout<<"Sound:Error: Not format compatible found\n";
            return 1;
        }
        cout<<"Type found: "<<sound->Type()<<"\n";
        // Using the right object
        if (sound->Type() == "stereo")
		{
            stereo = static_cast<SoundStereo*>(sound);
            cout<<"okay \n";
            
			// IMPRIME TODOS LOS ELEMENTOS
			
			//stereo->reverse();
			
			//auto normalized = stereo->Signal();
            /*
			for ( auto &i : normalized[0] )
			{
                cout<<"item:"<<i<<"\n";
            }
			*/
            
        }
		
		file->MulSeno(1000);
		file->eco(0.2, 0.5);
		file->reverse();
		
		save_wavefile(file);
        
    }
	else
	{
        cout<<"Not memory assigned\n";
    }

    return 0;
}
