#ifndef __ARCHIVOINDICEDISPOSITIVOS_H_INCLUDED__
#define __ARCHIVOINDICEDISPOSITIVOS_H_INCLUDED__


#include <fstream>
#include <string>


using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;

//Esta clase se usa para leer y guardar la informacion de los dipositivos de Salida
//usados durante la ultima ejecucion del programa.
class ArchivoDatosDispositivoSalida
{
private:
	//Estos representan la cabecera del archivo
	//esta cabecera esta basada en portaudio;

	struct CabeceraArchivo
	{
		char Tipo[4]; //= { 'D', 'S', 'D', 'A', '\0' };
		char data[4]; //= { 'd', 'a', 't', 'a', '\0' };
		uint16_t IdDispositivoSalidaAudio;
		uint16_t NumeroCanalesAudio;
		uint32_t FrecuenciadeMuestreo;
		uint16_t ApiDispositivo;
		uint16_t TamanoNombreDispositivoSalidaAudio;
	}Cabecera;

	std::string NombreDispostivoSalidaAudio;
	/////////////////////////////////////
	

	//Estas son de uso interno.
	std::string DireccionAchivoGuardado;
	

public:
	ArchivoDatosDispositivoSalida();
	~ArchivoDatosDispositivoSalida();

	//Estas funciones son para cuando se desea cargar datos desde un archivo existente
	bool LeerArchivoDatosDispositivo(std::string RutaArchivoLectura);
	uint16_t obtenerIdDispositivoSalidaAudio();
	uint16_t obtenerNumeroCanalesAudio();
	uint32_t obtenerFrecuenciadeMuestreo();
	uint16_t obtenerApiDispositivo();
	std::string obtenerNombreDispositivoSalidaAudio();

	//Estas funciones son para cuando se desea Guardar datos en un archivo.
	bool GuardarDatosDispositivoSalidaAudio(std::string &RutaArchivoGuardado, uint16_t IdDispositivo,
		uint16_t NumerodeCanalesdeAudio, uint32_t FrecuenciadeMuestreo,
		uint16_t ApiDispositivo, std::string &NombreDispositivoAudio);


private:
	void InicializarFormatoCabezera();
	void InicializarDatosPredeterminadosCabecera();
};

extern ArchivoDatosDispositivoSalida ArchivoDatosDispositivoSalidaAudio;

#endif


