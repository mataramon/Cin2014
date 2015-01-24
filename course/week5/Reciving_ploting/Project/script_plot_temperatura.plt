#gnuplot script > grafica.png   para correr el script y redirigirlo a al png
#Toma en cuenta el numero de muestra y la informacion de la temperatura (columna 1 y 2)

set terminal png
set title "Grafica de Temperatura"          
set xlabel "no. de muestra"               
set ylabel "Temperatura en grados centigrados"
set yrange [0:50]       
set output "grafica_humedad.png"             
plot "temp.dat" using 1:2 w l
