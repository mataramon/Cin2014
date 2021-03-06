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
    header = nullptr;
    
}

void WavFile::display(void){
    cout<<"Header         : "<<header<<"\n";
    cout<<"ID             : "<<Id<<"\n";
    cout<<"Chunck Size    : "<<ChuckSize.b<<"\n";
    cout<<"Format         : "<<Format<<"\n";
    cout<<"Format ID      : "<<FmtID<<"\n";
    cout<<"Format Size    : "<<FmtSize.b<<"\n";
    cout<<"Audio Format   : "<<FmtAudioFormat.a<<"\n";
    cout<<"Channels       : "<<FmtChannels.a<<"\n";      // 2
    cout<<"Sample Rate    : "<<FmtSampleRate.b<<"\n";    // 4
    cout<<"Byte   Rate    : "<<FmtByteRate.b<<"\n";      // 4
    cout<<"Block  Align   : "<<FmtBlockAlign.a<<"\n";    // 2
    cout<<"Bits per Sample: "<<FmtBitsPerSample.a<<"\n"; // 2
    cout<<"Data ID        : "<<DataID<<"\n";
    cout<<"Data Size      : "<<DataSize.b<<"\n";
    cout<<"------------------FILE CONTENT---------------------\n";
  //  for (int i=0;i<DataSize.b;i++){
      for (int i=0;i<32;i++){
        unsigned int pref = data[i];
        // removing zeros only 8 bytes
        pref = pref<<24;
        pref = pref>>24;
        printf("%02x ", pref);
        if (i % 30 == 0) cout<<"\n";
    }
    
    //cout<<"left:"<<left<<"\n";
    
    cout<<"\n------------------END CONTENT-----------------------\n";
    
}

WavFile::~WavFile(){
    // Release all pointers‘->
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
        if (neue->FmtAudioFormat.a != 1) {
            cout<<"Error: Currently only PCM Format = 1 is supported\n";
            delete neue;
            return nullptr;
        }
        
        
        wavefile.read(C16bit, 2);
        neue->FmtChannels = char2int(C16bit, 2);      // 2
        wavefile.read(C32bit, 4);
        neue->FmtSampleRate = char2int(C32bit, 4);    // 4
        
        wavefile.read(C32bit, 4);
        neue->FmtByteRate = char2int(C32bit, 4);      // 4
        wavefile.read(C16bit, 2);
        neue->FmtBlockAlign = char2int(C16bit, 2);    // 2
        wavefile.read(C16bit, 2);
        neue->FmtBitsPerSample = char2int(C16bit, 2); // 2
        wavefile.read(neue->DataID, 4);
        wavefile.read(C32bit, 4);
        neue->DataSize = char2int(C32bit, 4);
        // Loading all the samples
        neue->data = new char[neue->DataSize.b];
        neue->header = new char[44];
        // Loading all the file to memory
        wavefile.read(neue->data, neue->DataSize.b);
        wavefile.seekg(0);
        wavefile.read(neue->header, 44);
        
        wavefile.close();
        
    }
    else{
        cout<<"Error: Cannot open the wavefile "<<location<<"\n";
    }
    
    return neue;
}

Sound::Sound(WavFile* data){
    // we use short to take the bits per sample 
    type = "mono";
    // Number of bits to be used
    int bytes = data->FmtBitsPerSample.a/8;
    
    // Then reading the number of items that fills in size
    for (int i=0; i<data->DataSize.b;i=i+bytes){
        auto value = char2int(&(data->data[i]), bytes);
        //cout<<"Mono: "<<i<<"\n";

        mono.push_back(value);
    }
    cout<<"Mono information\n";
    cout<<"Channel 1: "<<mono.size()<<" samples\n";

}

vector<float> Sound::Signal(){
    vector<float> items;
    auto max_val = max_element(this->mono.begin(), this->mono.end(), abs_val);
    for (auto &i : this->mono){
        float magnitude = float(i.b)/float(abs(max_val->b));
        items.push_back(magnitude);
    }
    return items;
} 

Sound::~Sound(){
    
}

