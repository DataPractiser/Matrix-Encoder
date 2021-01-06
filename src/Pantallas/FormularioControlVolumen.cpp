#include "..\Pantallas\FormularioControlVolumen.h"
#include "..\Archivos\ArchivoControlVolumen.h"

//Funciones internas
bool EstadoFormularioControlVolumen = false;

void FormularioControlVolumen::AjusteFormularioporIdioma(wxLanguage IdiomaenUso)
{
	switch (IdiomaenUso)
	{
	case wxLANGUAGE_DEFAULT:
		XajusteporIdioma = 10;
		break;
	case wxLANGUAGE_UNKNOWN:
		XajusteporIdioma = 10;
		break;
	case wxLANGUAGE_ARABIC:
		XajusteporIdioma = 0;
		break;
	case wxLANGUAGE_CHINESE:
		XajusteporIdioma = 0;
		break;
	case wxLANGUAGE_ENGLISH:
		XajusteporIdioma = 15;
		break;
	case wxLANGUAGE_FRENCH:
		XajusteporIdioma = 10;
		break;
	case wxLANGUAGE_GERMAN:
		XajusteporIdioma = 75;
		break;
	case wxLANGUAGE_HINDI:
		XajusteporIdioma = 15;
		break;
	case wxLANGUAGE_PORTUGUESE:
		XajusteporIdioma = 0;
		break;
	case wxLANGUAGE_RUSSIAN:
		XajusteporIdioma = 38;
		break;
	case wxLANGUAGE_SPANISH:
		XajusteporIdioma = 0;
		break;
	default:
		break;
	}
}

