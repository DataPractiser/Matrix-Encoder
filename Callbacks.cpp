#include "Callbacks.h"

//varaibles usadas para balancear el volumen de los respectivos canales
float volumenL = 1.0;
float volumenR = 1.0;
float volumenC = 1.0;
float volumenLFE = 1.0;
float volumenSL = 1.0;
float volumenSR = 1.0;
float volumenRL = 1.0;
float volumenRR = 1.0;

float volumenLT = 1.0; //Este es para las muestras resultantes
float volumenRT = 1.0;

bool IncluirLFE = true;
bool FiltrarLFE = true;
bool ModoRangoDinamico = false; 


std::shared_ptr<MatrixEncoder> CodificadorMatriz(new MatrixEncoder);
std::shared_ptr<EightChannels<float>> MuestrasdeAudio(new EightChannels<float>);
std::shared_ptr<Estereo<float>> Matriz(new Estereo<float>);


int SurroundSeisCanalesFlotante(const void *bufferEntrada, void *bufferSalida, unsigned long muestrasxBuffer, const PaStreamCallbackTimeInfo * informacionTiempo, PaStreamCallbackFlags Estado, void * datosUsuario)
{
	(void)informacionTiempo;
	(void)datosUsuario;
	(void)Estado;
	(void)muestrasxBuffer;


	float *punteroEntrada = (float*)bufferEntrada;
	float *punteroSalida = (float*)bufferSalida;

	

	MuestrasdeAudio->L = (punteroEntrada[0] * volumenL);
	MuestrasdeAudio->R = (punteroEntrada[1] * volumenR);
	MuestrasdeAudio->C = (punteroEntrada[2] * volumenC);
	MuestrasdeAudio->LFE = (punteroEntrada[3] * volumenLFE);
	MuestrasdeAudio->SL = (punteroEntrada[4] * volumenSL);
	MuestrasdeAudio->SR = (punteroEntrada[5] * volumenSR);

	

	CodificadorMatriz->Codificar6Canales(MuestrasdeAudio->L, MuestrasdeAudio->R, MuestrasdeAudio->C, MuestrasdeAudio->LFE, MuestrasdeAudio->SL, MuestrasdeAudio->SR);

	punteroSalida[0] = (CodificadorMatriz->obtenerMuestraTotalL() * volumenLT);
	punteroSalida[1] = (CodificadorMatriz->obtenerMuestraTotalR() * volumenRT);

	return paContinue;
}


int SurroundOchoCanalesFlotante(const void *bufferEntrada, void *bufferSalida, unsigned long muestrasxBuffer, const PaStreamCallbackTimeInfo * informacionTiempo, PaStreamCallbackFlags Estado, void * datosUsuario)
{
	(void)datosUsuario;
	(void)informacionTiempo;
	(void)Estado;
	(void)muestrasxBuffer;

	float *punteroEntrada = (float*)bufferEntrada;
	float *punteroSalida = (float*)bufferSalida;


	MuestrasdeAudio->L = (punteroEntrada[0] * volumenL);
	MuestrasdeAudio->R = (punteroEntrada[1] * volumenR);
	MuestrasdeAudio->C = (punteroEntrada[2] * volumenC);
	MuestrasdeAudio->LFE = (punteroEntrada[3] * volumenLFE);
	MuestrasdeAudio->RL = punteroEntrada[4] * volumenRL;
	MuestrasdeAudio->RR = punteroEntrada[5] * volumenRR;
	MuestrasdeAudio->SL = punteroEntrada[6] * volumenSL;
	MuestrasdeAudio->SR = punteroEntrada[7] * volumenSR;

	CodificadorMatriz->Codificar8Canales(MuestrasdeAudio->L,
		MuestrasdeAudio->R,
		MuestrasdeAudio->C,
		MuestrasdeAudio->LFE,
		MuestrasdeAudio->SL,
		MuestrasdeAudio->SR,
		MuestrasdeAudio->RL,
		MuestrasdeAudio->RR);


	punteroSalida[0] = (CodificadorMatriz->obtenerMuestraTotalL() * volumenLT);
	punteroSalida[1] = (CodificadorMatriz->obtenerMuestraTotalR() * volumenRT);


	return paContinue;
}

int callbacknulo(const void*, void *, unsigned long, const PaStreamCallbackTimeInfo* , PaStreamCallbackFlags, void *)
{
//	Pa_Sleep(500);
	return paContinue;
}


