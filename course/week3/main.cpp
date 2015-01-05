//  main.cpp
//  Sound
//
//  Created by Angel Jovany Figueroa Ypiña on 12/30/14.
//  Copyright (c) 2014 Angel Jovany Figueroa Ypiña. All rights reserved.
//

#include <iostream>
#include "soundhandler.h"
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    SoundStereo* stereo = nullptr;
    Sound* sound = nullptr;
    
    //string location = "gtr.wav"; // Mono
    string location = "init.wav"; // stereo
    
    auto file = load_wavefile(location);
    
    if (file != nullptr){
        file->display();
        
        sound = get_vectors(file);
        if (sound == nullptr){
            cout<<"Sound:Error: Not format compatible found\n";
            return 1;
        }
        // Using the right object
        if (sound->Type() == "Stereo"){
            stereo = static_cast<SoundStereo*>(sound);
        }
        
    }else{
        cout<<"Not memory assigned\n";
    }


    return 0;
}
