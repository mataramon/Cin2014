//
//  soundhandler.cpp
//  Sound
//
//  Created by Angel Jovany Figueroa Ypiña on 12/30/14.
//  Copyright (c) 2014 Angel Jovany Figueroa Ypiña. All rights reserved.
//

// C headers 
#include <stdio.h>   
#include <string.h>

#include "soundhandler.h"


//
Sound::Sound(){}

Sound::~Sound(){}

WavFile::WavFile(){
    
    for (int i= 0;i<4;i++){
        Id[i]     = 'A';
        Format[i] = 'B';
        FmtID[i]  = 'C';
        DataID[i] = 'D';
    }
    
    ChuckSize.b = 0;        // 4
    // FMT
    FmtSize.b = 0;          // 4
    FmtAudioFormat.b = 0;   // 2
    FmtChannels.b = 0;      // 2
    FmtSampleRate.b = 0;    // 4
    FmtByteRate.b = 0;      // 4
    FmtBlockAlign.b = 0;    // 2
    FmtBitsPerSample.b = 0; // 2
    // Data
    DataSize.b = 0;
    data = nullptr;
    
}

void WavFile::display(void){
    cout<<sizeof(Id)<<" bytes :"<<Id<<"\n";
    cout<<ChuckSize.b<<"\n";
    cout<<sizeof(Format)<<" bytes :"<<Format<<"\n";
    cout<<sizeof(FmtID) <<" bytes :"<<FmtID<<"\n";
    cout<<FmtSize.b<<"\n";
    cout<<FmtAudioFormat.a<<"\n";
    cout<<FmtChannels.a<<"\n";      // 2
    cout<<FmtSampleRate.b<<"\n";    // 4
    cout<<FmtByteRate.b<<"\n";      // 4
    cout<<FmtBlockAlign.a<<"\n";    // 2
    cout<<FmtBitsPerSample.a<<"\n"; // 2
    
}

WavFile::~WavFile(){
    // Release all pointers
    delete data;
}


WavFile* load_wavefile(string location) {
    WavFile *neue = nullptr;
    streampos size = 0;
    ifstream wavefile (location, ios::in | ios::binary | ios::ate);
    char C32bit[4];
    char C16bit[2];
    
    
    if (wavefile.is_open()){
        size = wavefile.tellg();
        wavefile.seekg(0, ios::beg);
        char *items = new char[size];

        // starting the data structure
        if (size < 4) {
            cout<<"Error: File two small cannot get the header\n";
            return neue;
        }
        // Allocating memory
        neue = new WavFile();
        wavefile.read(neue->Id, 4);
        // Comparing if we have the RIFF value
        
        if (strcmp(neue->Id, "RIFF") != 0){
            cout<<"Error: File has a different format is not a wav file\n";
            delete neue;
            return nullptr;
        }
        // Reading chunk size
        wavefile.read(C32bit, 4);
        neue->ChuckSize = char2int(C32bit, 4);
        // Format
        wavefile.read(neue->Format, 4);
        wavefile.read(neue->FmtID, 4);
        wavefile.read(C32bit, 4);
        neue->FmtSize = char2int(C32bit, 4);
        wavefile.read(C16bit, 2);
        neue->FmtAudioFormat = char2int(C16bit, 2);   // 2
        wavefile.read(C16bit, 2);
        neue->FmtChannels = char2int(C16bit, 2);      // 2
        wavefile.read(C32bit, 4);
        neue->FmtSampleRate = char2int(C32bit, 4);    // 4
        /*
        wavefile.read(C32bit, 4);
        neue->FmtByteRate = char2int(C32bit, 4);      // 4
        wavefile.read(C16bit, 2);
        neue->FmtBlockAlign = char2int(C16bit, 2);    // 2
        wavefile.read(C16bit, 2);
        neue->FmtBitsPerSample = char2int(C16bit, 2); // 2
        */
        wavefile.close();
        
    }
    else{
        cout<<"Error: Cannot open the wavefile "<<location<<"\n";
    }
    
    return neue;
}


IntType char2int(char* item , unsigned int size){
    // Little endian son 5
    //   less           most
    //    []   []  []  []
    IntType result;
    int suma = 0;
    
    for (int i=0; i<size; i++){
           printf("-> %02x\n",item[i]);
        suma += (int(item[i])<<8*i);
    }
    
    cout<<hex<<suma<<"\n";
    
    if (size == 2){
        result.a = suma;
    }
    
    if (size == 4){
        result.b = suma;
    }
    return result;
}



void save_wavefile(WavFile* wavfile) {
    
    
    
}