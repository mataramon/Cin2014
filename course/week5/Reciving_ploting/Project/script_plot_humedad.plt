#gnuplot script > grafica.png   para correr el script y redirigirlo a al png
#Toma en cuenta el numero de muestra y la informacion de la humedad (columna 1 y 3)

set terminal png
set title "Grafica de Humedad"          
set xlabel "no. muestra"               
set ylabel "porcentaje(%) en Humedad" 
set yrange [0:90]                   
set output "grafica_temperatura.png"
plot "hum.dat" using 1:3 w l
