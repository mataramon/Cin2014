/* SoundEffect.h */

#ifndef SOUNDEFFECT_H_
#define SOUNDEFFECT_H_

#include <string>

#include "irrKlang.h"
#include "common/conio.h"


class SoundEffect  {
	
	private:
	irrklang::ISoundEngine* engine_;
	irrklang::ISound* music_;
	std::string	filename_;
	public:
		SoundEffect(std::string filename="lilium.wav");
		~SoundEffect();
		irrklang::ISoundEngine* engine() { return engine_; }
		void play(bool loop=false);
		void playBackground(std::string background, std::string foreground);
		void playCustomEcho(std::string filename, int echoLength=10, int delay=2, int repeatTimes=3);
		void playSurround(std::string filename);
};

#endif
