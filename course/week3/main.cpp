//
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
    // insert code here...
    string location = "clap.wav";
    auto file = load_wavefile(location);
    
    if (file != nullptr){
        file->display();
        
        // Dummy example
        Sound *sound = nullptr;
        sound = new Sound(file);
        cout<<sound->Type()<<"\n";
        delete sound;
        sound = new SoundStereo(file);
        cout<<sound->Type()<<"\n";
        delete sound;
        
    }else{
        cout<<"Not memory assigned\n";
    }


    return 0;
}
