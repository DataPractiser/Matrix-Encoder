#ifndef __ARCHIVOCAMBIOLENGUAJE_H_INCLUDED__
#define __ARCHIVOCAMBIOLENGUAJE_H_INCLUDED__

#include "wx/language.h"
#include <fstream>
using std::fstream;
using std::ofstream;
using std::ios;



unsigned char obtenerIdiomaPrograma(char* RutaArchivo);

void guardarIdiomaenUso(char* RutaArchivo, wxLanguage LenguajeSeleccionado);

#endif