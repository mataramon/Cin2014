//  main.cpp
//  Sound
//
//  Created by Angel Jovany Figueroa Ypiña on 12/30/14.
//  Copyright (c) 2014 Angel Jovany Figueroa Ypiña. All rights reserved.
//

#include <iostream>
#include "../include/soundhandler.h"
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    SoundStereo* stereo = nullptr;                      // Puntero a structura SoundStereo
    Sound* sound = nullptr;                             // Puntero a Structura Sound
    
    string location1 = "../examples/Dinero.wav"; 
    string location2 = "../examples/Censura.wav";                      // Stereo WAV;

    auto file1 = load_wavefile(location1);               // Apuntador a objeto WaveFile
    auto file2 = load_wavefile(location2);
    
    if ( file1 != nullptr && file2 != nullptr ){
      process(location1, location2); 
    }else{
        cout<<"Not memory assigned\n";
    }
    return 0;
}
