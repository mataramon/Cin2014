#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdint.h>
#include <conio.h>
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <ostream>
#include <Windows.h>

#include "WAVE.h"
#include "Riffile.h"
#include "Workspace.h"
#include "tremolo.h"


using namespace std;


	
	CWorkspace::CWorkspace()
	{
		pWave= new WaveFile();
	     
	
	}

	CWorkspace::~CWorkspace()
	{
		delete pWave;
		
	}

	void CWorkspace::LoadSLOW(const char* FileName)
	{
		const char* output="slow.wav";
	    const char* input=FileName;
		
		WaveFile in;
	    if (!in.OpenRead(input)) {
		cout << "Can't open " << input << " for reading." << endl;
		cout << in.GetError() << endl;
	
	    }
		WaveFile out;
	    out.SetupFormat(in.GetSampleRate(), in.GetBitsPerChannel());

	    if (out.OpenWrite(output)) {
		
		
	                                  

	const size_t delayLength = size_t(0.2 * out.GetSampleRate());  // in samples

	float* delayBuffer = new float[delayLength];

	for (size_t i = 0; i < in.GetNumSamples() + delayLength; i++) {
		float outputSample = 0;

		if (i < in.GetNumSamples()) {
			in.ReadSample(outputSample);

			outputSample *= 0.6;
		}

		if (i > delayLength)
			outputSample += delayBuffer[i % delayLength] * 0.5;

		out.WriteSample(outputSample);

		delayBuffer[i % delayLength] = outputSample;

	}
	delete []delayBuffer;

		}
	

}

	/*
void CWorkspace:: LoadECO(const char *FileName)
	{
		const char* output="eco.wav";
	    const char* input=FileName;
		
		WaveFile in;
	    if (!in.OpenRead(input)) {
		cout << "Can't open " << input << " for reading." << endl;
		cout << in.GetError() << endl;
	
	    }
		WaveFile out;
	    out.SetupFormat(in.GetSampleRate(), in.GetBitsPerChannel());

	    if (out.OpenWrite(output)) {
		
	                                  
		           size_t const m = in.GetNumSamples();
                    float samplesCpy[m];

                    for (size_t i = 0; i < in.GetNumSamples(); i++) {
                        float outputSample = 0;
                        in.ReadSample(outputSample);
                        outputSample *= 0.6;
                        samplesCpy[m--] = outputSample;
                    }

                    for (size_t i = 0; i < in.GetNumSamples(); i++) {
                        out.WriteSample(samplesCpy[i]);
                    }

	
		 const size_t delayLength = size_t(0.5 * out.GetSampleRate());

                    float* delayBuffer = new float[delayLength];

                    for (size_t i = 0; i < in.GetNumSamples() + delayLength; i++) {
                        float outputSample = 0;
                        if (i < in.GetNumSamples()) {
                            in.ReadSample(outputSample);
                            outputSample *= 3;
                        }
                        if (i > delayLength)
                            outputSample = outputSample + delayBuffer [i % delayLength] /2 ;
                        out.WriteSample(outputSample);
                        delayBuffer[i % delayLength] = outputSample;
                    }
                    delete delayBuffer;

		}
	
	
}
*/
void CWorkspace::LoadTREMOLO(const char* FileName)
{

	    char* output="tremolo.wav";
	    const char* input=FileName;
		
		WaveFile in;
	    if (!in.OpenRead(input)) {
		cout << "Can't open " << input << " for reading." << endl;
		cout << in.GetError() << endl;
	
	    }
		WaveFile out;
	    out.SetupFormat(in.GetSampleRate(), in.GetBitsPerChannel());

	    if (out.OpenWrite(output)) {
		
					Tremolo_init(4000, 1);
                    float outputSample = 0;

                    for(size_t i = 0; i < in.GetNumSamples(); i++) {
                        in.ReadSample(outputSample);
                        outputSample = Tremolo_process(0.7 * outputSample);
						out.WriteSample(outputSample);
						Tremolo_sweep();
                    }   
		}


}
	

