#include "MatrixEncoder.h"

MatrixEncoder::MatrixEncoder()
{
	ValorReduccion6Canales = valorPredeterminadoReduccionSeisCanales;
	ValorReduccion8Canales = valorPredeterminadoReduccionOchoCanales;
	CanalBajasFrecuenciasIncluido = true; //Pedeterminado.
	CanalBajasFrecuenciasFiltrado = false; //Pedeterminado.
	usarValoresFueradeRango = true;
}


MatrixEncoder::~MatrixEncoder()
{
	punteroBufferRetraso.clear();
}


void MatrixEncoder::eliminarRetrasoEnvolventes()
{
	punteroBufferRetraso.clear();
}

bool MatrixEncoder::inicializarFiltroPaseBajo(int FrecuenciadeMuestreo, float FrecuenciadeCorte)
{
	if (FrecuenciadeMuestreo <= 0)
	{
		return false;
	}
	if (FrecuenciadeCorte <= 0)
	{
		return false;
	}

	FiltroPaseBajo.establecerParametrodesFiltrado(FrecuenciadeCorte, FrecuenciadeMuestreo);
	return true;
}

void MatrixEncoder::IncluirCanalBajasFrecuencias(bool Incluido)
{
	if (Incluido == false)
	{
		CanalBajasFrecuenciasIncluido = Incluido;
		CanalBajasFrecuenciasFiltrado = false;
	}
	else
	{
		CanalBajasFrecuenciasIncluido = Incluido;
	}
}

void MatrixEncoder::FiltrarCanalBajasFrecuencias(bool Filtrado)
{
	CanalBajasFrecuenciasFiltrado = Filtrado;
}


void MatrixEncoder::FijarLimiteValores()
{
	//Se revisa que LT este entre los valores permitidos
	if (MuestraLTtemporal > ValorMaximo)
	{
		MuestraLTtemporal = ValorMaximo;
	}
	if (MuestraLTtemporal < ValorMinimo)
	{
		MuestraLTtemporal = ValorMinimo;
	}

	//Se revisa que RT este entre los valores permitidos
	if (MuestraRTtemporal > ValorMaximo)
	{
		MuestraRTtemporal = ValorMaximo;
	}
	if (MuestraRTtemporal < ValorMinimo)
	{
		MuestraRTtemporal = ValorMinimo;
	}
}

void MatrixEncoder::establecerRetrasoEnvolventes(int FrecuenciadeMuestreo, int RetrasoEnMilisegundos, int CanalesEnRetraso)
{
	//Validaciones
	if (RetrasoEnMilisegundos <= 0)
	{
		RetrasoEnMilisegundos = 1;
	}

	if (CanalesEnRetraso == 2)
	{
		CanalesEnRetraso = 2;
	}
	else if (CanalesEnRetraso == 4)
	{
		CanalesEnRetraso = 4;
	}
	else
	{
		CanalesEnRetraso = 2;
	}


	TamañoBufferRetraso = (((FrecuenciadeMuestreo / 1000) * RetrasoEnMilisegundos) * CanalesEnRetraso);
	
	eliminarRetrasoEnvolventes();

	punteroBufferRetraso.resize(TamañoBufferRetraso);

	IndiceBufferEscritura = 0;
	IndiceBufferLectura = 0;	
}


void MatrixEncoder::reestablecerValoresReduccion()
{
	ValorReduccion6Canales = valorPredeterminadoReduccionSeisCanales;
	ValorReduccion8Canales = valorPredeterminadoReduccionOchoCanales;
}


void MatrixEncoder::establecerValorReduccion6Canales(float& Valor)
{
	ValorReduccion6Canales = Valor;
}

void MatrixEncoder::establecerValorReduccion8Canales(float& Valor)
{
	ValorReduccion8Canales = Valor;
}


