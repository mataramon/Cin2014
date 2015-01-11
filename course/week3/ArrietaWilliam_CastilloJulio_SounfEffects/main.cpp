/* main.cpp */
#include <iostream>
#include <string>

#include "soundhandler.h"
#include "SoundEffect.h"

using std::cout;
using std::endl;
using std::string;

// IMPORTANT: Place your file on media directory
int main (int argc, char* argv[]) {
	if (argc < 2) {
		cout << "No parameters. Enter input and output filename with proper extensions." << endl;
		return 0;
	}
	string filename = argv[1];
	string outputfile = "new_file.wav";
	if (argv[2]) 
		outputfile = argv[2];
	cout << "Select your operation";

	//switch // enum ...
	
	// OPTION 1: EFFECTS
	//SoundEffect soundhandler(filename); // or soundhandler() with default value
	//if (!soundhandler.engine())
	//	cout << "Could not startup engine" << endl;
	//cout << "PLAY..." << endl;
	//soundhandler.play("lilium.wav");	// play soound
	//cout << "PLAY ON BACKGROUND..." << endl;
	//soundhandler.playBackground("breve_espacio.mp3", "lilium.wav");
	//cout << "PLAY ECHO..." << endl;
	//soundhandler.playCustomEcho("breve_espacio.mp3");
	//cout << "PLAY 3D Sound..." << endl;
	//soundhandler.playSurround("breve_espacio.mp3");
	
	// OPTION 2: SAVE FILE
	cout << "This option will save a new file in subdirectory media" << endl;
	cout << "Select effect: " << endl;
	SoundStereo* stereo = nullptr;	// Stereo
    Sound* sound = nullptr;			// Mono
    
	string location = "media/" + filename; // stereo
    auto file = load_wavefile(location);

    if (file != nullptr) {
        sound = get_vectors(file);

        if (sound == nullptr)	{
            cout<<"Sound:Error: Not format compatible found\n";
            return 1;
        }
        cout<<"Type found: "<<sound->Type()<<"\n";
       
		if (sound->Type() == "stereo") {			 // Using the right object
            stereo = static_cast<SoundStereo*>(sound);
            cout<<"okay \n";
        }

		file->MulSeno(1000);
		file->eco(0.2, 0.5);
		file->reverse();
		save_wavefile(file, outputfile);    
    }
	else {
        cout<<"Not memory assigned\n";
    }
	char playfile;
	cout << "Would you like to plat output file? [Y/N] " << endl;
	cin >> playfile;
	if (playfile == 'Y' || playfile == 'y') {
		cout << "Playing..";
		SoundEffect soundhandler(outputfile);
		if (!soundhandler.engine()) {
			cout << "Could not startup engine" << endl;
		}
		cout << "PLAY..." << endl;
		soundhandler.play();	// play sound
	}
	
	return 0;
}
