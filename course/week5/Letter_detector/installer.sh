#!/bin/bash
## ==============================================================================================================
## Title:   decompressor
## File:    decompress.sh
## ==============================================================================================================
## Authors: Luis Fernando Alvarez Guerrero,  Antonio Martin Altamirano Cornejo, Daniel Alejandro Vargas Gonzalez
## ==============================================================================================================
## Script que descomprime, compila y acomoda los archivos a modo de Instalador
## ==============================================================================================================
unzip proyecto.zip
cd proyecto
## ==============================================================================================================
## Upgrade and Update
## ==============================================================================================================
sudo apt-get update -y
sudo apt-get upgrade -y
## ==============================================================================================================
## Installing Complements
## ==============================================================================================================
sudo apt-get install -y build-essential libgtk2.0-dev libjpeg-dev libtiff4-dev libjasper-dev libopenexr-dev cmake python-dev python-numpy python-tk libtbb-dev libeigen3-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev libqt4-dev libqt4-opengl-dev sphinx-common texlive-latex-extra libv4l-dev libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev default-jdk ant libvtk5-qt4-dev
## ==============================================================================================================
## Making and installing libraries
## ==============================================================================================================
unzip opencv-2.4.9.zip
cd opencv-2.4.9
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_OPENGL=ON -D WITH_VTK=ON ..
make
sudo make install -y
## ==============================================================================================================
## Compiling and executing
## ==============================================================================================================
#cd ..
#cd ..
#cd codigo
#g++ -Wall -o ProyectoV2 ProyectoV2.cpp `pkg-config --cflags --libs opencv`
#./ProyectoV2
