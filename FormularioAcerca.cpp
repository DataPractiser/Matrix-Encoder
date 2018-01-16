#include "FormularioAcerca.h"

FormularioAcerca::FormularioAcerca(wxWindow* parent, const wxString & Titulo) : wxDialog(parent, wxID_ANY, Titulo)
{
	this->SetSize(wxSize(TamañoVentanaX, TamañoVentanaY));
	this->SetMinSize(wxSize(TamañoVentanaX, TamañoVentanaY));
	this->SetMaxSize(wxSize(TamañoVentanaX, TamañoVentanaY));
	Icono.CopyFromBitmap(wxBitmap(MatrixEncoderIcon_4));
	this->SetIcon(Icono);

	fondoVersionPrograma = new wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _T("Microsoft Sans Serif"), wxFONTENCODING_DEFAULT);
	fondofechaPrograma = new wxFont(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _T("Microsoft Sans Serif"), wxFONTENCODING_DEFAULT);

	panelFormularioAcerca = new wxPanel(this, ID_PANEL_FORMULARIO_ACERCAR, wxDefaultPosition, wxSize(TamañoVentanaX, TamañoVentanaY), NULL, wxString("ID_PANEL_FORMULARIO_ACERCAR"));
	panelFormularioAcerca->SetBackgroundColour(wxColor(255, 255, 255));

	stVersionPrograma = new wxStaticText(panelFormularioAcerca, ID_STATICTEXT_VERSION_PROGRAMA, "Matrix Encoder v1.0", wxPoint(15, 20), wxDefaultSize, 0, wxString("ID_STATICTEXT_VERSION_PROGRAMA"));
	stVersionPrograma->SetFont(*fondoVersionPrograma);

	stAgradecimiento = new wxStaticText(panelFormularioAcerca, ID_STATICTEXT_AGRADECIMIENTO, _("Este programa fue hecho con: "), wxPoint(30, 50), wxDefaultSize, 0, wxString("ID_STATICTEXT_AGRADECIMIENTO"));

	stbWXWidgetLogo = new wxBitmapButton(panelFormularioAcerca, ID_STATICBITMAP_WXWIDGETLOGO, wxBitmap(wxwidgetlogo), wxPoint(30, 80), wxDefaultSize, 0, wxDefaultValidator, wxString("ID_STATICBITMAP_WXWIDGETLOGO"));
	stbWXWidgetLogo->SetToolTip("www.wxwidget.org");

	stbPortAudioLogo = new wxBitmapButton(panelFormularioAcerca, ID_STATICBITMAP_PORTAUDIOLOGO, wxBitmap(portaudio_logo), wxPoint(30, 170), wxDefaultSize, 0, wxDefaultValidator, wxString("ID_STATICBITMAP_PORTAUDIOLOGO"));
	stbPortAudioLogo->SetToolTip("www.portaudio.com");

	stetiquetaAudacity = new wxStaticText(panelFormularioAcerca, ID_STATICTEXT_ETIQUETA_AUDACITY, _("Con modificaciones del equipo:"), wxPoint(30, 265), wxDefaultSize, 0, wxString("ID_STATICTEXT_ETIQUETA_AUDACITY"));

	stbAudacityLogo = new wxBitmapButton(panelFormularioAcerca, ID_STATICBITMAP_AUDACITYLOGO, wxBitmap(the_audacity_team), wxPoint(30, 280), wxDefaultSize, 0, wxDefaultValidator, wxString("ID_STATICBITMAP_AUDACITYLOGO"));
	stbAudacityLogo->SetToolTip("www.audacityteam.org");

	stFecha = new wxStaticText(panelFormularioAcerca, ID_STATICTEXT_FECHA, "2018", wxPoint(150, 400), wxDefaultSize, wxALIGN_CENTER, wxString("ID_STATICTEXT_FECHA"));

}

void FormularioAcerca::abrirLinkaWxWidget(wxCommandEvent& WXUNUSED(event))
{
	ShellExecute(0, 0, L"http://wxwidgets.org/", 0, 0, SW_SHOW);
}

void FormularioAcerca::abrirLinkaPortAudio(wxCommandEvent& WXUNUSED(event))
{
	ShellExecute(0, 0, L"http://www.portaudio.com/", 0, 0, SW_SHOW);
}

void FormularioAcerca::abrirLinkaAudacity(wxCommandEvent& WXUNUSED(event))
{
	ShellExecute(0, 0, L"http://www.audacityteam.org/", 0, 0, SW_SHOW);
}

void FormularioAcerca::cerrarVentana(wxCloseEvent& WXUNUSED(event))
{
	this->Destroy();
}


wxBEGIN_EVENT_TABLE(FormularioAcerca, wxDialog)
EVT_CLOSE(FormularioAcerca::cerrarVentana)
EVT_BUTTON(ID_STATICBITMAP_WXWIDGETLOGO, FormularioAcerca::abrirLinkaWxWidget)
EVT_BUTTON(ID_STATICBITMAP_PORTAUDIOLOGO, FormularioAcerca::abrirLinkaPortAudio)
EVT_BUTTON(ID_STATICBITMAP_AUDACITYLOGO, FormularioAcerca::abrirLinkaAudacity)
wxEND_EVENT_TABLE()
