#ifndef __MATRIXENCODER_H_INCLUDED
#define __MATRIXENCODER_H_INCLUDED


#include <iostream>
#include "LowPassFilter.h"
#include <vector>

class MatrixEncoder
{
private:
	//Estas alamaceran las muestras de audio
	//Respectivas a cada canal
	float muestraCanalL;
	float muestraCanalR;
	float muestraCanalC;
	float muestraCanalLFE;
	float muestraCanalSL;
	float muestraCanalSR;
	float muestraCanalRL;
	float muestraCanalRR;

	//Filtro de Pase bajo
	LowPassFilter FiltroPaseBajo;
	bool CanalBajasFrecuenciasIncluido; //Determinar si se incluye este canal en la muestra
	bool CanalBajasFrecuenciasFiltrado; //Determinar si se limita a 120 las frecuencias de este canal

										//Valores de ajuste de volumen
	float valor6CanalesLFENoFiltrado = 0.2643f;
	float valor6CanalesLFEFiltrado = 0.2657f;
	float valor6CanalesNOLFE = 0.3252f;
	float valor8CanalesLFENoFiltrado = 0.245f;
	float valor8CanalesLFEFiltrado = 0.2463f;
	float valor8CanalesNOLFE = 0.3f;

	//Condicional para elimina valores fuera de rango;
	bool usarValoresFueradeRango;

	//En estas variables se usara para hacer la mezcla de forma temporal ya que 
	//se necesitar una tipo de datos con un rango mayor
	float MuestraLTtemporal;
	float MuestraRTtemporal;

	//Esta es para las las versiones 

	//Estos representan la mezcla estero resultado que es compatible 
	//con un codificador de matriz;
	float muestraLT;
	float muestraRT;

	//Este buffer es opcional y se puede usar para agregar un ligero retraso 
	// a los canales envolventes lo que genera que problemas de desvalance de audio
	//sean solventados
	/*float *punteroBufferRetraso = nullptr;*/
	int TamañoBufferRetraso = 0;
	std::vector<float> punteroBufferRetraso;
	int IndiceBufferLectura = 0;
	int IndiceBufferEscritura = 0;

	//Valores de Conversion
	//Estos se usan para generar las mezclas compatibles con un decodificador de matriz;
	float ReduccionMono = 0.707f;
	float ReduccionSurroundDominante = 0.8707f;
	float ReduccionSurroundSubDominate = 0.50f;

	//Valores que se usan para fijar los limites de los tipos de datos a usar;
	float ValorMaximo = 1.0f;
	float ValorMinimo = -1.0f;

	//Esta funcion interna se usara para ver si el valor total esta entre los rangos 
	//maximos o minimos establecidos
	void FijarLimiteValores();


	//Esta variables controla los valores de reduccion de rango dinamico
	float ValorReduccion6Canales = NULL;
	float ValorReduccion8Canales = NULL;

	float valorPredeterminadoReduccionSeisCanales = 0.2643f;
	float valorPredeterminadoReduccionOchoCanales = 0.245f;

	//Estas funciones controlan los valores de reduccion;
	void reestablecerValoresReduccion();


public:
	MatrixEncoder();
	~MatrixEncoder();

	//Funciones que establecen un retraso a los canales surround, util para que no solapen o cancelen los canales
	//frontales
	void establecerRetrasoEnvolventes(int FrecuenciadeMuestreo, int RetrasoEnMilisegundos, int CanalesEnRetraso);
	void eliminarRetrasoEnvolventes();

	//Funciones relacionadas con el filtro de pase bajo
	//Se retorna 0 si la funcion no pudo inicializar el filtro de pase bajo, ya que se pueden pasar valores incorrectos.
	bool inicializarFiltroPaseBajo(int FrecuenciadeMuestreo, float FrecuenciadeCorte);

	void IncluirCanalBajasFrecuencias(bool);
	void FiltrarCanalBajasFrecuencias(bool);

	//Control de Volumen interno.
	//Esta funcion amplica una reduccion de volumen final de la mezcla para elminar valores fuera de rango
	//y usar todo el rango dinamico posible utilizado valores predeterminaods
	void comprimirRangoDinamico();

	//Esta funcion elimina las reducciones y puede hacer que se retorner valores fuerna de rango.
	void eliminarReducciondeRangoDinamico();

	//Esta funcion elimina los valores fuera de rango
	void eliminarValoresFueradeRango(bool);

	//Estas funciones sirven para aplicar valores de reduccion personalizados
	void establecerValorReduccion6Canales(float& Valor);
	void establecerValorReduccion8Canales(float& Valor);

	void Codificar6Canales(float& CanalL, float& CanalR, float& CanalC, float& CanalLFE, float& CanalSL, float& CanalSR);
	void Codificar8Canales(float& CanalL, float& CanalR, float& CanalC, float& CanalLFE, float& CanalSL, float& CanalSR, float& CanalRL, float& CanalRR);

	float obtenerMuestraTotalL();
	float obtenerMuestraTotalR();

};

#endif


