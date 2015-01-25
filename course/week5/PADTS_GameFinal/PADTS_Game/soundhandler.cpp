//
//  soundhandler.cpp
//  Sound
//
//  Created by Angel Jovany Figueroa Ypiña on 12/30/14.
//  Copyright (c) 2014 Angel Jovany Figueroa Ypiña. All rights reserved.
//
// C headers 
//#include "StdAfx.h"
#include "soundhandler.h"
#include <stdio.h>   
#include <stdlib.h>   
#include <string.h>


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
    for (int i=0;i<DataSize.b;i++)
	{
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
    // Release all pointers
    delete data;
}

void WavFile::reverse()
{
    int i;
	for (i = 0; i < DataSize.b; i++);
	char* newM = new char[i];

	for (int j = 0; j < i; j++)
	{
        newM[j] = data[j];
    }
	for (int j = 0; j < i; j += 2)
	{
		// Voltea en grupos de 16 bits
        data[j]	  = newM[i - 2 - j];
		data[j+1] = newM[i - 1 - j];
    }
	
} 

void WavFile::eco(float tiempo, float G)	// G = Ganancia del eco
{
	int Tiempo = tiempo * FmtSampleRate.b;
    int i;
	for (i = 0; i < DataSize.b; i++);
	char* newM = new char[i];

	for (int j = 0; j < i; j++)
	{
        newM[j] = data[j];
    }

	// ECO
	for(int j = Tiempo; j < i; j += 2)
	{
		data[j] = newM[j]+data[j-Tiempo]*G;
		data[j+1] = newM[j+1]+data[j+1-Tiempo]*G;
	}
	
} 


void WavFile::MulSeno(float f)
{
	float Freq = (1/f)*(FmtSampleRate.b*2);

    int i;
	for (i = 0; i < DataSize.b; i++);
	char* newM = new char[i];

	for (int j = 0; j < i; j++)
	{
        newM[j] = data[j];
    }
	
	// MULTIPLICAR POR SEÑAL SENO
	float volumeQ = 0;	// va de 0 a 1 y viceversa en cambios de volumeInc;
	float volumeInc = 1/Freq;
	cout<<volumeInc;
	getchar();
	for(int j = 0; j < i; j++)
	{
		data[j] = newM[j]*volumeQ;//+data[j-14000]*0.75;
		data[j+1] = newM[j+1]*volumeQ;//+data[j+1-14000]*0.75;
		
		if(volumeQ > 1 || volumeQ < 0)
			volumeInc *= -1;
		volumeQ += volumeInc;
	}
	
} 

