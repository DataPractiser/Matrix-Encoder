#include "ArchivoControlVolumen.h"



bool GuardarPerfildeVolumen(PerfilVolumen PerfildeVolumen, char *RutaArchivo)
{
	fstream ArchivoEscritura;


	ArchivoEscritura.open(RutaArchivo, ios::out | ios::binary);

	if (!ArchivoEscritura)
	{
		return false;
	}
	else
	{
		ArchivoEscritura.seekp(0);
		ArchivoEscritura.write(reinterpret_cast<char*>(&PerfildeVolumen), sizeof(PerfildeVolumen));
		ArchivoEscritura.close();
		return true;
	}
}

PerfilVolumen ObtenerPerfilVolumen(char *RutaArchivo)
{
	fstream ArchivoLectura;
	PerfilVolumen PerfilObtenido;

	PerfilObtenido.volumenL = 100;
	PerfilObtenido.volumenR = 100;
	PerfilObtenido.volumenC = 100;
	PerfilObtenido.volumenLFE = 100;
	PerfilObtenido.volumenSL = 100;
	PerfilObtenido.volumenSR = 100;
	PerfilObtenido.volumenRL = 100;
	PerfilObtenido.volumenRR = 100;
	PerfilObtenido.volumenLT = 100;
	PerfilObtenido.volumenRT = 100;
	PerfilObtenido.LowPassFilter = false;
	PerfilObtenido.IncluirLFE = false;
	PerfilObtenido.ModoRangoDinamico = true;

	ArchivoLectura.open(RutaArchivo, ios::in | ios::binary);

	if (!ArchivoLectura)
	{
		return PerfilObtenido;
	}
	else
	{
		ArchivoLectura.seekp(0);
		ArchivoLectura.read(reinterpret_cast<char*>(&PerfilObtenido), sizeof(PerfilVolumen));
		ArchivoLectura.close();

		//para asegurarse que no hay valores alterados se validara que los valores este entre 0 y 100;
		if (PerfilObtenido.volumenL > 100)
		{
			PerfilObtenido.volumenL = 100;
		}

		if (PerfilObtenido.volumenR > 100)
		{
			PerfilObtenido.volumenR = 100;
		}

		if (PerfilObtenido.volumenC > 100)
		{
			PerfilObtenido.volumenC = 100;
		}

		if (PerfilObtenido.volumenLFE > 100)
		{
			PerfilObtenido.volumenLFE = 100;
		}

		if (PerfilObtenido.volumenSL > 100)
		{
			PerfilObtenido.volumenSL = 100;
		}

		if (PerfilObtenido.volumenSR > 100)
		{
			PerfilObtenido.volumenSR = 100;
		}

		if (PerfilObtenido.volumenRL > 100)
		{
			PerfilObtenido.volumenRL = 100;
		}

		if (PerfilObtenido.volumenRR > 100)
		{
			PerfilObtenido.volumenRR = 100;
		}

		if (PerfilObtenido.volumenRT > 100)
		{
			PerfilObtenido.volumenRT = 100;
		}

		if (PerfilObtenido.volumenLT > 100)
		{
			PerfilObtenido.volumenLT = 100;
		}

		return PerfilObtenido;
	}

}
