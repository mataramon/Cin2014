//
//  soundhandler.cpp
//  Sound
//
//  Created by Angel Jovany Figueroa Ypiña on 12/30/14.
//  Copyright (c) 2014 Angel Jovany Figueroa Ypiña. All rights reserved.
//

#include "soundhandler.h"
//
Sound::Sound(){}

Sound::~Sound(){}

WavFile::WavFile(){}

WavFile::~WavFile(){}


WavFile* load_wavefile(string location) {
    WavFile *neue = nullptr;
    streampos size = 0;
    ifstream wavefile (location, ios::in | ios::binary | ios::ate);
    
    if (wavefile.is_open()){
        size = wavefile.tellg();
        wavefile.seekg(0, ios::beg);
        char *items = new char[size];


        // starting the data structure
        if (size < 4) {
            cout<<"Error: File two small cannot get the header\n";
            return neue;
        }
        wavefile.read(items, size);
        for (int i=0;i<4;i++){
            cout<<"->"<<*(items+i)<<"\n";
        }


        wavefile.close();
        
    }
    else{
        cout<<"Error: Cannot open the wavefile "<<location<<"\n";
    }
    
    return neue;
}

void save_wavefile(WavFile* wavfile) {
    
    
    
}