#ifndef FORMULARIOAYUDA_H_INCLUDED
#define FORMULARIOAYUDA_H_INCLUDED

#include "wx/wxprec.h"
//#include "wx/slider.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#include "wx/taskbar.h"
#include "Conexion.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../sample.xpm"
#endif

#include "img\MatrixEncoderIcon_3.xpm"

class textoInstrucciones : public wxTextCtrl
{
private:
	bool CapturadoTexto;

public:
	textoInstrucciones(wxWindow *parent, wxWindowID id, const wxString &value,
		const wxPoint &pos, const wxSize &size, int style = 0)
		: wxTextCtrl(parent, id, value, pos, size, style)
	{
		CapturadoTexto = false;
	}
};


class FormularioAyuda : public wxDialog
{
protected:
	wxLanguage IdiomaenUso;
private:
	wxIcon Icono;
	int TamañoVentanaX = 340;
	int TamañoVentanaY = 520;

	wxPanel* panelFormularioAyuda = nullptr;
	wxStaticBox* ContenedorInstrucciones = nullptr;
	textoInstrucciones* InstruccionesPrograma = nullptr;


	enum
	{
		ID_PANEL_FORMULARIO_AYUDA,
		ID_CONTENEDOR_INSTRUCCION,
		ID_INSTRUCCIONES
	};

public:
	FormularioAyuda(wxWindow* parent, const wxString& Titulo);
	~FormularioAyuda();
};

#endif