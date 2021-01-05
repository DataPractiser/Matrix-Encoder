#ifndef INICIALIZACION_H_INCLUDED
#define INICIALIZACION_H_INCLUDED


#include <math.h>
// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
//#include "wx/slider.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../sample.xpm"
#endif

#include "PantallaPrincipal.h"

#include <wx/snglinst.h>
#include "Conexion.h"
#include "RutaArchivo.h"
#include "ArchivoCambioLenguaje.h"

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------
class ConexionCliente : public wxConnection
{
	//Solo se usan estas redefiniciones porque es solo conecatar enviar solicutud y deconectarse
	virtual bool DoExecute(const void *data, size_t size, wxIPCFormat format) wxOVERRIDE;
	//virtual bool OnDisconnect() wxOVERRIDE;
};


class Cliente : public wxClient
{
protected:
	ConexionCliente *m_ConexionCliente;

public:
	Cliente();
	~Cliente();
	bool Conectar(const wxString& sHost, const wxString& sService, const wxString& sTopic);
	void Desconectar();
	bool EstaConectado();
	ConexionCliente *obtenerConexion();
	wxConnectionBase *OnMakeConnection() wxOVERRIDE;
};


// Define a new application type, each program should derive a class from wxApp
class CodificadorMatrizTiempoReal : public wxApp
{
protected:
	wxLanguage Lenguaje; 
	wxLocale Localizacion;
private:
	PantallaPrincipal *Ventana;
	wxSingleInstanceChecker *estadoInstancia;
	Cliente *m_Cliente;
	bool EstadoConexion;
	void ElegirUnIdioma();
public:
	virtual bool OnInit();// wxOVERRIDE;
	PantallaPrincipal *ObtenerPantallaPrincipal();
};

wxIMPLEMENT_APP(CodificadorMatrizTiempoReal);


#endif
