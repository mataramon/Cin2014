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
#include <vector>
#include <algorithm>
#include <cmath>
#include <ios>
#include <iomanip>


using namespace std;


/* We use this in order to allocate the datatypes */
union IntType{
    int a:16;  // only uses 16 bits
    int b:32;  // only uses 32 bits
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

// Applies a transformation to an audio file
/*------------- MONO CLASS -----------*/
class Sound {
    protected: // Protected items will be privete in the derivate class
        vector<IntType> mono;
        string type;
    public:
         Sound(WavFile*);
        ~Sound();
        // accessors
        string Type(void) const  {return type;      }
        void   Type(string type) {this->type = type;}
        vector<float> Signal(); 
        
        
};
/*---------- END MONO CLASS -------------*/

/*---------- START STEREO CLASS ---------*/
class SoundStereo  : public Sound{
    private:
        vector<IntType> left;
        vector<IntType> right;
        
    public:
        SoundStereo(WavFile*);
       ~SoundStereo();
       // Accessors
       vector<vector<float>> Signal();
       
};

/*---------- END STEREO CLASS   ----------*/

/* GENERIC PROTOTYPES FOR MISC FUNCTIONS*/
void save_wavefile(WavFile*);
WavFile* load_wavefile(string);
IntType char2int(char* , unsigned int);
//char* int2char (IntType , unsigned int);
void int2char (IntType , unsigned int, char*);
static bool abs_val(IntType, IntType);
Sound* get_vectors(WavFile*);
void process(string, string);
unsigned char readByte(char*);
#endif
