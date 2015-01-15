

/*El objetivo es copiar primero los 44 bytes del header y despues  el resto*/
#include <fstream>
#include <string>
#include <iostream>

using namespace std;
 char swap( char d); // funcion de prototipado para intercambiar bits
 					// debido a que esta codificado en little endian


 /* Funcion que tenia como objetivo crear el efecto pasabajas mediante la formula

 			y= n+(n+1)+(n+2)+n+.../ A

	Al final me di cuenta que el problema es que juego con una muy pequeña trama de muestra,
	por lo que al final es impreceptible el efecto, ignore todo uso orientado a objetos
	debido a la falta de conocimientos y experiencia, intentar aplicar estos conceptos causo 
	nos un poco de atraso y sin resultados
 */

int main(int argc, const char * argv[])
{
	unsigned int size;
	char * memblock;
	char bit,bit_in;
	char delay[30];
	unsigned int x=44;
	unsigned int  num;
	float value;
	int resul;

	ifstream base_wav (argv[0], ios::binary | ios::in | ios::ate );
	if (base_wav.is_open()) {

	size = base_wav.tellg(); 		//numero de bytes del archivo
	memblock = new char [size];		//copiar solo 44 bytes-> refrente al header para el posterior
									// tratado de bytes del data
	
	base_wav.seekg(0, ios::beg);
	base_wav.read(memblock, size);	//se pasa todo el wav a la memoria
	base_wav.close();


	ofstream effect_wav ("effect.wav", ios::binary | ios::binary );
	if (effect_wav.is_open()); {
	
	effect_wav.write(memblock, 44); //se escribe el header en el archivo nuevo.wav

	while (x <= size ){			//se pasa byte por byte de la data
	if (x>=44){

	bit = *memblock++;			// apuntador a la memoria wav, que incrementa byte a byte

	//implementacionde la formula
	resul = (int)(delay[12]+delay[10]+delay[8]+delay[6]+delay[4]+delay[2]+delay[0])/5;
	bit_in = (char) (resul & 0xFF)>>2; 

	//se guarda el resultados de la formula
	effect_wav.write(&bit_in, 1);

	delay[16] = delay[15];
	delay[15] = delay[14];
	delay[14] = delay[13];
	delay[13] = delay[12];
	delay[12] = delay[11];
	delay[11] = delay[10];
	delay[10] = delay[9];
	delay[9] = delay[8];
	delay[8] = delay[7];
	delay[7] = delay[6];
	delay[6] = delay[5];
	delay[5] = delay[4];
	delay[4] = delay[3];
	delay[3] = delay[2];
	delay[2] = delay[1];
	delay[1] = delay[0];
	delay[0] = bit;
	x=x+1;
	}

//espacio para retroalimentacion
}




	effect_wav.close();
	}}
	
	
	
	return 0;
}

//Funcion para intercambiar de little endian a big endian los bytes
 char swap( char d)
{
	 char a;
	 
	 a = (d & 0x01) << 7 | (d & 0x02) << 5 | (d & 0x04) << 3 | (d & 0x08) << 1; 
	 a += (d & 0x10) >> 1 | (d & 0x20) >> 3 | (d & 0x40) >> 5 | (d & 0x80) >> 7;
	return a;

}