FormularioControlVolumen::FormularioControlVolumen(wxWindow *Parent, int NumoeroCanalesaProcesar, wxLanguage IdiomaenUso) : wxDialog(Parent, wxID_ANY, _("Control de Volumen"))
{
	if (NumoeroCanalesaProcesar == 6)
	{
		NumerodeCanalesenProceso = NumoeroCanalesaProcesar;
		valorPosicion = 100;
	}

	LenguajeEnUso = IdiomaenUso;
	AjusteFormularioporIdioma(IdiomaenUso);

	this->SetSize(wxSize(TamanoVentanaX - valorPosicion + XajusteporIdioma, TamanoVentanaY));
	this->SetMinSize(wxSize((TamanoVentanaX - valorPosicion + XajusteporIdioma), TamanoVentanaY));
	this->SetMaxSize(wxSize(TamanoVentanaX - valorPosicion + XajusteporIdioma, TamanoVentanaY));
	
	
	Icono.CopyFromBitmap(wxBitmap(MatrixEncoderIcon_1));
	this->SetIcon(Icono);

	wxFont estiloLetrasCanales(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _T("Microsoft Sans Serif"), wxFONTENCODING_DEFAULT);
	wxFont estiloLetrasValoresSliders(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, _T("Microsoft Sans Serif"), wxFONTENCODING_DEFAULT);

	panelFormularioControlVolumen = new wxPanel(this, ID_PANEL_FORMULARIO_VOLUMEN, wxPoint(0, 0), wxSize(TamanoVentanaX - valorPosicion + XajusteporIdioma, TamanoVentanaY), NULL, wxString("Formulario Control Volumen"));
	panelFormularioControlVolumen->SetBackgroundColour(wxColor(255, 255, 255));

	stPerfilVolumen = new wxStaticText(panelFormularioControlVolumen, ID_STATICTEXT_PERFILESVOLUMEN, _("Perfil de Volumen"), wxPoint(18, 12), wxDefaultSize, NULL, wxString("ID_STATICTEXT_PERFILESVOLUMEN"));
	cbPerfilesVolumen = new wxComboBox(panelFormularioControlVolumen, ID_COMBOBOX_PERFILES_VOLUMEN, wxEmptyString, wxPoint(120, 10), wxSize(150, 50), 0, 0, wxCB_READONLY | wxCB_DROPDOWN, wxDefaultValidator, wxString("ID_COMBOBOX_PERFILES_VOLUMEN"));
	cbPerfilesVolumen->SetBackgroundColour(wxColor(255, 255, 255));
	establecerPerfilesVolumen(NumoeroCanalesaProcesar);

	btnReiniciar = new wxButton(panelFormularioControlVolumen, ID_BUTTON_REINICIAR, _("Reiniciar"), wxPoint(280, 9), wxSize(100, 25), 0, wxDefaultValidator, wxString("ID_BUTTON_REINICIAR"));
	btnReiniciar->SetFont(estiloLetrasValoresSliders);
	btnReiniciar->SetBackgroundColour(wxColor(255, 255, 255));

	stbContenedorVolumenEntrada = new wxStaticBox(panelFormularioControlVolumen, ID_STATICBOX_CONTENEDOR_VOLUMEN_ENTRADA, _("Volumen Canales de Entrada"), wxPoint(12, 40), wxSize(410 - valorPosicion, 178), 0, wxString("ID_STATICBOX_CONTENEDOR_VOLUMEN_ENTRADA"));
	stbContenedorVolumenEntrada->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	LL = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_LL, "L", wxPoint(18, 25), wxDefaultSize, NULL, wxString("ID_STATICTEXT_LL"));
	LL->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LL->SetFont(estiloLetrasCanales);

	LR = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_LR, "R", wxPoint(68, 25), wxDefaultSize, NULL, wxString("ID_STATICTEXT_LR"));
	LR->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LR->SetFont(estiloLetrasCanales);

	LC = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_LR, "C", wxPoint(118, 25), wxDefaultSize, NULL, wxString("ID_STATICTEXT_LC"));
	LC->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LC->SetFont(estiloLetrasCanales);

	LLFE = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_LLFE, "LFE", wxPoint(168, 25), wxDefaultSize, NULL, wxString("ID_STATICTEXT_LLFE"));
	LLFE->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LLFE->SetFont(estiloLetrasCanales);

	LSL = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_LSL, "SL", wxPoint(218, 25), wxDefaultSize, NULL, wxString("ID_STATICTEXT_LSL"));
	LSL->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LSL->SetFont(estiloLetrasCanales);

	LSR = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_LSR, "SR", wxPoint(268, 25), wxDefaultSize, NULL, wxString("ID_STATICTEXT_LSR"));
	LSR->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LSR->SetFont(estiloLetrasCanales);

	LRL = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_LRL, "RL", wxPoint(318, 25), wxDefaultSize, NULL, wxString("ID_STATICTEXT_LRL"));
	LRL->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LRL->SetFont(estiloLetrasCanales);

	LRR = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_LRR, "RR", wxPoint(368, 25), wxDefaultSize, NULL, wxString("ID_STATICTEXT_LRR"));
	LRR->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LRR->SetFont(estiloLetrasCanales);

	//Sliders

	tbVolumenCanalL = new wxSlider(stbContenedorVolumenEntrada, ID_SLIDER_TB_VOLUMEN_CANAL_L, 100, 0, 100, wxPoint(15, 45), wxSize(40, 106), wxSL_INVERSE | wxSL_VERTICAL | wxSL_AUTOTICKS, wxDefaultValidator, wxString("ID_SLIDER_TB_VOLUMEN_CANAL_L"));
	tbVolumenCanalR = new wxSlider(stbContenedorVolumenEntrada, ID_SLIDER_TB_VOLUMEN_CANAL_R, 100, 0, 100, wxPoint(65, 45), wxSize(40, 106), wxSL_INVERSE | wxSL_VERTICAL | wxSL_AUTOTICKS, wxDefaultValidator, wxString("ID_SLIDER_TB_VOLUMEN_CANAL_R"));
	tbVolumenCanalC = new wxSlider(stbContenedorVolumenEntrada, ID_SLIDER_TB_VOLUMEN_CANAL_C, 100, 0, 100, wxPoint(115, 45), wxSize(40, 106), wxSL_INVERSE | wxSL_VERTICAL | wxSL_AUTOTICKS, wxDefaultValidator, wxString("ID_SLIDER_TB_VOLUMEN_CANAL_C"));
	tbVolumenCanalLFE = new wxSlider(stbContenedorVolumenEntrada, ID_SLIDER_TB_VOLUMEN_CANAL_LFE, 100, 0, 100, wxPoint(165, 45), wxSize(40, 106), wxSL_INVERSE | wxSL_VERTICAL | wxSL_AUTOTICKS, wxDefaultValidator, wxString("ID_SLIDER_TB_VOLUMEN_CANAL_LFE"));
	tbVolumenCanalSL = new wxSlider(stbContenedorVolumenEntrada, ID_SLIDER_TB_VOLUMEN_CANAL_SL, 100, 0, 100, wxPoint(215, 45), wxSize(40, 106), wxSL_INVERSE | wxSL_VERTICAL | wxSL_AUTOTICKS, wxDefaultValidator, wxString("ID_SLIDER_TB_VOLUMEN_CANAL_SL"));
	tbVolumenCanalSR = new wxSlider(stbContenedorVolumenEntrada, ID_SLIDER_TB_VOLUMEN_CANAL_SR, 100, 0, 100, wxPoint(265, 45), wxSize(40, 106), wxSL_INVERSE | wxSL_VERTICAL | wxSL_AUTOTICKS, wxDefaultValidator, wxString("ID_SLIDER_TB_VOLUMEN_CANAL_SR"));
	tbVolumenCanalRL = new wxSlider(stbContenedorVolumenEntrada, ID_SLIDER_TB_VOLUMEN_CANAL_RL, 100, 0, 100, wxPoint(315, 45), wxSize(40, 106), wxSL_INVERSE | wxSL_VERTICAL | wxSL_AUTOTICKS, wxDefaultValidator, wxString("ID_SLIDER_TB_VOLUMEN_CANAL_RL"));
	tbVolumenCanalRR = new wxSlider(stbContenedorVolumenEntrada, ID_SLIDER_TB_VOLUMEN_CANAL_RR, 100, 0, 100, wxPoint(365, 45), wxSize(40, 106), wxSL_INVERSE | wxSL_VERTICAL | wxSL_AUTOTICKS, wxDefaultValidator, wxString("ID_SLIDER_TB_VOLUMEN_CANAL_RR"));

	//texto Valores  sliders
	NivelL = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_NIVELL, "100%", wxPoint(15, 150), wxDefaultSize, NULL, wxString("ID_STATICTEXT_NIVELL"));
	NivelL->SetFont(estiloLetrasValoresSliders);
	NivelL->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	NivelR = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_NIVELR, "100%", wxPoint(65, 150), wxDefaultSize, NULL, wxString("ID_STATICTEXT_NIVELR"));
	NivelR->SetFont(estiloLetrasValoresSliders);
	NivelR->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	NivelC = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_NIVELC, "100%", wxPoint(115, 150), wxDefaultSize, NULL, wxString("ID_STATICTEXT_NIVELC"));
	NivelC->SetFont(estiloLetrasValoresSliders);
	NivelC->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	NivelLFE = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_NIVELLFE, "100%", wxPoint(165, 150), wxDefaultSize, NULL, wxString("ID_STATICTEXT_NIVELFE"));
	NivelLFE->SetFont(estiloLetrasValoresSliders);
	NivelLFE->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	NivelSL = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_NIVELSL, "100%", wxPoint(215, 150), wxDefaultSize, NULL, wxString("ID_STATICTEXT_NIVELSL"));
	NivelSL->SetFont(estiloLetrasValoresSliders);
	NivelSL->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	NivelSR = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_NIVELSR, "100%", wxPoint(265, 150), wxDefaultSize, NULL, wxString("ID_STATICTEXT_NIVELSR"));
	NivelSR->SetFont(estiloLetrasValoresSliders);
	NivelSR->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	NivelRL = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_NIVELRL, "100%", wxPoint(315, 150), wxDefaultSize, NULL, wxString("ID_STATICTEXT_NIVELRL"));
	NivelRL->SetFont(estiloLetrasValoresSliders);
	NivelRL->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	NivelRR = new wxStaticText(stbContenedorVolumenEntrada, ID_STATICTEXT_NIVELRR, "100%", wxPoint(365, 150), wxDefaultSize, NULL, wxString("ID_STATICTEXT_NIVELRR"));
	NivelRR->SetFont(estiloLetrasValoresSliders);
	NivelRR->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	stbContenedorVolumenSalida = new wxStaticBox(panelFormularioControlVolumen, ID_STATICBOX_CONTENEDOR_VOLUMEN_SALIDA, _("Volumen de Salida"), wxPoint(430 - valorPosicion, 40), wxSize(125, 178), 0, wxString("ID_STATICBOX_CONTENEDOR_VOLUMEN_SALIDA"));
	stbContenedorVolumenSalida->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	LLT = new wxStaticText(stbContenedorVolumenSalida, ID_STATICTEXT_LRL, "L", wxPoint(15, 25), wxDefaultSize, NULL, wxString("ID_STATICTEXT_LLT"));
	LLT->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LLT->SetFont(estiloLetrasCanales);

	LRT = new wxStaticText(stbContenedorVolumenSalida, ID_STATICTEXT_LRR, "R", wxPoint(65, 25), wxDefaultSize, NULL, wxString("ID_STATICTEXT_LRT"));
	LRT->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LRT->SetFont(estiloLetrasCanales);

	tbVolumenLT = new wxSlider(stbContenedorVolumenSalida, ID_SLIDER_TB_VOLUMEN_CANAL_LT, 100, 0, 100, wxPoint(10, 45), wxSize(40, 106), wxSL_INVERSE | wxSL_VERTICAL | wxSL_AUTOTICKS, wxDefaultValidator, wxString("ID_SLIDER_TB_VOLUMEN_CANAL_LT"));
	tbVolumenRT = new wxSlider(stbContenedorVolumenSalida, ID_SLIDER_TB_VOLUMEN_CANAL_RT, 100, 0, 100, wxPoint(60, 45), wxSize(40, 106), wxSL_INVERSE | wxSL_VERTICAL | wxSL_AUTOTICKS, wxDefaultValidator, wxString("ID_SLIDER_TB_VOLUMEN_CANAL_RT"));

	NivelLT = new wxStaticText(stbContenedorVolumenSalida, ID_STATICTEXT_NIVELLT, "100%", wxPoint(15, 150), wxDefaultSize, NULL, wxString("ID_STATICTEXT_NIVELLT"));
	NivelLT->SetFont(estiloLetrasValoresSliders);
	NivelLT->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	NivelRT = new wxStaticText(stbContenedorVolumenSalida, ID_STATICTEXT_NIVELR, "100%", wxPoint(65, 150), wxDefaultSize, NULL, wxString("ID_STATICTEXT_NIVELRT"));
	NivelRT->SetFont(estiloLetrasValoresSliders);
	NivelRT->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));

	stbContenedorOpcionesLFE = new wxStaticBox(panelFormularioControlVolumen, ID_STATICBOX_CONTENEDOR_OPCIONES_LFE, _("Opciones LFE"), wxPoint(562 - valorPosicion, 40), wxSize(120 + XajusteporIdioma, 85), 0, wxString("ID_STATICBOX_CONTENEDOR_VOLUMEN_SALIDA"));
	stbContenedorOpcionesLFE->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
																												   //565 - valorPosicion, 65																			
	cbIncluirLFE = new wxCheckBox(stbContenedorOpcionesLFE, ID_CHECKBUTTON_INCLUIR_LFE, _("Incluir canal LFE"), wxPoint(2, 25), wxDefaultSize, wxALIGN_RIGHT, wxDefaultValidator, wxString("ID_CHECKBUTTON_INCLUIR_LFE"));
	cbIncluirLFE->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	cbIncluirLFE->SetFont(estiloLetrasValoresSliders);
	cbIncluirLFE->SetToolTip(_("Marque para incluir el canal de bajas frecuencias en la mezcla estereo"));

	cbFiltrarLFE = new wxCheckBox(stbContenedorOpcionesLFE, ID_CHECKBUTTON_FILTRAR_LFE, _("Filtrar canal LFE"), wxPoint(5, 50), wxDefaultSize, wxALIGN_RIGHT, wxDefaultValidator, wxString("ID_CHECKBUTTON_FILTRAR_LFE"));
	cbFiltrarLFE->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	cbFiltrarLFE->SetFont(estiloLetrasValoresSliders);
	cbFiltrarLFE->SetToolTip(_("Marque para aplicar un filtro de pase bajo de 120hz a este canal y eliminar frecuencias que no corresponden a este canal. Advertencia: activar esto puede causar un aumento en el uso del CPU"));

	stbContenedorModoRangoDinamico = new wxStaticBox(panelFormularioControlVolumen, ID_STATICBOX_CONTENEDOR_OPCIONES_RANGO, _("Rango Dinamico"), wxPoint(562 - valorPosicion, 130), wxSize(120, 70), 0, wxString("ID_STATICBOX_CONTENEDOR_OPCIONES_RANGO"));
	stbContenedorModoRangoDinamico->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	stbContenedorModoRangoDinamico->SetFont(estiloLetrasValoresSliders);
	                                                                                                              //578 - valorPosicion, 150
	rbModoJuego = new wxRadioButton(stbContenedorModoRangoDinamico, ID_RADIOBUTTON_MODOJUEGO, _("Modo Juego"), wxPoint(10, 20), wxDefaultSize, 0, wxDefaultValidator, wxString("ID_RADIOBUTTON_MODOJUEGO"));
	rbModoJuego->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	rbModoJuego->SetFont(estiloLetrasValoresSliders);
	rbModoJuego->SetToolTip(_("Marque para usar todo el rango dinamico disponible. Los juegos usualmente poseen un rango dinamico o volumen muy alto, esto ayuda a usar todo el rango de un mezcla estero"));

	rbModoPelicula = new wxRadioButton(stbContenedorModoRangoDinamico, ID_RADIOBUTTON_MODOPELICULA, _("Modo Pelicula"), wxPoint(10, 45), wxDefaultSize, 0, wxDefaultValidator, wxString("ID_RADIOBUTTON_MODOPELICULA"));
	rbModoPelicula->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	rbModoPelicula->SetFont(estiloLetrasValoresSliders);
	rbModoPelicula->SetToolTip(_("Marque para no utilizar la compresion del rango dinamico. Usualmente las peliculas o videos tienen un rango dinamico o volumen menor a los juegos. Use esto modo cuando considere que el volumen de lo que esta reproduciendo es muy bajo"));

	if (valorPosicion == 100)
	{
		tbVolumenCanalRL->Hide();
		tbVolumenCanalRR->Hide();
		NivelRL->Hide();
		NivelRR->Hide();
		LRL->Hide();
		LRR->Hide();
	}

	InicializarNivelesVolumen();
	EstadoFormularioControlVolumen = true;
}


