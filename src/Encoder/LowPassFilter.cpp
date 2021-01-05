#include "LowPassFilter.h"

LowPassFilter::LowPassFilter()
{
	CantidadPasadas = sizeof(muestraAnterior) / sizeof(*muestraAnterior);

	for (int i = 0; i < CantidadPasadas; i++)
	{
		muestraAnterior[i] = 0.0;
	}
}

LowPassFilter::~LowPassFilter()
{
}

void LowPassFilter::establecerCoefiecienteResistencia()
{
	CoeficientedeResistencia = 1.0f / (FrecuenciadeCorte * 2 * Pi);
}

void LowPassFilter::establecerParametrodesFiltrado(float FrecuenciaCorte, int FrecuenciaMuestreo)
{
	if (FrecuenciaCorte <= 0)
	{
		FrecuenciadeCorte = 120.00f;
	}
	else
	{
		FrecuenciadeCorte = FrecuenciaCorte;
	}

	if (FrecuenciaMuestreo <= 0)
	{
		FrecuenciaDeMuestreo = 44100;
	}
	else
	{
		FrecuenciaDeMuestreo = FrecuenciaMuestreo;
	}

	establecerCoefiecienteResistencia();
	establecerDominiodeTiempo();
	establecerAlpha();
}

float LowPassFilter::obtenerMuestraFiltrada(float& MuestraaFiltrar)
{
	muestraAnterior[0] = (muestraAnterior[0] + (Alpha * (MuestraaFiltrar - muestraAnterior[0])));
	muestraAnterior[1] = (muestraAnterior[1] + (Alpha * (muestraAnterior[0] - muestraAnterior[1])));
	muestraAnterior[2] = (muestraAnterior[2] + (Alpha * (muestraAnterior[1] - muestraAnterior[2])));
	muestraAnterior[3] = (muestraAnterior[3] + (Alpha * (muestraAnterior[2] - muestraAnterior[3])));
	muestraAnterior[4] = (muestraAnterior[4] + (Alpha * (muestraAnterior[3] - muestraAnterior[1])));


	return (muestraAnterior[4] * -1);
}

void LowPassFilter::establecerDominiodeTiempo()
{
	DominiodeTiempo = (1.0f / FrecuenciaDeMuestreo);
}

void LowPassFilter::establecerAlpha()
{
	Alpha = DominiodeTiempo / (CoeficientedeResistencia + DominiodeTiempo);
}

