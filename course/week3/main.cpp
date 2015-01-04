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
    string location = "pacman_x.wav";
    auto file = load_wavefile(location);
    
    if (file != nullptr){
        file->display();
        
    }else{
        cout<<"Not memory assigned\n";
    }

    // memory
    cout<<sizeof(char)<<"\n";
    cout<<sizeof(int)<<"\n";
    cout<<sizeof(string)<<"\n";
    
    // Dummy example
    Sound *sound = nullptr;
    sound = new Sound(file);
    cout<<sound->Type()<<"\n";
    delete sound;
    sound = new SoundStereo(file);
    cout<<sound->Type()<<"\n";
    delete sound;
    
    return 0;
}
