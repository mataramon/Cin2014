

//---------------------------------------------------------------------------
#pragma argsused
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdint.h>
#include <conio.h>
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>
#include <ostream>
#include <stdlib.h>

#include "WAVE.h"

using namespace std;
int option=0;

static void reportProblem()
{
	cout << "  *** ERROR: Result incorrect." << endl;
}

static void checkResult(bool got, bool expected)
{
	if (got)
		cout << "success." << endl;
	else
		cout << "fail." << endl;

	if (got != expected)
		reportProblem();
}


static void ShowErrors(WaveFile& from, WaveFile& to)
{
	bool any = from.GetError() || to.GetError();

	if (from.GetError())
		cout << "Error on input: " << from.GetError() << "." << endl;

	if (to.GetError())
		cout << "Error on output: " << to.GetError() << "." << endl;

	if (!any)
		cout << "Success." << endl;
}

static void ShowFormat(WaveFile& wave)
{
	cout
		<< "Format:           " << wave.GetFormatType()
		<< (wave.IsCompressed()? " (compressed)" : " (PCM)") << endl
		<< "Channels:         " << wave.GetNumChannels() << endl
		<< "Sample rate:      " << wave.GetSampleRate() << endl
		<< "Bytes per second: " << wave.GetBytesPerSecond() << endl
		<< "Bytes per sample: " << wave.GetBytesPerSample() << endl
		<< "Bits per channel: " << wave.GetBitsPerChannel() << endl
		<< "Bytes:            " << wave.GetDataLength() << endl
		<< "Samples:          " << wave.GetNumSamples() << endl
		<< "Seconds:          " << wave.GetNumSeconds() << endl
		<< "File pointer:     " << (wave.GetFile()? "good" : "null") << endl;

	string type, value;
	if (wave.GetFirstExtraItem(type, value)) {
		cout << "Extra data:" << endl;
		do {
			cout << "  " << type << ": " << value << endl;
		} while (wave.GetNextExtraItem(type, value));

		wave.ResetToStart();
	}

	system("pause");
	system("cls");
}


//---------------------------------------------------------------------------
int main(int argc, char **argv) {
    WaveFile in;
	if (!in.OpenRead(argv[1])) {
		cout << "Can't open source file: " << argv[1] << " for reading." << endl;
		cout << "Usage: " << argv[0] << " input.wav output.wav" << endl;
		cout << in.GetError() << endl;
		return 1;
	}

	WaveFile out;
	out.SetupFormat(in.GetSampleRate(), in.GetBitsPerChannel());

	if (!out.OpenWrite(argv[2])) {
		cout << "Can't open destination file: " << argv[2] << " for writing." << endl;
		cout << "Usage: " << argv[0] << " input.wav output.wav" << endl;

		cout << out.GetError() << endl;
		return 1;
	}

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
	 cout<<"Succes creating \""<<argv[2]<<"\""<<endl;
	 system("pause");
	 system("cls");



	return 0;

}//end of program