WavFile* load_wavefile(string location) {
    WavFile *neue = nullptr;
    streampos size = 0;
    ifstream wavefile (location, ios::in | ios::binary | ios::ate);
    char C32bit[4];
    char C16bit[2];
    
    if (wavefile.is_open())
	{
        size = wavefile.tellg();
        wavefile.seekg(0, ios::beg);
        
        // starting the data structure
        if (size < 4)
		{
            cout<<"Error: File is too small, cannot get the header\n";
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
        // Loading all the file to memory
        wavefile.read(neue->data, neue->DataSize.b);
        
        wavefile.close();
        
    }
    else
	{
        cout<<"Error: Cannot open the wavefile "<<location<<"\n";
    }
    
    return neue;
}

Sound::Sound(WavFile* data)
{
    // we use short to take the bits per sample 
    type = "mono";
    // Number of bits to be used
    int bytes = data->FmtBitsPerSample.a/8;
    
    // Then reading the number of items that fills in size
    for (int i=0; i<data->DataSize.b;i=i+bytes)
	{
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
    for (auto i : this->mono)
	{
        float magnitude = float(i.b)/float(abs(max_val->b));
        items.push_back(magnitude);
    }
    return items;
} 

Sound::~Sound(){
    
}

SoundStereo::SoundStereo(WavFile* data) : Sound(data)
{
    // The difference are the channels
    // with two channels
    // [ LEFT RIGHT ] 16 bits per sample, but with two channels is 32 bits each sample
    
    // Overwriting then type
    this->type = "stereo";
    // Number of bits to be used
    int bytes = data->FmtBitsPerSample.a/8;
    
    for (int i=0; i<data->DataSize.b-bytes;i=i+(2*bytes))
	{
        auto value = char2int(&(data->data[i]), bytes);
        //cout<<"left "<<i<<"\n";
        left.push_back(value);
    }
    
    for (int i=bytes; i<data->DataSize.b;i=i+(2*bytes))
	{
        auto value = char2int(&(data->data[i]), bytes);
        //cout<<"right "<<i<<"\n";
        right.push_back(value);
    }
    
    cout<<"Stereo information\n";
    cout<<"Channel 1: "<<left.size()<<" samples\n";
    cout<<"Channel 2: "<<right.size()<<" samples\n";

}

vector<vector<float>> SoundStereo::Signal()
{
    vector<vector<float>> items;
    vector<float> Left ;
    vector<float> Right;
    
    auto max_val = max_element(this->left.begin(), this->left.end(), abs_val);
    
    cout<<"max value:"<<max_val->a<<"\n";
    
    for (auto &i : this->left)
	{
        float magnitude = float(i.a)/float(abs(max_val->a));
        Left.push_back(magnitude);
    }
    
    max_val = max_element(this->right.begin(), this->right.end(), abs_val);
    
    for (auto &i : this->right)
	{
        float magnitude = float(i.b)/float(abs(max_val->b));
        Right.push_back(magnitude);
    }
    
    items.push_back(Left);
    items.push_back(Right);
    
    return items;
} 

void Sound::reverse()
{
	vector<IntType> newM ;
    
    for (int i = 0; i < mono.size(); i++)
	{
        newM.push_back(mono[i]);
    }
	for (int i = 0; i < mono.size(); i++)
	{
        mono[i] = newM[mono.size() - 1 - i];
    }
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
    
    for (unsigned int i=0; i<size; i++){
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


// ------ My Functions (PADTS) -------
void SoundStereo::reverse()
{
	vector<IntType> newL ;
	vector<IntType> newR ;
    
    for (int i = 0; i < left.size(); i++)
	{
        newL.push_back(left[i]);
    }
	for (int i = 0; i < left.size(); i++)
	{
        left[i] = newL[left.size() - 1 - i];
    }
    
    for (int i = 0; i < right.size(); i++)
	{
        newR.push_back(right[i]);
    }
	for (int i = 0; i < right.size(); i++)
	{
        right[i] = newR[right.size() - 1 - i];
    }
} 

// Funcion para guardar archivo .wav
void save_wavefile(WavFile* wavfile, std::string outputfile)
{
	outputfile = "media/" + outputfile;
    if (wavfile)
	{
		char ptr4[32];
		char ptr2[16];

		ofstream wavefile(outputfile, ios::binary);

		wavefile.write(wavfile->Id, 4);
		wavefile.put( wavfile->ChuckSize.b);
		wavefile.put( wavfile->ChuckSize.b >> 8);
		wavefile.put( wavfile->ChuckSize.b >> 16);
		wavefile.put( wavfile->ChuckSize.b >> 24);
        wavefile.write(wavfile->Format, 4);
        wavefile.write(wavfile->FmtID, 4);
		wavefile.put(wavfile->FmtSize.b);
		wavefile.put(wavfile->FmtSize.b >> 8);
		wavefile.put(wavfile->FmtSize.b >> 16);
		wavefile.put(wavfile->FmtSize.b >> 24);
		wavefile.put(wavfile->FmtAudioFormat.a);
		wavefile.put(wavfile->FmtAudioFormat.a >> 8);
		wavefile.put(wavfile->FmtChannels.a);
		wavefile.put(wavfile->FmtChannels.a >> 8);
		wavefile.put(wavfile->FmtSampleRate.b);
		wavefile.put(wavfile->FmtSampleRate.b >> 8);
		wavefile.put(wavfile->FmtSampleRate.b >> 16);
		wavefile.put(wavfile->FmtSampleRate.b >> 24);
		wavefile.put(wavfile->FmtByteRate.b);
		wavefile.put(wavfile->FmtByteRate.b >> 8);
		wavefile.put(wavfile->FmtByteRate.b >> 16);
		wavefile.put(wavfile->FmtByteRate.b >> 24);
		wavefile.put(wavfile->FmtBlockAlign.a);
		wavefile.put(wavfile->FmtBlockAlign.a >> 8);
		wavefile.put(wavfile->FmtBitsPerSample.a);
		wavefile.put(wavfile->FmtBitsPerSample.a >> 8);
        wavefile.write(wavfile->DataID, 4);
		wavefile.put(wavfile->DataSize.b);
		wavefile.put(wavfile->DataSize.b >> 8);
		wavefile.put(wavfile->DataSize.b >> 16);
		wavefile.put(wavfile->DataSize.b >> 24);
        // Saving all the file
        wavefile.write(wavfile->data, wavfile->DataSize.b);
        
        //wavefile.close();


    }
}
