#ifndef FORMULARIOACERCA_H
#define FORMULARIOACERCA_H

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
#endif*/

#include "xrc\rc\MisXPM\MatrixEncoderIcon_4.xpm"
#include "xrc\rc\MisXPM\wxwidgetlogo.xpm"
#include "xrc\rc\MisXPM\portaudio_logo.xpm"
#include "xrc\rc\MisXPM\the_audacity_team.xpm"

class FormularioAcerca : public wxDialog
{

private:
	wxIcon Icono;
	int TamañoVentanaX = 340;
	int TamañoVentanaY = 480;

	wxPanel* panelFormularioAcerca = nullptr;

	wxBitmapButton* stbWXWidgetLogo = nullptr;
	wxBitmapButton* stbPortAudioLogo = nullptr;
	wxBitmapButton* stbAudacityLogo = nullptr;

	wxFont* fondoVersionPrograma = nullptr;
	wxFont* fondofechaPrograma = nullptr;

	wxStaticText* stVersionPrograma = nullptr;
	wxStaticText* stAgradecimiento = nullptr;
	wxStaticText *stetiquetaAudacity = nullptr;
	wxStaticText* stFecha = nullptr;


	enum
	{
		ID_PANEL_FORMULARIO_ACERCAR,
		ID_STATICBITMAP_WXWIDGETLOGO,
		ID_STATICBITMAP_PORTAUDIOLOGO,
		ID_STATICBITMAP_AUDACITYLOGO,

		ID_STATICTEXT_VERSION_PROGRAMA,
		ID_STATICTEXT_AGRADECIMIENTO,
		ID_STATICTEXT_ETIQUETA_AUDACITY,
		ID_STATICTEXT_FECHA,

		ID_STATIC_TEXT_LINK_PRUEBA,

	};

	wxDECLARE_EVENT_TABLE();

public:
	FormularioAcerca(wxWindow* parent, const wxString& Titulo);
	void abrirLinkaWxWidget(wxCommandEvent& event);
	void abrirLinkaPortAudio(wxCommandEvent& event);
	void abrirLinkaAudacity(wxCommandEvent& event);
	void cerrarVentana(wxCloseEvent& event);
};



#endif
