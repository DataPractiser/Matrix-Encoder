#include "ArchivoCambioLenguaje.h"

unsigned char obtenerIdiomaPrograma(char * RutaArchivo)
{
	fstream ArchivoLectura;
	short int IdiomaObtenido = wxLANGUAGE_DEFAULT;

	ArchivoLectura.open(RutaArchivo, ios::in | ios::binary);

	if (!ArchivoLectura)
	{
		return wxLANGUAGE_DEFAULT;
	}
	else
	{
		ArchivoLectura.seekp(0);
		ArchivoLectura.read(reinterpret_cast<char*>(&IdiomaObtenido), sizeof(IdiomaObtenido));
		ArchivoLectura.close();

		if (IdiomaObtenido == wxLANGUAGE_ARABIC || IdiomaObtenido == wxLANGUAGE_GERMAN
			|| IdiomaObtenido == wxLANGUAGE_FRENCH || IdiomaObtenido == wxLANGUAGE_ENGLISH
			|| IdiomaObtenido == wxLANGUAGE_SPANISH || IdiomaObtenido == wxLANGUAGE_HINDI
			|| IdiomaObtenido == wxLANGUAGE_PORTUGUESE || IdiomaObtenido == wxLANGUAGE_RUSSIAN
			|| IdiomaObtenido == wxLANGUAGE_CHINESE)
		{
			return IdiomaObtenido;
		}
		else
		{
			return wxLANGUAGE_DEFAULT;
		}
	}
}

void guardarIdiomaenUso(char * RutaArchivo, wxLanguage LenguajeSeleccionado)
{
	fstream ArchivoEscritura;
	short int IdiomaaGuardar = NULL;

	if (LenguajeSeleccionado == wxLANGUAGE_ARABIC || LenguajeSeleccionado == wxLANGUAGE_GERMAN
		|| LenguajeSeleccionado == wxLANGUAGE_FRENCH || LenguajeSeleccionado == wxLANGUAGE_ENGLISH
		|| LenguajeSeleccionado == wxLANGUAGE_SPANISH || LenguajeSeleccionado == wxLANGUAGE_HINDI
		|| LenguajeSeleccionado == wxLANGUAGE_PORTUGUESE || LenguajeSeleccionado == wxLANGUAGE_RUSSIAN
		|| LenguajeSeleccionado == wxLANGUAGE_CHINESE)
	{
		IdiomaaGuardar = LenguajeSeleccionado;
	}
	else
	{
		IdiomaaGuardar = wxLANGUAGE_DEFAULT;
	}


	ArchivoEscritura.open(RutaArchivo, ios::out | ios::binary);

	if (ArchivoEscritura)
	{
		ArchivoEscritura.seekp(0);
		ArchivoEscritura.write(reinterpret_cast<char*>(&IdiomaaGuardar), sizeof(IdiomaaGuardar));
		ArchivoEscritura.close();
	}

}