void FormularioControlVolumen::ReiniciarControlesVolumen()
{
	cbPerfilesVolumen->SetSelection(wxNOT_FOUND);
	tbVolumenCanalL->SetValue(100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalL->GetValue());
	NivelL->SetLabel(cadenaValorSliders + "%");
	volumenL = 1.0;

	tbVolumenCanalR->SetValue(100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalR->GetValue());
	NivelR->SetLabel(cadenaValorSliders + "%");
	volumenR = 1.0;

	tbVolumenCanalC->SetValue(100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalC->GetValue());
	NivelC->SetLabel(cadenaValorSliders + "%");
	volumenC = 1.0;

	tbVolumenCanalLFE->SetValue(100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalLFE->GetValue());
	NivelLFE->SetLabel(cadenaValorSliders + "%");
	volumenLFE = 1.0;

	tbVolumenCanalSL->SetValue(100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalSL->GetValue());
	NivelSL->SetLabel(cadenaValorSliders + "%");
	volumenSL = 1.0;

	tbVolumenCanalSR->SetValue(100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalSR->GetValue());
	NivelSR->SetLabel(cadenaValorSliders + "%");
	volumenSR = 1.0;

	tbVolumenCanalRL->SetValue(100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalRL->GetValue());
	NivelRL->SetLabel(cadenaValorSliders + "%");
	volumenRL = 1.0;

	tbVolumenCanalRR->SetValue(100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalRR->GetValue());
	NivelRR->SetLabel(cadenaValorSliders + "%");
	volumenRR = 1.0;

	tbVolumenLT->SetValue(100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenLT->GetValue());
	NivelLT->SetLabel(cadenaValorSliders + "%");
	volumenLT = 1.0;

	tbVolumenRT->SetValue(100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenRT->GetValue());
	NivelRT->SetLabel(cadenaValorSliders + "%");
	volumenRT = 1.0;
}

