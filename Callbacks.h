#ifndef __CALLBACKS_H_INCLUDED__
#define __CALLBACKS_H_INCLUDED__


#include "MatrixEncoder.h"
#include "Canales.h"
#include <memory>
#include <portaudio.h>

//variables usadas para balancear el volumen de los respectivos canales
extern float volumenL;
extern float volumenR;
extern float volumenC;
extern float volumenLFE;
extern float volumenSL;
extern float volumenSR;
extern float volumenRL;
extern float volumenRR;

//Este es para las muestras resultantes
extern float volumenLT; 
extern float volumenRT;

//Control de modos de rango dinamico y opciones LFE
extern bool IncluirLFE;
extern bool FiltrarLFE;
extern bool ModoRangoDinamico;

//Procesadores
extern std::shared_ptr<MatrixEncoder> CodificadorMatriz;
extern std::shared_ptr<EightChannels<float>> MuestrasdeAudio;
extern std::shared_ptr<Estereo<float>> Matriz;


int SurroundSeisCanalesFlotante(const void *bufferEntrada,
	void *bufferSalida,
	unsigned long muestrasxBuffer,
	const PaStreamCallbackTimeInfo *informacionTiempo,
	PaStreamCallbackFlags Estado,
	void *datosUsuario);

int SurroundOchoCanalesFlotante(const void * bufferEntrada,
	void * bufferSalida,
	unsigned long muestrasxBuffer,
	const PaStreamCallbackTimeInfo *informacionTiempo,
	PaStreamCallbackFlags Estado,
	void * datosUsuario);

int callbacknulo(const void * bufferEntrada,
	void * bufferSalida,
	unsigned long muestrasxBuffer,
	const PaStreamCallbackTimeInfo *informacionTiempo,
	PaStreamCallbackFlags Estado,
	void * datosUsuario);


#endif


