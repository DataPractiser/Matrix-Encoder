#ifndef __ARCHIVOCONTROLVOLUMEN_H_INCLUDED__
#define __ARCHIVOCONTROLVOLUMEN_H_INCLUDED__

#include <fstream>
using std::fstream;
using std::ofstream;
using std::ios;

//Este archivo contiene funciones para la lectura de un archivo que contiene las perfiles de volumen que 

//Esta estrucutra se usara para guardar representar un perfil de volumen
struct PerfilVolumen
{
	unsigned char volumenL;
	unsigned char volumenR;
	unsigned char volumenC;
	unsigned char volumenLFE;
	unsigned char volumenSL;
	unsigned char volumenSR;
	unsigned char volumenRL;
	unsigned char volumenRR;
	unsigned char volumenLT;
	unsigned char volumenRT;
	bool IncluirLFE;
	bool LowPassFilter; //Para guardar si se esta usando el Low pass filter.
	bool ModoRangoDinamico; // Para guardar el modo de reduccion de rango dinamico a usar;
};

bool GuardarPerfildeVolumen(PerfilVolumen PerfildeVolumen, char *RutaArchivo);

PerfilVolumen ObtenerPerfilVolumen(char *RutaArchivo);



#endif