void FormularioControlVolumen::elegirPerfilVolumen()
{
	/* 0 Personalizado*/
	if (cbPerfilesVolumen->GetSelection() == 0)
	{
		InicializarNivelesVolumen();
	}
	//1 Solo L
	if (cbPerfilesVolumen->GetValue() == _("Solo L"))
	{
		tbVolumenCanalL->SetValue(100);
		volumenL = 1.0;
		NivelL->SetLabel("100%");

		tbVolumenCanalR->SetValue(0);
		volumenR = 0.0;
		NivelR->SetLabel("0%");

		tbVolumenCanalC->SetValue(0);
		volumenC = 0.0;
		NivelC->SetLabel("0%");

		tbVolumenCanalLFE->SetValue(0);
		volumenLFE = 0.0;
		NivelLFE->SetLabel("0%");

		tbVolumenCanalSL->SetValue(0);
		volumenSL = 0.0;
		NivelSL->SetLabel("0%");

		tbVolumenCanalSR->SetValue(0);
		volumenSR = 0.0;
		NivelSR->SetLabel("0%");

		tbVolumenCanalRL->SetValue(0);
		volumenRL = 0.0;
		NivelRL->SetLabel("0%");

		tbVolumenCanalRR->SetValue(0);
		volumenRR = 0.0;
		NivelRR->SetLabel("0%");
	}
	//2 Solo R
	else if (cbPerfilesVolumen->GetValue() == _("Solo R"))
	{
		tbVolumenCanalL->SetValue(0);
		volumenL = 0.0;
		NivelL->SetLabel("0%");

		tbVolumenCanalR->SetValue(100);
		volumenR = 1.0;
		NivelR->SetLabel("100%");

		tbVolumenCanalC->SetValue(0);
		volumenC = 0.0;
		NivelC->SetLabel("0%");

		tbVolumenCanalLFE->SetValue(0);
		volumenLFE = 0.0;
		NivelLFE->SetLabel("0%");

		tbVolumenCanalSL->SetValue(0);
		volumenSL = 0.0;
		NivelSL->SetLabel("0%");

		tbVolumenCanalSR->SetValue(0);
		volumenSR = 0.0;
		NivelSR->SetLabel("0%");

		tbVolumenCanalRL->SetValue(0);
		volumenRL = 0.0;
		NivelRL->SetLabel("0%");

		tbVolumenCanalRR->SetValue(0);
		volumenRR = 0.0;
		NivelRR->SetLabel("0%");
	}
	//3 Solo C
	else if (cbPerfilesVolumen->GetValue() == _("Solo C"))
	{
		tbVolumenCanalL->SetValue(0);
		volumenL = 0.0;
		NivelL->SetLabel("0%");

		tbVolumenCanalR->SetValue(0);
		volumenR = 0.0;
		NivelR->SetLabel("0%");

		tbVolumenCanalC->SetValue(100);
		volumenC = 1.0;
		NivelC->SetLabel("100%");

		tbVolumenCanalLFE->SetValue(0);
		volumenLFE = 0.0;
		NivelLFE->SetLabel("0%");

		tbVolumenCanalSL->SetValue(0);
		volumenSL = 0.0;
		NivelSL->SetLabel("0%");

		tbVolumenCanalSR->SetValue(0);
		volumenSR = 0.0;
		NivelSR->SetLabel("0%");

		tbVolumenCanalRL->SetValue(0);
		volumenRL = 0.0;
		NivelRL->SetLabel("0%");

		tbVolumenCanalRR->SetValue(0);
		volumenRR = 0.0;
		NivelRR->SetLabel("0%");
	}
	//4 Solo LFE

	else if (cbPerfilesVolumen->GetValue() == _("Solo LFE"))
	{
		tbVolumenCanalL->SetValue(0);
		volumenL = 0.0;
		NivelL->SetLabel("0%");

		tbVolumenCanalR->SetValue(0);
		volumenR = 0.0;
		NivelR->SetLabel("0%");

		tbVolumenCanalC->SetValue(0);
		volumenC = 0.0;
		NivelC->SetLabel("0%");

		tbVolumenCanalLFE->SetValue(100);
		volumenLFE = 1.0;
		NivelLFE->SetLabel("100%");

		tbVolumenCanalSL->SetValue(0);
		volumenSL = 0.0;
		NivelSL->SetLabel("0%");

		tbVolumenCanalSR->SetValue(0);
		volumenSR = 0.0;
		NivelSR->SetLabel("0%");

		tbVolumenCanalRL->SetValue(0);
		volumenRL = 0.0;
		NivelRL->SetLabel("0%");

		tbVolumenCanalRR->SetValue(0);
		volumenRR = 0.0;
		NivelRR->SetLabel("0%");
	}
	//5 Solo SL

	else if (cbPerfilesVolumen->GetValue() == _("Solo SL"))
	{
		tbVolumenCanalL->SetValue(0);
		volumenL = 0.0;
		NivelL->SetLabel("0%");

		tbVolumenCanalR->SetValue(0);
		volumenR = 0.0;
		NivelR->SetLabel("0%");

		tbVolumenCanalC->SetValue(0);
		volumenC = 0.0;
		NivelC->SetLabel("0%");

		tbVolumenCanalLFE->SetValue(0);
		volumenLFE = 0.0;
		NivelLFE->SetLabel("0%");

		tbVolumenCanalSL->SetValue(100);
		volumenSL = 1.0;
		NivelSL->SetLabel("100%");

		tbVolumenCanalSR->SetValue(0);
		volumenSR = 0.0;
		NivelSR->SetLabel("0%");

		tbVolumenCanalRL->SetValue(0);
		volumenRL = 0.0;
		NivelRL->SetLabel("0%");

		tbVolumenCanalRR->SetValue(0);
		volumenRR = 0.0;
		NivelRR->SetLabel("0%");
	}
	//6 Solo SR

	else if (cbPerfilesVolumen->GetValue() == _("Solo SR"))
	{
		tbVolumenCanalL->SetValue(0);
		volumenL = 0.0;
		NivelL->SetLabel("0%");

		tbVolumenCanalR->SetValue(0);
		volumenR = 0.0;
		NivelR->SetLabel("0%");

		tbVolumenCanalC->SetValue(0);
		volumenC = 0.0;
		NivelC->SetLabel("0%");

		tbVolumenCanalLFE->SetValue(0);
		volumenLFE = 0.0;
		NivelLFE->SetLabel("0%");

		tbVolumenCanalSL->SetValue(0);
		volumenSL = 0.0;
		NivelSL->SetLabel("0%");

		tbVolumenCanalSR->SetValue(100);
		volumenSR = 1.0;
		NivelSR->SetLabel("100%");

		tbVolumenCanalRL->SetValue(0);
		volumenRL = 0.0;
		NivelRL->SetLabel("0%");

		tbVolumenCanalRR->SetValue(0);
		volumenRR = 0.0;
		NivelRR->SetLabel("0%");
	}
	//7 Solo RL
	else if (cbPerfilesVolumen->GetValue() == _("Solo RL"))
	{
		tbVolumenCanalL->SetValue(0);
		volumenL = 0.0;
		NivelL->SetLabel("0%");

		tbVolumenCanalR->SetValue(0);
		volumenR = 0.0;
		NivelR->SetLabel("0%");

		tbVolumenCanalC->SetValue(0);
		volumenC = 0.0;
		NivelC->SetLabel("0%");

		tbVolumenCanalLFE->SetValue(0);
		volumenLFE = 0.0;
		NivelLFE->SetLabel("0%");

		tbVolumenCanalSL->SetValue(0);
		volumenSL = 0.0;
		NivelSL->SetLabel("0%");

		tbVolumenCanalSR->SetValue(0);
		volumenSR = 0.0;
		NivelSR->SetLabel("0%");

		tbVolumenCanalRL->SetValue(100);
		volumenRL = 1.0;
		NivelRL->SetLabel("100%");

		tbVolumenCanalRR->SetValue(0);
		volumenRR = 0.0;
		NivelRR->SetLabel("0%");
	}
	//8 Solo RR
	else if (cbPerfilesVolumen->GetValue() == _("Solo RR"))
	{
		tbVolumenCanalL->SetValue(0);
		volumenL = 0.0;
		NivelL->SetLabel("0%");

		tbVolumenCanalR->SetValue(0);
		volumenR = 0.0;
		NivelR->SetLabel("0%");

		tbVolumenCanalC->SetValue(0);
		volumenC = 0.0;
		NivelC->SetLabel("0%");

		tbVolumenCanalLFE->SetValue(0);
		volumenLFE = 0.0;
		NivelLFE->SetLabel("0%");

		tbVolumenCanalSL->SetValue(0);
		volumenSL = 0.0;
		NivelSL->SetLabel("0%");

		tbVolumenCanalSR->SetValue(0);
		volumenSR = 0.0;
		NivelSR->SetLabel("0%");

		tbVolumenCanalRL->SetValue(0);
		volumenRL = 0.0;
		NivelRL->SetLabel("0%");

		tbVolumenCanalRR->SetValue(100);
		volumenRR = 1.0;
		NivelRR->SetLabel("100%");
	}

	//9 Solo L y R
	else if (cbPerfilesVolumen->GetValue() == _("Solo L y R"))
	{
		tbVolumenCanalL->SetValue(100);
		volumenL = 1.0;
		NivelL->SetLabel("100%");

		tbVolumenCanalR->SetValue(100);
		volumenR = 1.0;
		NivelR->SetLabel("100%");

		tbVolumenCanalC->SetValue(0);
		volumenC = 0.0;
		NivelC->SetLabel("0%");

		tbVolumenCanalLFE->SetValue(0);
		volumenLFE = 0.0;
		NivelLFE->SetLabel("0%");

		tbVolumenCanalSL->SetValue(0);
		volumenSL = 0.0;
		NivelSL->SetLabel("0%");

		tbVolumenCanalSR->SetValue(0);
		volumenSR = 0.0;
		NivelSR->SetLabel("0%");

		tbVolumenCanalRL->SetValue(0);
		volumenRL = 0.0;
		NivelRL->SetLabel("0%");

		tbVolumenCanalRR->SetValue(0);
		volumenRR = 0.0;
		NivelRR->SetLabel("0%");
	}
	//10 Solo SL y SR
	else if (cbPerfilesVolumen->GetValue() == _("Solo SL y SR"))
	{
		tbVolumenCanalL->SetValue(0);
		volumenL = 0.0;
		NivelL->SetLabel("0%");

		tbVolumenCanalR->SetValue(0);
		volumenR = 0.0;
		NivelR->SetLabel("0%");

		tbVolumenCanalC->SetValue(0);
		volumenC = 0.0;
		NivelC->SetLabel("0%");

		tbVolumenCanalLFE->SetValue(0);
		volumenLFE = 0.0;
		NivelLFE->SetLabel("0%");

		tbVolumenCanalSL->SetValue(100);
		volumenSL = 1.0;
		NivelSL->SetLabel("100%");

		tbVolumenCanalSR->SetValue(100);
		volumenSR = 1.0;
		NivelSR->SetLabel("100%");

		tbVolumenCanalRL->SetValue(0);
		volumenRL = 0.0;
		NivelRL->SetLabel("0%");

		tbVolumenCanalRR->SetValue(0);
		volumenRR = 0.0;
		NivelRR->SetLabel("0%");
	}
	//11 Solo RL y RR
	else if (cbPerfilesVolumen->GetValue() == _("Solo RL y RR"))
	{
		tbVolumenCanalL->SetValue(0);
		volumenL = 0.0;
		NivelL->SetLabel("0%");

		tbVolumenCanalR->SetValue(0);
		volumenR = 0.0;
		NivelR->SetLabel("0%");

		tbVolumenCanalC->SetValue(0);
		volumenC = 0.0;
		NivelC->SetLabel("0%");

		tbVolumenCanalLFE->SetValue(0);
		volumenLFE = 0.0;
		NivelLFE->SetLabel("0%");

		tbVolumenCanalSL->SetValue(0);
		volumenSL = 0.0;
		NivelSL->SetLabel("0%");

		tbVolumenCanalSR->SetValue(0);
		volumenSR = 0.0;
		NivelSR->SetLabel("0%");

		tbVolumenCanalRL->SetValue(100);
		volumenRL = 1.0;
		NivelRL->SetLabel("100%");

		tbVolumenCanalRR->SetValue(100);
		volumenRR = 1.0;
		NivelRR->SetLabel("100%");

	}
}

