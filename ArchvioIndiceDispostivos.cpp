#include "ArchivoIndiceDispostivos.h"
#include <wx/msgdlg.h>

ArchivoDatosDispositivoSalida ArchivoDatosDispositivoSalidaAudio;

ArchivoDatosDispositivoSalida::ArchivoDatosDispositivoSalida()
{
	InicializarFormatoCabezera();
	InicializarDatosPredeterminadosCabecera();

}

void ArchivoDatosDispositivoSalida::InicializarFormatoCabezera()
{
	//Datos de la cabecera predeterminada de los archivos;
	//Esta indica el tipo de archivo Dispositivo Salida DAtos
	Cabecera.Tipo[0] = 'D';
	Cabecera.Tipo[1] = 'S';
	Cabecera.Tipo[2] = 'D';
	Cabecera.Tipo[3] = 'A';
	Cabecera.Tipo[4] = '\0';

	Cabecera.data[0] = 'd';
	Cabecera.data[1] = 'a';
	Cabecera.data[2] = 't';
	Cabecera.data[3] = 'a';
	Cabecera.data[4] = '\0';
}

void ArchivoDatosDispositivoSalida::InicializarDatosPredeterminadosCabecera()
{
	Cabecera.IdDispositivoSalidaAudio = 0;
	Cabecera.NumeroCanalesAudio = 0;
	Cabecera.FrecuenciadeMuestreo = 0;
	Cabecera.ApiDispositivo = 0;
	Cabecera.TamanoNombreDispositivoSalidaAudio = 0;
}


ArchivoDatosDispositivoSalida::~ArchivoDatosDispositivoSalida()
{

}

bool ArchivoDatosDispositivoSalida::LeerArchivoDatosDispositivo(std::string RutaArchivoLectura)
{
	int DesplazamientoArchivo = 0;
	char NombreObtenido[100];
	ifstream ArchivoLectura(RutaArchivoLectura, ios::in | ios::binary);


	if (!ArchivoLectura)
	{
		ArchivoLectura.close();
		return false;
	}
	else
	{
		ArchivoLectura.seekg(DesplazamientoArchivo);
		ArchivoLectura.read(reinterpret_cast<char*>(&Cabecera), sizeof(Cabecera));
		DesplazamientoArchivo = sizeof(Cabecera);

		if (Cabecera.TamanoNombreDispositivoSalidaAudio > 100)
		{
			NombreDispostivoSalidaAudio = "no_audio_device";
			Cabecera.FrecuenciadeMuestreo = 0;
			Cabecera.ApiDispositivo = 0;
			Cabecera.NumeroCanalesAudio = 0;
			Cabecera.IdDispositivoSalidaAudio = 0;
		}
		else
		{
			NombreObtenido[Cabecera.TamanoNombreDispositivoSalidaAudio] = '\0'; //para cerrar la cadena

			ArchivoLectura.seekg(DesplazamientoArchivo);
			ArchivoLectura.read(NombreObtenido, Cabecera.TamanoNombreDispositivoSalidaAudio);
		}

		
		ArchivoLectura.close();

		NombreDispostivoSalidaAudio = NombreObtenido;		

		return true;
	}
}

uint16_t ArchivoDatosDispositivoSalida::obtenerIdDispositivoSalidaAudio()
{
	return Cabecera.IdDispositivoSalidaAudio;
}

uint16_t ArchivoDatosDispositivoSalida::obtenerNumeroCanalesAudio()
{
	return Cabecera.NumeroCanalesAudio;
}

uint32_t ArchivoDatosDispositivoSalida::obtenerFrecuenciadeMuestreo()
{
	return Cabecera.FrecuenciadeMuestreo;
}

uint16_t ArchivoDatosDispositivoSalida::obtenerApiDispositivo()
{
	return Cabecera.ApiDispositivo;
}

std::string ArchivoDatosDispositivoSalida::obtenerNombreDispositivoSalidaAudio()
{
	if (NombreDispostivoSalidaAudio.empty() == true)
	{
		return "no_device";
	}
	else
	{
		return NombreDispostivoSalidaAudio;
	}
	
}

bool ArchivoDatosDispositivoSalida::GuardarDatosDispositivoSalidaAudio(std::string &RutaArchivoGuardado,
	uint16_t IdDispositivo,
	uint16_t NumerodeCanalesdeAudio,
	uint32_t FrecuenciadeMuestreo,
	uint16_t ApiDispositivo,
	std::string & NombreDispositivoAudio)
{
	ofstream ArchivoGuardado;
	int DesplazamientoArchivo = 0;
	
	
	//Se llena la cabecera del archivo con los datos de entrada;
	DireccionAchivoGuardado = RutaArchivoGuardado;

	InicializarFormatoCabezera();

	Cabecera.IdDispositivoSalidaAudio = IdDispositivo;
	Cabecera.NumeroCanalesAudio = NumerodeCanalesdeAudio;
	Cabecera.FrecuenciadeMuestreo = FrecuenciadeMuestreo;
	Cabecera.ApiDispositivo = ApiDispositivo;

	//	delete NombreDispostivoSalidaAudio;

	Cabecera.TamanoNombreDispositivoSalidaAudio = NombreDispositivoAudio.length();


	NombreDispostivoSalidaAudio = NombreDispositivoAudio;

	if (NombreDispostivoSalidaAudio.length() > 100)
	{
		return false;
	}

	ArchivoGuardado.open(DireccionAchivoGuardado, ios::out | ios::binary);


	if (!ArchivoGuardado)
	{
		InicializarDatosPredeterminadosCabecera();
		ArchivoGuardado.close();
		return false;
	}
	else
	{
		//Se colocan los datos 
		ArchivoGuardado.seekp(DesplazamientoArchivo);
		DesplazamientoArchivo += sizeof(Cabecera);
		ArchivoGuardado.write(reinterpret_cast<char*>(&Cabecera), DesplazamientoArchivo);

		//Luego el nombre del dispositivo de audio
		ArchivoGuardado.seekp(DesplazamientoArchivo);
		ArchivoGuardado.write(NombreDispostivoSalidaAudio.c_str(), Cabecera.TamanoNombreDispositivoSalidaAudio);
		ArchivoGuardado.close();

		return true;
	}

}


