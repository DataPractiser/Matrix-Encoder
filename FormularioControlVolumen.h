#ifndef FORMULARIOCONTROLVOLUMEN_H_INCLUDED
#define FORMULARIOCONTROLVOLUMEN_H_INCLUDED

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

#include "img\MatrixEncoderIcon_2.xpm"
#include "RutaArchivo.h"

#include "Callbacks.h"

extern bool EstadoFormularioControlVolumen;

class FormularioControlVolumen : public  wxDialog
{
private:
	//Se le asigan el numero de canales o niveles que se van a nivel
	//si el dispositivo a procesar es 6 solo 6 controles deslizantes aparaceran.
	int NumerodeCanalesenProceso;
	//Este valor se usa para cambiar el tamano del formulario cuando solo se procesan 6 canales de audio;
	int valorPosicion = 0;

	//Variables
	int TamanoVentanaX = 706;
	int TamanoVentanaY = 280; 
	int XajusteporIdioma = 0;

	

	wxPanel* panelFormularioControlVolumen = nullptr;
	wxIcon Icono;

	//elementos del formulario
	wxStaticText* stPerfilVolumen = nullptr;
	wxComboBox* cbPerfilesVolumen = nullptr;
	wxButton* btnReiniciar = nullptr;

	wxStaticBox* stbContenedorVolumenEntrada = nullptr;
	wxStaticBox* stbContenedorVolumenSalida = nullptr;
	wxStaticBox* stbContenedorOpcionesLFE = nullptr;
	wxStaticBox* stbContenedorModoRangoDinamico = nullptr;

	wxStaticText* LL = nullptr;
	wxStaticText* LR = nullptr;
	wxStaticText* LC = nullptr;
	wxStaticText* LLFE = nullptr;
	wxStaticText* LSL = nullptr;
	wxStaticText* LSR = nullptr;
	wxStaticText* LRL = nullptr;
	wxStaticText* LRR = nullptr;

	wxStaticText* LLT = nullptr;
	wxStaticText* LRT = nullptr;

	wxString cadenaValorSliders;
	wxSlider* tbVolumenCanalL = nullptr;
	wxSlider* tbVolumenCanalR = nullptr;
	wxSlider* tbVolumenCanalC = nullptr;
	wxSlider* tbVolumenCanalLFE = nullptr;
	wxSlider* tbVolumenCanalSL = nullptr;
	wxSlider* tbVolumenCanalSR = nullptr;
	wxSlider* tbVolumenCanalRL = nullptr;
	wxSlider* tbVolumenCanalRR = nullptr;


	wxSlider* tbVolumenLT = nullptr;
	wxSlider* tbVolumenRT = nullptr;

	wxStaticText* NivelL = nullptr;
	wxStaticText* NivelR = nullptr;
	wxStaticText* NivelC = nullptr;
	wxStaticText* NivelLFE = nullptr;
	wxStaticText* NivelSL = nullptr;
	wxStaticText* NivelSR = nullptr;
	wxStaticText* NivelRL = nullptr;
	wxStaticText* NivelRR = nullptr;

	wxStaticText* NivelLT = nullptr;
	wxStaticText* NivelRT = nullptr;

	wxCheckBox* cbIncluirLFE = nullptr;
	wxCheckBox* cbFiltrarLFE = nullptr;

	wxRadioButton* rbModoJuego = nullptr;
	wxRadioButton* rbModoPelicula = nullptr;


	void ReiniciarControlesVolumen();
	void elegirPerfilVolumen();
	void LeerPerfilVolumen();
	void GuardarPerfilVolumen();
	void InicializarNivelesVolumen();
	void incluirCanalBajasFrecuencias();
	void establecerPerfilesVolumen(unsigned char Canales);


	//Esta funcion se usa para cambiar los diferentes valores
	//de uso de rango dimanico ya que en base a si se usa el
	//canal LFE este cambiara;
	void cambiarValoresDeReduccionVolumen();

	//Estas variables y funciones son para ajustar los formularios en vase al 
	//lenguaje en uso
	wxLanguage LenguajeEnUso;
	void AjusteFormularioporIdioma(wxLanguage IdiomaenUso);

public:
	//constructor
	FormularioControlVolumen(wxWindow *Parent, int numeroCanalesaProcesar, wxLanguage IdiomaenUso);
	void cerrarVentana(wxCloseEvent& event);
	void btnReiniciar_click(wxCommandEvent& event);