SoundStereo::SoundStereo(WavFile* data) : Sound(data){
    // The difference are the channels
    // with two channels
    // [ LEFT RIGHT ] 16 bits per sample, but with two channels is 32 bits each sample
    
    // Overwriting then type
    this->type = "stereo";
    // Number of bits to be used
    int bytes = data->FmtBitsPerSample.a/8;
    
    for (int i=0; i<data->DataSize.b-bytes;i=i+(2*bytes)){
        auto value = char2int(&(data->data[i]), bytes);
        //cout<<"left "<<i<<"\n";
        left.push_back(value);
    }
    
    for (int i=bytes; i<data->DataSize.b;i=i+(2*bytes)){
        auto value = char2int(&(data->data[i]), bytes);
        //cout<<"right "<<i<<"\n";
        right.push_back(value);
    }
    
    cout<<"Stereo information\n";
    cout<<"Channel 1: "<<left.size()<<" samples\n";
    cout<<"Channel 2: "<<right.size()<<" samples\n";

}

vector<vector<float>> SoundStereo::Signal(){
    vector<vector<float>> items;
    vector<float> Left ;
    vector<float> Right;
    
    auto max_val = max_element(this->left.begin(), this->left.end(), abs_val);
    
    cout<<"max value:"<<max_val->a<<"\n";
    
    for (auto &i : this->left){
        float magnitude = float(i.a)/float(abs(max_val->a));
        Left.push_back(magnitude);
    }
    
    max_val = max_element(this->right.begin(), this->right.end(), abs_val);
    
    for (auto &i : this->right){
        float magnitude = float(i.b)/float(abs(max_val->b));
        Right.push_back(magnitude);
    }
    
    items.push_back(Left);
    items.push_back(Right);
    
    return items;
} 

SoundStereo::~SoundStereo(){  
}

IntType char2int(char* item , unsigned int size){
    // Little endian
    //   less           most
    //    []   []  []  []
    IntType result;
    result.b = 0; // cleaning the value
    int suma = 0;
    
    for (int i=0; i<size; i++){
        unsigned int pref = item[i];
        // removing zeros only 8 bytes
        pref = pref<<24;
        pref = pref>>24;
        suma += (pref<<8*i);
    }
        
    if (size == 2){
        result.a = suma;
    }
    
    if (size == 4){
        result.b = suma;
    }
    return result;
}

void save_wavefile(WavFile* wavfile) {

    ofstream outfile ("waveoutfile.wav", ios::out | ios::binary | ios::app);
 
   for (int j=0;j<44;j++){ 
    outfile << wavfile->header[j];
     }
   for (int i=0;i<wavfile->DataSize.b;i++){
//for (int i=0;i<32;i++){
    //    unsigned int pref = wavfile->ChuckSize.b;
    //    pref = pref<<24;
    //    pref = pref>>24;
    //	outfile << pref;
          outfile << wavfile->data[i];
      }
    outfile.close();
	
}

Sound* get_vectors(WavFile* data){
    // Pointer to base class
    Sound *sound = nullptr;
    
    switch (data->FmtChannels.a){
        case 1:
            sound = new Sound(data);
            break;
        case 2:
            sound = new SoundStereo(data);
            break;
        default:
            cout<<"Error: cannot create a container for this number of channels: "<<data->FmtChannels.a<<"\n";
            break;
    }
    
    return sound;
}

static bool abs_val(IntType x, IntType y){
    return (abs(x.a) < abs(y.a));
}


void Eco(WavFile* audio)
{
	int i;
	auto delay = audio->FmtSampleRate.b/2;
	auto length = audio->DataSize.b;
	int B[length+delay];
	int C[length+delay];
	

	for(i=0; i<length; i++)
	{
		C[i]=audio->data[i];
		B[delay+i]=audio->data[i];
	}

	for(i=0;i<delay;i++)
	{
		C[length+i]=0;
		B[i]=0;
	}

	for(i=0;i<(length);i++)
	{
		audio->data[i] = B[i]+C[i];
	}
	
}