void FormularioControlVolumen::LeerPerfilVolumen()
{
	PerfilVolumen PerfilObtenido = {NULL,NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	RutaArchivoVolumen = getenv(Enviro.c_str()) + finalRuta + ArchivoVolumen;


	PerfilObtenido = ObtenerPerfilVolumen((char*)RutaArchivoVolumen.c_str());


	volumenL = PerfilObtenido.volumenL / 100.00;
	volumenR = PerfilObtenido.volumenR / 100.00;
	volumenC = PerfilObtenido.volumenC / 100.00;
	volumenLFE = PerfilObtenido.volumenLFE / 100.00;
	volumenSL = PerfilObtenido.volumenSL / 100.00;
	volumenSR = PerfilObtenido.volumenSR / 100.00;
	volumenRL = PerfilObtenido.volumenRL / 100.00;
	volumenRR = PerfilObtenido.volumenRR / 100.00;
	volumenLT = PerfilObtenido.volumenLT / 100.00;
	volumenRT = PerfilObtenido.volumenRT / 100.00;

	IncluirLFE = PerfilObtenido.IncluirLFE;

	cbIncluirLFE->SetValue(IncluirLFE);

	FiltrarLFE = PerfilObtenido.LowPassFilter;

	cbFiltrarLFE->SetValue(FiltrarLFE);


	if (PerfilObtenido.ModoRangoDinamico == false)
	{
		rbModoJuego->SetValue(true);

	}
	else if (PerfilObtenido.ModoRangoDinamico == true)
	{
		rbModoPelicula->SetValue(true);
	}

	if (ModoRangoDinamico == false)
	{
		rbModoJuego->SetValue(true);

	}
	else if (ModoRangoDinamico == true)
	{
		rbModoPelicula->SetValue(true);
	}


	incluirCanalBajasFrecuencias();
}

void FormularioControlVolumen::GuardarPerfilVolumen()
{
	PerfilVolumen PerfilaGuardar = { NULL,NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};


	PerfilaGuardar.volumenL = tbVolumenCanalL->GetValue();
	PerfilaGuardar.volumenR = tbVolumenCanalR->GetValue();
	PerfilaGuardar.volumenC = tbVolumenCanalC->GetValue();
	PerfilaGuardar.volumenLFE = tbVolumenCanalLFE->GetValue();
	PerfilaGuardar.volumenSL = tbVolumenCanalSL->GetValue();
	PerfilaGuardar.volumenSR = tbVolumenCanalSR->GetValue();
	PerfilaGuardar.volumenRL = tbVolumenCanalRL->GetValue();
	PerfilaGuardar.volumenRR = tbVolumenCanalRR->GetValue();
	PerfilaGuardar.volumenLT = tbVolumenLT->GetValue();
	PerfilaGuardar.volumenRT = tbVolumenRT->GetValue();

	if (cbIncluirLFE->GetValue() == true)
	{
		PerfilaGuardar.IncluirLFE = true;
	}
	else if (cbIncluirLFE->GetValue() == false)
	{
		PerfilaGuardar.IncluirLFE = false;
	}

	if (cbFiltrarLFE->GetValue() == true)
	{
		PerfilaGuardar.LowPassFilter = true;
	}
	else if (cbFiltrarLFE->GetValue() == false)
	{
		PerfilaGuardar.LowPassFilter = false;
	}

	if (rbModoJuego->GetValue() == true && rbModoPelicula->GetValue() == false)
	{
		PerfilaGuardar.ModoRangoDinamico = false;
	}
	else if (rbModoPelicula->GetValue() == true && rbModoJuego->GetValue() == false)
	{
		PerfilaGuardar.ModoRangoDinamico = true;
	}

	RutaArchivoVolumen = getenv(Enviro.c_str()) + finalRuta + ArchivoVolumen;


	GuardarPerfildeVolumen(PerfilaGuardar, (char*)RutaArchivoVolumen.c_str());

	
}

void FormularioControlVolumen::InicializarNivelesVolumen()
{
	LeerPerfilVolumen();


	tbVolumenCanalL->SetValue(volumenL * 100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalL->GetValue());
	NivelL->SetLabel(cadenaValorSliders + "%");

	tbVolumenCanalR->SetValue(volumenR * 100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalR->GetValue());
	NivelR->SetLabel(cadenaValorSliders + "%");

	tbVolumenCanalC->SetValue(volumenC * 100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalC->GetValue());
	NivelC->SetLabel(cadenaValorSliders + "%");

	tbVolumenCanalLFE->SetValue(volumenLFE * 100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalLFE->GetValue());
	NivelLFE->SetLabel(cadenaValorSliders + "%");

	tbVolumenCanalSL->SetValue(volumenSL * 100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalSL->GetValue());
	NivelSL->SetLabel(cadenaValorSliders + "%");

	tbVolumenCanalSR->SetValue(volumenSR * 100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalSR->GetValue());
	NivelSR->SetLabel(cadenaValorSliders + "%");

	tbVolumenCanalRL->SetValue(volumenRL * 100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalRL->GetValue());
	NivelRL->SetLabel(cadenaValorSliders + "%");

	tbVolumenCanalRR->SetValue(volumenRR * 100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalRR->GetValue());
	NivelRR->SetLabel(cadenaValorSliders + "%");

	//L Y R TOTALES
	tbVolumenLT->SetValue(volumenLT * 100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenLT->GetValue());
	NivelLT->SetLabel(cadenaValorSliders + "%");

	tbVolumenRT->SetValue(volumenRT * 100);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenRT->GetValue());
	NivelRT->SetLabel(cadenaValorSliders + "%");

	cbIncluirLFE->SetValue(IncluirLFE);
	cbFiltrarLFE->SetValue(FiltrarLFE);
}