	//Esta funcion es para cuando se ha hecho una actualizacion en el dispositivo de entrada
	//y este formulario estn en pantalla, efectuando los cambios necesarios.
	void refrescarFormularioControlVolumen(int CanalesaProcesar);

	void tbVolumenCanalL_cambioValor(wxCommandEvent& event);
	void tbVolumenCanalR_cambioValor(wxCommandEvent& event);
	void tbVolumenCanalC_cambioValor(wxCommandEvent& event);
	void tbVolumenCanalLFE_cambioValor(wxCommandEvent& event);
	void tbVolumenCanalSL_cambioValor(wxCommandEvent& event);
	void tbVolumenCanalSR_cambioValor(wxCommandEvent& event);
	void tbVolumenCanalRL_cambioValor(wxCommandEvent& event);
	void tbVolumenCanalRR_cambioValor(wxCommandEvent& event);
	void tbVolumenLT_cambioValor(wxCommandEvent& event);
	void tbVolumenRT_cambioValor(wxCommandEvent& event);

	void cbPerfilesVolumen_cambioIndice(wxCommandEvent& event);

	void cbIncluirLFE_cambioCheck(wxCommandEvent& event);
	void cbFiltrarLFE_cambioCheck(wxCommandEvent& event);

	void rbModoJuego_cambioCheck(wxCommandEvent& event);
	void rbModoPelicula_cambioCheck(wxCommandEvent& event);


private:
	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();


};

enum
{
	ID_PANEL_FORMULARIO_VOLUMEN,

	ID_STATICTEXT_PERFILESVOLUMEN,
	ID_STATICTEXT_LL,
	ID_STATICTEXT_LR,
	ID_STATICTEXT_LC,
	ID_STATICTEXT_LLFE,
	ID_STATICTEXT_LSL,
	ID_STATICTEXT_LSR,
	ID_STATICTEXT_LRL,
	ID_STATICTEXT_LRR,
	ID_STATICTEXT_LLT,
	ID_STATICTEXT_LRT,
	ID_STATICTEXT_NIVELL,
	ID_STATICTEXT_NIVELR,
	ID_STATICTEXT_NIVELC,
	ID_STATICTEXT_NIVELLFE,
	ID_STATICTEXT_NIVELSL,
	ID_STATICTEXT_NIVELSR,
	ID_STATICTEXT_NIVELRL,
	ID_STATICTEXT_NIVELRR,
	ID_STATICTEXT_NIVELLT,
	ID_STATICTEXT_NIVELRT,

	ID_SLIDER_TB_VOLUMEN_CANAL_L,
	ID_SLIDER_TB_VOLUMEN_CANAL_R,
	ID_SLIDER_TB_VOLUMEN_CANAL_C,
	ID_SLIDER_TB_VOLUMEN_CANAL_LFE,
	ID_SLIDER_TB_VOLUMEN_CANAL_SL,
	ID_SLIDER_TB_VOLUMEN_CANAL_SR,
	ID_SLIDER_TB_VOLUMEN_CANAL_RL,
	ID_SLIDER_TB_VOLUMEN_CANAL_RR,
	ID_SLIDER_TB_VOLUMEN_CANAL_LT,
	ID_SLIDER_TB_VOLUMEN_CANAL_RT,

	ID_STATICBOX_CONTENEDOR_VOLUMEN_ENTRADA,
	ID_STATICBOX_CONTENEDOR_VOLUMEN_SALIDA,
	ID_STATICBOX_CONTENEDOR_OPCIONES_LFE,
	ID_STATICBOX_CONTENEDOR_OPCIONES_RANGO,

	ID_BUTTON_REINICIAR,
	ID_COMBOBOX_PERFILES_VOLUMEN,

	ID_CHECKBUTTON_INCLUIR_LFE,
	ID_CHECKBUTTON_FILTRAR_LFE,

	ID_RADIOBUTTON_MODOJUEGO,
	ID_RADIOBUTTON_MODOPELICULA


};
#endif