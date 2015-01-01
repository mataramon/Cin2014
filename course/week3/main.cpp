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
    string location = "/Users/leofigy/Desktop/myaudio.wav";
    auto file = load_wavefile(location);
    //cout<<"it is empty :("<<file->Id<<"\n";


    return 0;
}
