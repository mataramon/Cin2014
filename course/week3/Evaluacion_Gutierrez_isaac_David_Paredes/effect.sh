#!/bin/bash



# Script to make easy the handling of program write in c++, to create files wav with effects
# a file .wav must been exist, and folder were the objetc must be store,  the script is divide in
# the next functions to make easy the understanding how it works
# Authors:
# 			Gutierrez Arrazola Isaac
#			Paredes Cardona David Ivan

# check_compile :		Program to check if the program in C++ if already compile in the system
# check_file	:		Look if the file is exist, and the extension file (wav)
# run_program 	:		Execute the program , reciving the argument (file)
# alert_finish  :		Advised the user already if finish all the program
# delete_all    :		Erase the folder where is the object save

# script For linux, Alsa must be in the sysem (aplay)
# effect.exec  -> file executable
# main_effect.cpp -> file main
# effect.wav -> archivo wav creado

PWD_back=pwd

function check_compile {
if [ -d $HOME/.data_effect ]; then
	g++  $1 -o $HOME/.data_effect/test.exec
	chmod u+x $HOME/.data_effect/test.exec
else
	mkdir $HOME/.data_effect
	g++  $1 -o $HOME/.data_effect/test.exec
	chmod u+x $HOME/.data_effect/test.exec
fi
}


extRegex=".+\.wav"

function check_file {
	if [[ $1 =~ $extRegex ]]; then
	echo "File valid "
	else
	echo "File with extension no valid $2"
	exit 0
	fi
}

function run_program {
	cd $HOME/.data_effect
	./test.exec $2
}

function finish_run {
	aplay -q effect.wav
	echo "Thank you for using this program"
}

function delete_all {
	echo "delete all relate to program"
	rm -rf $HOME/.data_effect
}

#-----------------------run
if [ "$1" == "-erase_all" ]; then
	echo "deleting object and folder..."
	delete_all
	exit 0
fi

check_compile $1
check_file $2
run_program $2
finish_run




