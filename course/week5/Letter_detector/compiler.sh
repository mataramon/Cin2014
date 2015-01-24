#!/bin/bash
cd codigo
g++ -Wall -o ProyectoV2 ProyectoV2.cpp `pkg-config --cflags --libs opencv`
./ProyectoV2
