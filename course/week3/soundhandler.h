//
//  soundhandler.h
//  Sound
//
//  Created by Angel Jovany Figueroa Ypiña on 12/30/14.
//  Copyright (c) 2014 Angel Jovany Figueroa Ypiña. All rights reserved.
//

#ifndef Sound_soundhandler_h
#define Sound_soundhandler_h

#include <string>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;


/* We use this in order to allocate the datatypes */
union IntType{
    int a:16;  // only uses 16 bits
    int b:32;  // only uses 32 bits
};


// Applies a transformation to an audio file

class Sound {
    
    public:
         Sound();
        ~Sound();


};

// Loading an encoding file
class WavFile {
    // structure to represent the wavefile
    public:
        // Header                   BYTES
        char Id[4];      // 4  - RIFF
        IntType ChuckSize;        // 4
        char Format[4];  // 4  - WAVE
        // FMT
        char FmtID[4];   // 4  - fmt
        IntType FmtSize;          // 4
        IntType FmtAudioFormat;   // 2
        IntType FmtChannels;      // 2
        IntType FmtSampleRate;    // 4
        IntType FmtByteRate;      // 4
        IntType FmtBlockAlign;    // 2
        IntType FmtBitsPerSample; // 2
        // Data
        char DataID[4];   // 4 - data
        IntType DataSize;
        char*   data;
        WavFile();
       ~WavFile();
        void display(void);
    
};

// Functions to save the wave file
void save_wavefile(WavFile*);
WavFile* load_wavefile(string);
IntType char2int(char* , unsigned int);

#endif
