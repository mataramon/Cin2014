/* SoundEffect.cpp */ 
#include <iostream>
#include "SoundEffect.h"

using std::cout;
using std::endl;
using irrklang::createIrrKlangDevice;
using irrklang::vec3df;

SoundEffect::SoundEffect(std::string filename/*="lilium.wav"*/): filename_(filename) { 
	engine_ = createIrrKlangDevice();
}

void SoundEffect::play(bool loop/*=false*/) {
	filename_ = "media/" + filename_;
	cout << "Press ESC to quit" << endl;
	cout << "Playing: " << filename_ << endl;
	engine_->play2D(filename_.c_str(), loop);
	while (true) {
		int key = getch();
		if (key == 27)
			break; // user pressed ESCAPE key
	} 
}


void SoundEffect::playBackground(std::string background, std::string foreground) {
	background = "media/" + background;
	foreground = "media/" + foreground;
	cout << "Playing on background: " << background << "\t";
	cout << "Playing in foreground: " << foreground << endl;
	engine_->play2D(background.c_str(), true);
	do {
		cout << "Pres ESC to quit or another key to play again" << endl;
		engine_->play2D(foreground.c_str());
	} while (getch() != 27 );
}

void SoundEffect::playCustomEcho(std::string filename, int echoLength/*=10*/, int delay/*=2*/, int repeatTimes/*=3*/) { 
	filename = "media/" + filename;
	cout << "Playing: " << filename << endl;
	int n = 0;
	do {
		engine_->play2D(filename.c_str());
		sleep(delay);
		n++;	
		if (n == repeatTimes)
			sleep(echoLength);
	} while (n != repeatTimes);
}

void SoundEffect::playSurround(std::string filename) {
	filename = "media/" + filename;
	cout << "Playing: " << filename << endl;
	music_ = engine_->play3D(filename.c_str(), vec3df(0,0,0), true, false, true);
	if (music_)
		music_->setMinDistance(5.0f);
	cout << "\nPlaying streamed sound in 3D." << endl;
	cout << "Press ESCAPE to quit, any other key to play sound at random position." << endl << endl;
	cout << "+ = Listener position" << endl;
	cout << "o = Playing sound" << endl;
	float posOnCircle = 0;
	const float radius = 5;
	while(true) {// endless loop until user exits
		posOnCircle += 0.04f;
		vec3df pos3d(radius * cosf(posOnCircle), 0, radius * sinf(posOnCircle * 0.5f));
		engine_->setListenerPosition(vec3df(0,0,0), vec3df(0,0,1));
		if (music_)
			music_->setPosition(pos3d);
		char stringForDisplay[] = "          +         ";
		int charpos = (int)((pos3d.X + radius) / radius * 10.0f);
		if (charpos >= 0 && charpos < 20)
			stringForDisplay[charpos] = 'o';
		int playPos = music_ ? music_->getPlayPosition() : 0;
		printf("\rx:(%s)   3dpos: %.1f %.1f %.1f, playpos:%d:%.2d    ",
			stringForDisplay, pos3d.X, pos3d.Y, pos3d.Z,
			playPos/60000, (playPos%60000)/1000 );
		sleepSomeTime();
		if (kbhit())
		{
			int key = getch();
			if (key == 27)
				break; // user pressed ESCAPE key
			else	{
				vec3df pos(fmodf((float)rand(),radius*2)-radius, 0, 0);
				const char* filename;
				if (rand()%2)
					filename = "media/bell.wav";
				else
					filename = "media/explosion.wav";
				engine_->play3D(filename, pos);
				printf("\nplaying %s at %.1f %.1f %.1f\n",
					filename, pos.X, pos.Y, pos.Z);
			}
		}
	}
	if (music_)
		music_->drop(); // release music stream.
}

SoundEffect::~SoundEffect(){
	engine_->drop();
}
