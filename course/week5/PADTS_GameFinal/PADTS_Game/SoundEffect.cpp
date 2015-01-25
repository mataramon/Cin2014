/* SoundEffect.cpp */ 
#include <iostream>
#include "SoundEffect.h"
using std::cout;
using std::endl;

using irrklang::createIrrKlangDevice;
using irrklang::vec3df;


SoundEffect::SoundEffect(std::string filename/*="lilium.wav"*/) { 
	engine_ = createIrrKlangDevice();
}

void SoundEffect::play(std::string filenames, bool loop/*=false*/) {
	//filenames = "../media/" + filenames;	
	//cout << "Playing: " << filenames << endl;
	//cout << "Press ENTER to play game" << endl;
	engine_->play2D(filenames.c_str(), loop);
	/*while (true) {
		int key = getch();
		if (key == 27)
			break; // user pressed ESCAPE key
	}*/
}

SoundEffect::~SoundEffect()
{
	engine_->drop();
}