void FormularioControlVolumen::incluirCanalBajasFrecuencias()
{
	if (cbIncluirLFE->GetValue() == true)
	{
		IncluirLFE = true;
		CodificadorMatriz->IncluirCanalBajasFrecuencias(IncluirLFE);
		tbVolumenCanalLFE->Enable(true);
		cbFiltrarLFE->Enable(true);
	}
	else if (cbIncluirLFE->GetValue() == false)
	{
		IncluirLFE = false;
		CodificadorMatriz->IncluirCanalBajasFrecuencias(IncluirLFE);
		tbVolumenCanalLFE->Enable(false);
		cbFiltrarLFE->Enable(false);
		cbFiltrarLFE->SetValue(false);
	}
}
///////////////////////////////////////////////////////
void FormularioControlVolumen::establecerPerfilesVolumen(unsigned char Canales)
{
	cbPerfilesVolumen->Clear();
	cbPerfilesVolumen->Append(_("Personalizado"));

	if (Canales == 6)
	{
		cbPerfilesVolumen->Append(_("Solo L"));
		cbPerfilesVolumen->Append(_("Solo R"));
		cbPerfilesVolumen->Append(_("Solo C"));
		cbPerfilesVolumen->Append(_("Solo LFE"));
		cbPerfilesVolumen->Append(_("Solo SL"));
		cbPerfilesVolumen->Append(_("Solo SR"));
		cbPerfilesVolumen->Append(_("Solo L y R"));
		cbPerfilesVolumen->Append(_("Solo SL y SR"));
	}
	else if (Canales == 8)
	{
		cbPerfilesVolumen->Append(_("Solo L"));
		cbPerfilesVolumen->Append(_("Solo R"));
		cbPerfilesVolumen->Append(_("Solo C"));
		cbPerfilesVolumen->Append(_("Solo LFE"));
		cbPerfilesVolumen->Append(_("Solo SL"));
		cbPerfilesVolumen->Append(_("Solo SR"));
		cbPerfilesVolumen->Append(_("Solo RL"));
		cbPerfilesVolumen->Append(_("Solo RR"));
		cbPerfilesVolumen->Append(_("Solo L y R"));
		cbPerfilesVolumen->Append(_("Solo SL y SR"));
		cbPerfilesVolumen->Append(_("Solo RL y RR"));
	}

	cbPerfilesVolumen->SetSelection(0);
}


