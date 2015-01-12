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
        cout<<"Type found: "<<sound->Type()<<"\n";
        // Using the right object
        if (sound->Type() == "stereo"){
            stereo = static_cast<SoundStereo*>(sound);
            cout<<"okay \n";
            auto normalized = stereo->Signal();
            
       /*     for (auto &i: normalized[0]){
                cout<<"item:"<<i<<"\n";
            }*/
            
        }
        
    }else{
        cout<<"Not memory assigned\n";
    }
  //  auto dato = char2int(file->Id,4);
   // printf("%02x ", dato);
    //cout << dato;
	Eco(file);
    save_wavefile(file);
    return 0;
}