void MatrixEncoder::comprimirRangoDinamico()
{
	if (CanalBajasFrecuenciasIncluido == true && CanalBajasFrecuenciasFiltrado == false)
	{
		ValorReduccion6Canales = valor6CanalesLFENoFiltrado;
		ValorReduccion8Canales = valor8CanalesLFENoFiltrado;
	}
	else if (CanalBajasFrecuenciasIncluido == true && CanalBajasFrecuenciasFiltrado == true)
	{
		ValorReduccion6Canales = valor6CanalesLFEFiltrado;
		ValorReduccion8Canales = valor8CanalesLFEFiltrado;
	}
	else if (CanalBajasFrecuenciasIncluido == false && CanalBajasFrecuenciasFiltrado == false)
	{
		ValorReduccion6Canales = valor6CanalesNOLFE;
		ValorReduccion8Canales = valor8CanalesNOLFE;
	}
}

void MatrixEncoder::eliminarReducciondeRangoDinamico()
{
	ValorReduccion6Canales = 1.0;
	ValorReduccion8Canales = 1.0;
}

void MatrixEncoder::eliminarValoresFueradeRango(bool usar)
{
	usarValoresFueradeRango = usar;
}

void MatrixEncoder::Codificar6Canales(float& CanalL, float& CanalR, float& CanalC, float& CanalLFE, float& CanalSL, float& CanalSR)
{
	muestraCanalL = CanalL;
	muestraCanalR = CanalR;
	muestraCanalC = CanalC;
	muestraCanalLFE = CanalLFE;

	MuestraLTtemporal = muestraCanalL + (muestraCanalC * ReduccionMono);
	MuestraRTtemporal = muestraCanalR + (muestraCanalC * ReduccionMono);

	if (CanalBajasFrecuenciasIncluido == true)
	{
		if (CanalBajasFrecuenciasFiltrado == true)
		{
			muestraCanalLFE = FiltroPaseBajo.obtenerMuestraFiltrada(muestraCanalLFE) * ReduccionMono;
		}
		else if (CanalBajasFrecuenciasFiltrado == false)
		{
			muestraCanalLFE = muestraCanalLFE * ReduccionMono;
		}
	}
	else if (CanalBajasFrecuenciasIncluido == false)
	{
		muestraCanalLFE *= 0.0;
	}

	MuestraLTtemporal += muestraCanalLFE;
	MuestraRTtemporal += muestraCanalLFE;

	if (punteroBufferRetraso.empty() == true)//En caso de que no se use el buffer de Retraso
	{
		muestraCanalSL = CanalSL;
		muestraCanalSR = CanalSR;
	}
	else
	{
		if (IndiceBufferEscritura >= TamañoBufferRetraso || IndiceBufferEscritura < 0)
		{
			IndiceBufferEscritura = 0;
		}

		if (IndiceBufferLectura >= TamañoBufferRetraso || IndiceBufferLectura < 0)
		{
			IndiceBufferLectura = 0;
		}

		muestraCanalSL = punteroBufferRetraso[IndiceBufferLectura];
		muestraCanalSR = punteroBufferRetraso[IndiceBufferLectura += 1];
		punteroBufferRetraso[IndiceBufferEscritura] = CanalSL;
		punteroBufferRetraso[IndiceBufferEscritura += 1] = CanalSR;
		IndiceBufferLectura += 1;
		IndiceBufferEscritura += 1;

	}

	MuestraLTtemporal += ((muestraCanalSL * ReduccionSurroundDominante) + (muestraCanalSR * ReduccionSurroundSubDominate));
	MuestraRTtemporal += (((muestraCanalSR * ReduccionSurroundDominante) + (muestraCanalSL * ReduccionSurroundSubDominate)) * -1);

	//Reduccion para tratar de usar todo el rango dinamico posible
	MuestraLTtemporal *= ValorReduccion6Canales;
	MuestraRTtemporal *= ValorReduccion6Canales;


	if (usarValoresFueradeRango == false)
	{
		FijarLimiteValores();
	}

	muestraLT = MuestraLTtemporal;
	muestraRT = MuestraRTtemporal;
}


