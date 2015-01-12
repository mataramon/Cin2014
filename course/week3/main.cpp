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
    string location = "init6.wav"; // stereo
    
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

        int cont = 0;
        if (sound->Type() == "mono"){
            //stereo = static_cast<SoundStereo*>(sound);
            cout<<"okay \n";
            auto normalized = sound->Signal();
            
<<<<<<< HEAD
       /*     for (auto &i: normalized[0]){
                cout<<"item:"<<i<<"\n";
            }*/
=======
            for (auto &i: normalized[0]){
                cout<<cont<<"\t"<<i<<"\n";

                cont++;
            }
>>>>>>> f65e8f3ec2c19f42a2e21001e10cceb507cdc09e
            
        }
        
    }else{
        cout<<"Not memory assigned\n";
    }


    return 0;
}