void FormularioControlVolumen::cambiarValoresDeReduccionVolumen()
{
	if (rbModoJuego->GetValue() == true && rbModoPelicula->GetValue() == false)
	{
		if (cbIncluirLFE->GetValue() == true && cbFiltrarLFE->GetValue() == true)
		{
			CodificadorMatriz->IncluirCanalBajasFrecuencias(true);
			CodificadorMatriz->FiltrarCanalBajasFrecuencias(true);
			CodificadorMatriz->comprimirRangoDinamico();
		}
		else if (cbIncluirLFE->GetValue() == true && cbFiltrarLFE->GetValue() == false)
		{
			CodificadorMatriz->IncluirCanalBajasFrecuencias(true);
			CodificadorMatriz->FiltrarCanalBajasFrecuencias(false);
			CodificadorMatriz->comprimirRangoDinamico();
		}
	}
	else if (rbModoJuego->GetValue() == false && rbModoPelicula->GetValue() == true)
	{
		CodificadorMatriz->eliminarReducciondeRangoDinamico();
	}
}


//Declaracion de los eventos


void FormularioControlVolumen::btnReiniciar_click(wxCommandEvent& WXUNUSED(event))
{
	ReiniciarControlesVolumen();
}

void FormularioControlVolumen::refrescarFormularioControlVolumen(int CanalesaProcesar)
{
	bool OcultarElementos = false;
	if (CanalesaProcesar != NumerodeCanalesenProceso) //Significa que el valor no coincide
	{
		NumerodeCanalesenProceso = CanalesaProcesar;

		if (CanalesaProcesar == 6)
		{
			valorPosicion = 100;
			tbVolumenCanalRL->Hide();
			tbVolumenCanalRR->Hide();
			NivelRL->Hide();
			NivelRR->Hide();
			LRL->Hide();
			LRR->Hide();
		}
		else if (CanalesaProcesar == 8)
		{
			OcultarElementos = true;
			valorPosicion = 0;
		}

		AjusteFormularioporIdioma(LenguajeEnUso);

		
		panelFormularioControlVolumen->SetSize(wxSize(TamanoVentanaX - valorPosicion, TamanoVentanaY));
		stbContenedorVolumenEntrada->SetSize(wxSize(410 - valorPosicion, 178));
		stbContenedorVolumenSalida->SetPosition(wxPoint(430 - valorPosicion, 40));
		stbContenedorOpcionesLFE->SetPosition(wxPoint(562 - valorPosicion, 40));
		stbContenedorModoRangoDinamico->SetPosition(wxPoint(562 - valorPosicion, 130));

		
		tbVolumenCanalRL->Show(OcultarElementos);
		tbVolumenCanalRR->Show(OcultarElementos);
		NivelRL->Show(OcultarElementos);
		NivelRR->Show(OcultarElementos);
		LRL->Show(OcultarElementos);
		LRR->Show(OcultarElementos);
		establecerPerfilesVolumen(CanalesaProcesar);

		
		this->SetMinSize(wxSize((TamanoVentanaX - valorPosicion + XajusteporIdioma), TamanoVentanaY));
		this->SetMaxSize(wxSize(TamanoVentanaX - valorPosicion + XajusteporIdioma, TamanoVentanaY));
		this->SetSize(wxSize(TamanoVentanaX - valorPosicion + XajusteporIdioma, TamanoVentanaY));
		this->UpdateWindowUI();
		return;

	}
	else if (CanalesaProcesar < 6 || CanalesaProcesar > 8)
	{
		this->Close();
		return;
	}
	else
	{
		//Si el numero se matiene igual se matiene la apariencia actual;
		return;
	}
}

void FormularioControlVolumen::tbVolumenCanalL_cambioValor(wxCommandEvent& WXUNUSED(event))
{

	volumenL = (tbVolumenCanalL->GetValue() / 100.00);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalL->GetValue());
	NivelL->SetLabel(cadenaValorSliders + "%");
}

void FormularioControlVolumen::tbVolumenCanalR_cambioValor(wxCommandEvent& WXUNUSED(event))
{
	volumenR = (tbVolumenCanalR->GetValue() / 100.00);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalR->GetValue());
	NivelR->SetLabel(cadenaValorSliders + "%");

}

void FormularioControlVolumen::tbVolumenCanalC_cambioValor(wxCommandEvent& WXUNUSED(event))
{
	volumenC = (tbVolumenCanalC->GetValue() / 100.00);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalC->GetValue());
	NivelC->SetLabel(cadenaValorSliders + "%");
}

