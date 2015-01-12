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
	
	enum Options { EFFECTS=1, SAVE=2 };
	Options option;
	int choise;
	int effect;
	string filename;
	string outputfile = "outputfile.wav";
	
	if (argc < 2) {
		cout << "No parameters. Enter input and output filename with proper extensions." << endl;
		return 0;
	}
	filename = argv[1];
	if (argv[2]) {
		outputfile = argv[2];
	}
	cout << "Select your operation, select the number." << endl;
	cout << "1. EFFECTS: Reproduce your file with selected effects." << endl;
	cout << "2. SAVE FILE: Saves output file in media/ subdirectory." << endl;
	cout << "OPTION : ";
	cin >> choise;
	if (choise == 1) option = EFFECTS;
	else if (choise == 2) option = SAVE;
	else {
		cout << "Not valid option. Run program again." << endl; 
		return 0;
	}
	if (option == EFFECTS) {
		SoundEffect soundhandler(filename); // or soundhandler() with default value
		if (!soundhandler.engine())
			cout << "Could not startup engine" << endl;
		cout << "\tSelect effect: " << endl;
		cout << "\t1. Play audio " << endl
			 << "\t2. Play audio in background " << endl
			 << "\t3. Play audio with echo " << endl
			 << "\t4. Play 3D sound " << endl;
		cout << "\tEFFECT: " ;
		cin >> effect;
		switch (effect) {
		case 1:
			cout << "PLAY..." << endl;
			soundhandler.play(filename);	// play soound
			break;
		case 2: 
			cout << "PLAY ON BACKGROUND..." << endl;
			soundhandler.playBackground("breve_espacio.mp3", filename);
			break;
		case 3:
			cout << "PLAY ECHO..." << endl;
			soundhandler.playCustomEcho(filename);
			break;
		case 4: 
			cout << "PLAY 3D Sound..." << endl;
			soundhandler.playSurround(filename);
			break;
		default: 
			cout << "Not valid option. Run program again." << endl;
			return 0;
		}
	}

	// OPTION 2: SAVE FILE
	if (option == SAVE) {
		// cout << "Select effect: " << endl;
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
			cout << "\nFile saved as media/" << outputfile  << endl;
		}
		else {
		    cout<<"Not memory assigned\n";
		}
		char playfile;
		cout << "Would you like to plat output file? [Y/N] " ;
		cin >> playfile;
		if (playfile == 'Y' || playfile == 'y') {
			SoundEffect soundhandler(outputfile);
			if (!soundhandler.engine()) {
				cout << "Could not startup engine" << endl;
			}
			soundhandler.play(outputfile);	// play sound
		}
	}
	return 0;
}

