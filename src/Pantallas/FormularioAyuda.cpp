#include "FormularioAyuda.h"

FormularioAyuda::FormularioAyuda(wxWindow* parent, const wxString & Titulo) : wxDialog(parent, wxID_ANY, Titulo)
{

	this->SetSize(wxSize(TamanoVentanaX, TamanoVentanaY));
	this->SetMinSize(wxSize(TamanoVentanaX, TamanoVentanaY));
	this->SetMaxSize(wxSize(TamanoVentanaX, TamanoVentanaY));
	Icono.CopyFromBitmap(wxBitmap(MatrixEncoderIcon_1));
	this->SetIcon(Icono);

	panelFormularioAyuda = new wxPanel(this, ID_PANEL_FORMULARIO_AYUDA, wxDefaultPosition, wxSize(TamanoVentanaX, TamanoVentanaY), NULL, wxString("ID_PANEL_FORMULARIO_AYUDA"));
	panelFormularioAyuda->SetBackgroundColour(wxColor(255, 255, 255));

	ContenedorInstrucciones = new wxStaticBox(panelFormularioAyuda, ID_CONTENEDOR_INSTRUCCION, (_("Uso del programa")), wxPoint(12, 10), wxSize(300, 450), 0, _T("ID_CONTENEDOR_DISPOSITIVO_INSTRUCCION"));
	ContenedorInstrucciones->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	InstruccionesPrograma = new textoInstrucciones(ContenedorInstrucciones, ID_INSTRUCCIONES, _("1) Instale o configure un dispositivo de audio en modo de 5.1 o 7.1 y establezcalo como el predeterminado este puede ser virtual o fisico\n\n") +
		_("2) Configure un segundo dispositivo en modo estereo o 2 canales de salida, este debe ser un dispositivo fisico para que puede escuchar el audio mezclado como HDMI, altavoces, etc.\n\n") +
		_("3) Asegurese que la frecuencia de muestreo de ambos dispositivos sea la misma.\n\n") +
		_("4) Presione el boton refrescar o codificar y escuche el audio en una mezcla compatible con sistemas matriciales de audio.\n") +
		_("\n\n\n") +
		_("Notas: \n") +
		_("*Cambios a la frecuencia de muestreo, numero de canales o profundidad de bits,  puede interrumpir proceso de audio, pero el programa realiza los ajustes necesarios para mantenerlo activo\n\n") +
		_("**Cambiar de un usuario a otro puede interrumpir tambien el flujo de audio.")
		, wxPoint(15, 20), wxSize(270, 410), wxTE_RICH | wxTE_MULTILINE | wxTE_AUTO_URL | wxTE_READONLY | wxNO_BORDER);
	InstruccionesPrograma->SetBackgroundColour(wxColor(255, 255, 255));

}

FormularioAyuda::~FormularioAyuda()
{
}