void MatrixEncoder::Codificar8Canales(float& CanalL, float& CanalR, float& CanalC, float& CanalLFE, float& CanalSL, float& CanalSR, float& CanalRL, float& CanalRR)
{
	muestraCanalL = CanalL;
	muestraCanalR = CanalR;
	muestraCanalC = CanalC;
	muestraCanalLFE = CanalLFE;

	MuestraLTtemporal = muestraCanalL + (muestraCanalC * ReduccionMono);
	MuestraRTtemporal = muestraCanalR + (muestraCanalC * ReduccionMono);

	if (CanalBajasFrecuenciasIncluido == true)
	{
		if (CanalBajasFrecuenciasFiltrado == true)
		{
			muestraCanalLFE = FiltroPaseBajo.obtenerMuestraFiltrada(muestraCanalLFE) * ReduccionMono;
		}
		else
		{
			muestraCanalLFE = muestraCanalLFE * ReduccionMono;
		}
	}
	else if (CanalBajasFrecuenciasIncluido == false)
	{
		muestraCanalLFE *= 0.0;
	}

	MuestraLTtemporal += muestraCanalLFE;
	MuestraRTtemporal += muestraCanalLFE;

	if (punteroBufferRetraso.empty() == true)//En caso de que no se use el buffer de Retraso
	{
		muestraCanalRL = CanalRL;
		muestraCanalRR = CanalRR;
		muestraCanalSL = CanalSL;
		muestraCanalSR = CanalSR;
	}
	else
	{
		if (IndiceBufferEscritura >= TamañoBufferRetraso || IndiceBufferEscritura < 0)
		{
			IndiceBufferEscritura = 0;
		}

		if (IndiceBufferLectura >= TamañoBufferRetraso || IndiceBufferLectura < 0)
		{
			IndiceBufferLectura = 0;
		}

		muestraCanalRL = punteroBufferRetraso[IndiceBufferLectura];
		muestraCanalRR = punteroBufferRetraso[IndiceBufferLectura += 1];
		muestraCanalSL = punteroBufferRetraso[IndiceBufferLectura += 1];
		muestraCanalSR = punteroBufferRetraso[IndiceBufferLectura += 1];

		punteroBufferRetraso[IndiceBufferEscritura] = CanalRL;
		punteroBufferRetraso[IndiceBufferEscritura += 1] = CanalRR;
		punteroBufferRetraso[IndiceBufferEscritura += 1] = CanalSL;
		punteroBufferRetraso[IndiceBufferEscritura += 1] = CanalSR;

		IndiceBufferLectura += 1;
		IndiceBufferEscritura += 1;
	}

	MuestraLTtemporal += ((muestraCanalSL * ReduccionSurroundDominante) +
		(muestraCanalSR * ReduccionSurroundSubDominate) +
		(muestraCanalRL * ReduccionSurroundDominante) +
		(muestraCanalRR * 0.631f));

	MuestraRTtemporal += (((muestraCanalSR * ReduccionSurroundDominante) * -1) +
		((muestraCanalSL * ReduccionSurroundSubDominate) * -1) +
		((muestraCanalRR * ReduccionSurroundDominante) * -1) +
		((muestraCanalRL * 0.631f) * -1));

	//Reduccion para tratar de usar todo el rango dinamico posible
	MuestraLTtemporal *= ValorReduccion8Canales;
	MuestraRTtemporal *= ValorReduccion8Canales;

	if (usarValoresFueradeRango == false)
	{
		FijarLimiteValores();
	}


	muestraLT = MuestraLTtemporal;
	muestraRT = MuestraRTtemporal;
}


float MatrixEncoder::obtenerMuestraTotalL()
{
	return muestraLT;
}

float MatrixEncoder::obtenerMuestraTotalR()
{
	return muestraRT;
}

