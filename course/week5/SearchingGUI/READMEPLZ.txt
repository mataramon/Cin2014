

About Project flow:
	This program is intended to be used as an example of a search engine with the autocomplete feature.
	It uses a tree like structure to autocomplete a word using prefixes presented in a basic GUI.

Authors: 
	Octavio Gomez Navarro, Jorge Hernandez, Mr. Internet.

Flow description:
	-User will be asked to input a word or part of it.
	-This word will then enter a process, pushing the search button, in which it will be analyzed character by 	character.
	-Each character of the word will be compared against the tree structure, from node to node, until the end of 		 the word, or the process reaches a leaf.
	-The program first searches for a father within the tree structure, this node will be the first letter of the 		 word that the user is looking for.
	-When the search is over, the program will return the complete word (if the user provided a prefix) and a text 		 containing information about the requested subject in a separate window, that can be closed at anytime.

Scope of project:
	-Basic GUI in python Tkinter.
	-Only prefixes will be used for the autocomplete feature.
	-Uppercase and lowercase allowed for input.
	-No GUI.
	-Topic: Pets (Generic names like pig, cat, dog, bird, fish, etc. not specific names or breeds).
