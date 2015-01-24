#!/bin/bash

cp $1 temp.dat 
cp $1 hum.dat

gnuplot script_plot_temperatura.plt
gnuplot script_plot_humedad.plt