void FormularioControlVolumen::tbVolumenCanalLFE_cambioValor(wxCommandEvent& WXUNUSED(event))
{
	volumenLFE = (tbVolumenCanalLFE->GetValue() / 100.00);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalLFE->GetValue());
	NivelLFE->SetLabel(cadenaValorSliders + "%");
}

void FormularioControlVolumen::tbVolumenCanalSL_cambioValor(wxCommandEvent& WXUNUSED(event))
{
	volumenSL = (tbVolumenCanalSL->GetValue() / 100.00);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalSL->GetValue());
	NivelSL->SetLabel(cadenaValorSliders + "%");
}

void FormularioControlVolumen::tbVolumenCanalSR_cambioValor(wxCommandEvent& WXUNUSED(event))
{
	volumenSR = (tbVolumenCanalSR->GetValue() / 100.00);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalSR->GetValue());
	NivelSR->SetLabel(cadenaValorSliders + "%");
}

void FormularioControlVolumen::tbVolumenCanalRL_cambioValor(wxCommandEvent& WXUNUSED(event))
{
	volumenRL = (tbVolumenCanalRL->GetValue() / 100.00);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalRL->GetValue());
	NivelRL->SetLabel(cadenaValorSliders + "%");
}

void FormularioControlVolumen::tbVolumenCanalRR_cambioValor(wxCommandEvent& WXUNUSED(event))
{
	volumenRR = (tbVolumenCanalRR->GetValue() / 100.00);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenCanalRR->GetValue());
	NivelRR->SetLabel(cadenaValorSliders + "%");
}

void FormularioControlVolumen::tbVolumenLT_cambioValor(wxCommandEvent& WXUNUSED(event))
{
	volumenLT = (tbVolumenLT->GetValue() / 100.00);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenLT->GetValue());
	NivelLT->SetLabel(cadenaValorSliders + "%");
}

void FormularioControlVolumen::tbVolumenRT_cambioValor(wxCommandEvent& WXUNUSED(event))
{
	volumenRT = (tbVolumenRT->GetValue() / 100.00);
	cadenaValorSliders = wxString::Format(wxT("%d"), tbVolumenRT->GetValue());
	NivelRT->SetLabel(cadenaValorSliders + "%");
}

void FormularioControlVolumen::cbPerfilesVolumen_cambioIndice(wxCommandEvent& WXUNUSED(event))
{
	elegirPerfilVolumen();
}

void FormularioControlVolumen::cbIncluirLFE_cambioCheck(wxCommandEvent& WXUNUSED(event))
{
	incluirCanalBajasFrecuencias();
	cambiarValoresDeReduccionVolumen();
}

void FormularioControlVolumen::cbFiltrarLFE_cambioCheck(wxCommandEvent& WXUNUSED(event))
{
	if (cbFiltrarLFE->GetValue() == true)
	{
		FiltrarLFE = true;

	}
	if (cbFiltrarLFE->GetValue() == false)
	{
		FiltrarLFE = false;
	}
	CodificadorMatriz->FiltrarCanalBajasFrecuencias(FiltrarLFE);
	cambiarValoresDeReduccionVolumen();
}

void FormularioControlVolumen::rbModoJuego_cambioCheck(wxCommandEvent& WXUNUSED(event))
{
	ModoRangoDinamico = false;
	cambiarValoresDeReduccionVolumen();
}

void FormularioControlVolumen::rbModoPelicula_cambioCheck(wxCommandEvent& WXUNUSED(event))
{
	ModoRangoDinamico = true;
	cambiarValoresDeReduccionVolumen();
}



void FormularioControlVolumen::cerrarVentana(wxCloseEvent& WXUNUSED(event))
{
	GuardarPerfilVolumen();
	EstadoFormularioControlVolumen = false;
	this->Destroy();
}




//Listado de eventos

wxBEGIN_EVENT_TABLE(FormularioControlVolumen, wxDialog)

EVT_CLOSE(FormularioControlVolumen::cerrarVentana)

EVT_BUTTON(ID_BUTTON_REINICIAR, FormularioControlVolumen::btnReiniciar_click)

EVT_COMBOBOX(ID_COMBOBOX_PERFILES_VOLUMEN, FormularioControlVolumen::cbPerfilesVolumen_cambioIndice)

EVT_CHECKBOX(ID_CHECKBUTTON_INCLUIR_LFE, FormularioControlVolumen::cbIncluirLFE_cambioCheck)
EVT_CHECKBOX(ID_CHECKBUTTON_FILTRAR_LFE, FormularioControlVolumen::cbFiltrarLFE_cambioCheck)

EVT_RADIOBUTTON(ID_RADIOBUTTON_MODOJUEGO, FormularioControlVolumen::rbModoJuego_cambioCheck)
EVT_RADIOBUTTON(ID_RADIOBUTTON_MODOPELICULA, FormularioControlVolumen::rbModoPelicula_cambioCheck)

EVT_SLIDER(ID_SLIDER_TB_VOLUMEN_CANAL_L, FormularioControlVolumen::tbVolumenCanalL_cambioValor)
EVT_SLIDER(ID_SLIDER_TB_VOLUMEN_CANAL_R, FormularioControlVolumen::tbVolumenCanalR_cambioValor)
EVT_SLIDER(ID_SLIDER_TB_VOLUMEN_CANAL_C, FormularioControlVolumen::tbVolumenCanalC_cambioValor)
EVT_SLIDER(ID_SLIDER_TB_VOLUMEN_CANAL_LFE, FormularioControlVolumen::tbVolumenCanalLFE_cambioValor)
EVT_SLIDER(ID_SLIDER_TB_VOLUMEN_CANAL_SL, FormularioControlVolumen::tbVolumenCanalSL_cambioValor)
EVT_SLIDER(ID_SLIDER_TB_VOLUMEN_CANAL_SR, FormularioControlVolumen::tbVolumenCanalSR_cambioValor)
EVT_SLIDER(ID_SLIDER_TB_VOLUMEN_CANAL_RL, FormularioControlVolumen::tbVolumenCanalRL_cambioValor)
EVT_SLIDER(ID_SLIDER_TB_VOLUMEN_CANAL_RR, FormularioControlVolumen::tbVolumenCanalRR_cambioValor)
EVT_SLIDER(ID_SLIDER_TB_VOLUMEN_CANAL_LT, FormularioControlVolumen::tbVolumenLT_cambioValor)
EVT_SLIDER(ID_SLIDER_TB_VOLUMEN_CANAL_RT, FormularioControlVolumen::tbVolumenRT_cambioValor)

wxEND_EVENT_TABLE()