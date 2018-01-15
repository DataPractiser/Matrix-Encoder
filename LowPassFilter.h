#ifndef __LOWPASSFILTER_H_INCLUDED
#define __LOWPASSFILTER_H_INCLUDED


#include <math.h>

class LowPassFilter
{
private:
	float Pi = 3.1416f;
	float FrecuenciadeCorte;
	float CoeficientedeResistencia;
	float DominiodeTiempo;
	float Alpha;

	float muestraAnterior[3];
	int CantidadPasadas;


	float MuestraFiltrada;
	int FrecuenciaDeMuestreo;

private:
	void establecerCoefiecienteResistencia();
	void establecerDominiodeTiempo();
	void establecerAlpha();
public:
	void establecerParametrodesFiltrado(float FrecuenciaCorte, int FrecuenciaMuestreo);
	float obtenerMuestraFiltrada(float& MuestraaFiltrar);
	LowPassFilter();
	~LowPassFilter();


};
#endif

