#python v3.4
'''libreria necesaria: pyserial v2.7 (modulo necesario y extra al conjunto que viene 
    por defecto al interprete de python 3 , ver recomendaciones al ejecutarse en windows
http://pyserial.sourceforge.net/  
para plotear los datos se necesita gnuplot
cuando se ejecuta el .sh esta desarrollado para funcionar con 3 columnas,
proporcionadas por uC '''

#------------------
import os
import sys
import subprocess 
#--------------
import datetime
import serial
import time

x = datetime.datetime.today()
nombre_archivo ="{}-{}-{}-{}-{}-{}.dat".format(x.year,x.month,x.day,x.hour,x.minute,x.second)
print ('Creacion de archivo: {}'.format(nombre_archivo))

texto = open(nombre_archivo,mode='w')

contador = 0
puerto_nuevo = 0
intentos_abriendo_puerto = 0
puerto_open_exitoso = False

while intentos_abriendo_puerto < 3:
    try:
        print('Intentando abrir el puerto ACM{}...'.format(puerto_nuevo))
        path_tty = ('/dev/ttyACM{}'.format(puerto_nuevo))
        ser = serial.Serial(path_tty,baudrate=9600,timeout=5)
    except IOError:
        puerto_nuevo += 1
        if puerto_nuevo > 50:
            intentos_abriendo_puerto += 1
            puerto_nuevo = 0
            print('Intento: {} reiniciando conexion... '.format(intentos_abriendo_puerto),end=' ',flush=True)
            time.sleep(1)
            print('3 ',end=' ',flush=True)
            time.sleep(1)
            print('2 ',end =' ',flush=True)
            time.sleep(1)
            print('1 ...',flush=True)
            time.sleep(1) 
    except:
        print('Problemas no esperados con la conexion serial')
    else: 
        print('Exito abriendo el puerto: ACM{}'.format(puerto_nuevo))
        puerto_open_exitoso = True
        break
if puerto_open_exitoso:  
    while contador<30: 
        try:    
            cadena_texto=ser.readline()
            #cadena_texto='{} {}'.format(contador,cadena_texto)
            #cadena_texto ="{} {}".format(contador,cadena_texto_1)
            cadena_guardada=cadena_texto.decode('utf-8')
            texto.write(cadena_guardada)
            print(cadena_texto)
            contador=contador+1
        except:
            print('{} cerrado prematuramente debido a una interrupcion en la conexion'.format(nombre_archivo))
            break   
        if contador == 29:
            print('archivo {} guardado exitosamente'.format(nombre_archivo))
            print('creating png images')
            comando = "./script_control_gnuplot.sh {}".format(nombre_archivo)
            os.system(comando)
            #comando = "./facedetect TEMPLATEh.PNG &"
            #os.system(comando)
            #contador=0
    ser.close()
    texto.close()
else:
    print('No se logro abrir el puerto')

"""La funcion de este programa es crear un archivo nuevo, teniendo como nombres
la fecha actual y hora (de la maquina host), YYYY-MM-DD-hr(s)-min(s)-seg(s).dat
guarda hasta conseguir X datos, esta como el limite en el ciclo while, almacena
series de datos con caracter especial \n al final (este es el delimitante por linea)
Para la conexion del puerto, la realiza teniendo como base el path /dev/ttyAMC{X}
donde X es un numero que va incrementando hasta encontrar un tty disponible
Una vez juntado las muestras esperadas ploteara ambas imagenes

nota: no presenta timeout, tener cuidado con este paremetro, podria dejar colgado el script
en caso de no recibir/interrumpir la informacion serial de manera abrupta """
