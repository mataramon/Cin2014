/* SoundEffect.h */

#ifndef SOUNDEFFECT_H_
#define SOUNDEFFECT_H_

#include <string>
#include <irrKlang.h>

#if defined(WIN32)
#include <conio.h>
#include <Windows.h>
#else
#include <conio.h>
#endif

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll


class SoundEffect  {
	
	private:
	
	irrklang::ISound* music_;
	
	public:
		irrklang::ISoundEngine* engine_;
		SoundEffect(std::string filename);
		~SoundEffect();
		irrklang::ISoundEngine* engine() { return engine_; }
		void play(std::string filename, bool loop=false);
		void playBackground(std::string background, std::string foreground);
		void playCustomEcho(std::string filename, int echoLength=10, int delay=2, int repeatTimes=3);
		void playSurround(std::string filename);
};

#endif
