#ifndef PANTALLAPRINCIPAL_H_INCLUDED
#define PANTALLAPRINCIPAL_H_INCLUDED



// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include <wx/taskbar.h>
//#include "wx/slider.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "Conexion.h"
// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows it is in resources and even
// though we could still include the XPM here it would be unused)
#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "../sample.xpm"
#endif

#include "img\MatrixEncoderl6to2.xpm" 
#include "img\MatrixEncoderl8to2.xpm"
#include "img\advertencia.xpm"
#include "img\MatrixEncoderIcon_1.xpm"

#include "Callbacks.h"
#include "MatrixEncoder.h"
#include "FormularioAcerca.h"
#include "ArchivoIndiceDispositivos.h"
#include "FormularioControlVolumen.h"
#include "FormularioAyuda.h"
#include "ArchivoControlVolumen.h"
#include "ArchivoCambioLenguaje.h"
#include "ErroresPrograma.h"
#include "RutaArchivo.h"

//Para cliente monitor
#include  <Mmdeviceapi.h>


//Solo se usara para monitorear cambio del dispositivo principal

#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

class ClienteMonitor : public IMMNotificationClient
{
	LONG Referencia;
	IMMDeviceEnumerator* ptrEnumerador;
	LPWSTR IDdispositivoPredeterminado;

	/*Esta variable es para que cuando no haya dispositivos
	a IDdispositivoPredeterminado se le pueda asignar una cadena
	nula para que cuando sea comparada no hay violaciones
	de acceso */
	std::wstring  cm_cadena_vacia = L"no audio device\0";

	HRESULT STDMETHODCALLTYPE getDefaultAudioEndpointId();

public:
	ClienteMonitor();
	~ClienteMonitor();
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, VOID **ppvInterface);

	//Funciones notificador
	HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow Flujo, ERole Rol, LPCWSTR IdDispositivo);
	HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR IdDispositivo);
	HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR IdDispositivo);
	HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR IdDispositivo, DWORD NuevoEstado);
	HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR IdDispositivo, const PROPERTYKEY propiedad);
};


static const wxLanguage IdiomasSoportados[] =
{
	wxLANGUAGE_FRENCH,
	wxLANGUAGE_GERMAN,
	wxLANGUAGE_RUSSIAN,
	wxLANGUAGE_SPANISH,
	wxLANGUAGE_PORTUGUESE,
	wxLANGUAGE_CHINESE,
	wxLANGUAGE_HINDI,
	wxLANGUAGE_ENGLISH,
	wxLANGUAGE_ARABIC,
};


const wxString IdiomasDisponibles[] =
{
	"Francais",
	"Deutsch",
	"Russky",
	"Espanol",
	"Portugesse",
	"Chinese",
	"Hindi",
	"English",
	"Arabic",
};


//Esta estrucutra se usa en conjunto con la ListaDispositivosSalida para alamacenar los datos
//de estos dispositivos.
struct InformacionDispositivo
{
	unsigned char IDdispositivo;
	unsigned char NumCanales;
	unsigned int FrecuenciaMuestreo;
	unsigned int Api;
	unsigned int tamanoNombre;
	std::string NombreDispositivo;
};



//Conexiones
class ConexionServidor : public wxConnection
{
public:
	virtual bool OnExecute(const wxString& topic, const void *data, size_t size, wxIPCFormat format) wxOVERRIDE;
	virtual bool OnDisconnect() wxOVERRIDE;
};

class Servidor : public wxServer
{
protected:
	ConexionServidor *m_ConexionServidor;

public:
	Servidor();
	virtual ~Servidor();
	void Desconectar();
	bool EstadoConexion();
	ConexionServidor *ObtenerConexion();
	virtual wxConnectionBase *OnAcceptConnection(const wxString& topic) wxOVERRIDE;
};

class IconoBarra : public wxTaskBarIcon
{
private:

	wxMenu *SubMenuModoVolumen;
	void MonstrarVentanaPrincipal();
public:

	IconoBarra() {};


	virtual wxMenu *CreatePopupMenu() wxOVERRIDE; //Crea el menu del icono;
	void Click_Icono(wxTaskBarIconEvent& event);
	void abrirPantallaPrincipal(wxCommandEvent& event);
	void CerrarPrograma(wxCommandEvent& evento);
	void AbrirPanelControlVolumen(wxCommandEvent& event);
	void AbrirPanelDispositivos_Audio(wxCommandEvent& event);
	void ReiniciarSonido(wxCommandEvent& event);
	void elegirModoJuego(wxCommandEvent& event);
	void elegirModoPelicula(wxCommandEvent& event);
	void actualizarRadioBotonModoJuego(wxUpdateUIEvent & event);
	void actualizarRadioBotonModoPelicula(wxUpdateUIEvent & event);

	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_MENU_ABRIR_PANTALLA_PRINCIPAL = 100,
	ID_MENU_ABRIR_FORUMALRIO_CONTROL_VOLUMEN,
	ID_MENU_REINICIAR_AUDIO,
	ID_MENU_CERRAR,
	ID_MENU_CAMBIAR_MODO_VOLUMEN,
	ID_MENU_ABRIR_PANEL_DISPOSITIVOS_AUDIO,
	ID_MENU_MODO_JUEGO,
	ID_MENU_MODO_PELICULA
};

static void InterrupcionAudioDispositivoPredeterminado(void *);

static void InterrupcionAudioDispositivoSalida(void *);

class PantallaPrincipal : public wxFrame
{
private:
	//Formularios adicionales
	FormularioAcerca *AcercaFormulario = nullptr; // = new FormularioAcerca(this, "Acerca de este Programa");
	FormularioControlVolumen *controlVolumen = nullptr;// = new FormularioControlVolumen(this, 6);
	FormularioAyuda *AyudaFormulario = nullptr;


	//Variables de los dispositivos de audio
	InformacionDispositivo InformacionDispositivoEntrada;

											
	unsigned char DispositivoSalida;

	std::vector<InformacionDispositivo> ListaDispositivosSalida;

	int IndicecbDispositivoSalida;
	unsigned char ConteoDispositivosSalida;

	unsigned char MinimoNumeroCanalesEntrada = 6;
	unsigned char MaximoNumeroCanalesEntrada = 8;

	unsigned char MaximoNumeroCanalesSalida = 2;

	PaHostApiTypeId ApiaUsar = paWASAPI;

	//Datos internos
	PaStream *Flujo; //Este es el flujo de audio que se controlara
	PaStream  *FlujoMonitorDispositivoEntrada;
	PaStreamFinishedCallback *ptrFuncionMonitorDispositivoEntrada = nullptr;
	PaStreamFinishedCallback *ptrFuncionMonitorDispositivoSalida = nullptr;
	int RetrasoEnMilisegundos = 3; //Este dato es para el buffer de retraso usaod para los canales envolventes

	//Funciones internas del programa
	//funciones de eleccion de dispositivos
	PaError InicializarAudio();
	PaError Codificar();
	PaError Refrescar();
	
	//Monitor de dispositivos de audio
	IMMDeviceEnumerator *ptrEnumeradorDispositivosAudio = nullptr;
	ClienteMonitor *MonitorDispositivoPredeterminado = nullptr;

	HRESULT InicilizarMonitorDispositivoPredeterminado();
	HRESULT EliminarMonitorDispositivoPredeterminado();


	void errorFrecuenciadeMuestreo();
	PaError verificarNumerodeDispositivosEnSistema(PaHostApiTypeId Api); //Esta funcion verfica que haya dispositivos en el sistema;
	PaError  establecerDispositivoPredeterminadoEntrada(int NumeroCanalesMinimo, int NumeroCanalesMaximo, PaHostApiTypeId Api);
	PaError establecerDispositivosdeSalida(int CanalesSalida, PaHostApiTypeId Api);

	PaError TransformarAudio(PaDeviceIndex DispositivoSalida);

	void InicializarVolumen();
	void GuardarPerfilVolumen();

	bool cambio_dispositivo = false;
	void DetenerAudio();
	void formatoEtiquetaCanales();

	//Estas funciones activan o desactivan los elementos de las pantalla principal
	void activarElementosPantallaPrincipal();
	void desactivarElementosPantallaPrincipal();

	//Abrir panel de dispositivos de audio.
	void AbrirPanelDispositivosAudio(wxCommandEvent& Evento);


	int TamanoVentanaX = 530;
	int TamanoVentanaY = 300;

	//Servidor Interno;
	bool EstadoServidorInterno;
	Servidor *ServidorInterno;
	void IncializarServidorInterno();


	//Menu
	wxIcon Icono;
	wxMenuBar* BarraMenuPatallaPrincipal = nullptr;
	wxMenu* Archivo = nullptr;
	wxMenu* Opciones = nullptr;
	wxMenu* Ayuda = nullptr;

	//Elmentos panel Principal.
	wxStaticBox* ContenedorDispositivoEntrada = nullptr;
	wxStaticBox* ContenedorDispositivoSalida = nullptr;

	wxComboBox* cbDispositivoEntrada = nullptr;
	wxComboBox* cbDispositivoSalida = nullptr;

	wxStaticText* LCanalesEntrada = nullptr;
	wxStaticText* LFrecuenciaMuestreoEntrada = nullptr;

	wxStaticText* LCanalesSalida = nullptr;
	wxStaticText* LFrecuenciaMuestreoSalida = nullptr;

	wxStaticText* LDECanales = nullptr;
	wxStaticText* LDEFrecuenciaMuestreo = nullptr;

	wxStaticText* LDSCanales = nullptr;
	wxStaticText* LDSFrecuenciaMuestreo = nullptr;

	wxButton* btnRefrescar = nullptr;
	wxButton* btnCodificar = nullptr;
	wxButton* btnDetener = nullptr;

	//Imagenes
	wxStaticBitmap* pbMatrixEncoder6to2 = nullptr;
	wxStaticBitmap* pbMatrixEncoder8to2 = nullptr;
	wxStaticBitmap* pbAdvertenciaFrecuenciaMuestreo = nullptr;

	wxPanel* PanelPrincipal = nullptr;


	//Ajuste del rotulo frecuencia de muestreo por motivo de los idiomas.
	int XajusteporIdioma = 0;
	wxLocale& LocalizacionPantallaPrincipal;
	void AjusteFormularioporIdioma(wxLanguage IdiomaenUso);

	//Para determinar que el proceso fue detenido automaticamente se usa este bool
	bool BotonDetenerHaSidoPresionado = false;

protected:
	//Icono de Barra
	IconoBarra *MiIconodeBarra = nullptr;
	wxLanguage Idiomaenuso;

public:
	// ctor(s)
	PantallaPrincipal(const wxString& title, wxLocale& Localizacion, wxLanguage Idioma);
	virtual ~PantallaPrincipal();

	//Funcion para cuando se inicializ otra instancia
	void MostrarVentana();
	void DesconectarServidorInterno();

	//Funciones para el menajeo de cambio en los dispositivos 
	//de audio 
	bool BotonDetenerPresionado();
	int obtenerIndiceDispositivoSalida();
	void CambioDispositivoPrincipal();
	void CambiosDispositivoPredeterminadoEntrada();
	void CambiosDispositivoSalida();
	void abrir_panel_dispositivos_audio();

	// event handlers (these functions should _not_ be virtual)
	void CerrarPrograma(wxCommandEvent& event);
	void TerminarPrograma(wxCloseEvent& event);
	void btnCodificar_clicked(wxCommandEvent& event);
	void btnRefrescar_clicked(wxCommandEvent& event);
	void btnDetener_clicked(wxCommandEvent& event);
	void cbDispositivoSalida_CambioIndice(wxCommandEvent& event);
	void abrirFormularioAcerca(wxCommandEvent& event);
	void abrirFormularioAyuda(wxCommandEvent& event);
	void abrirFormularioControlVolumen(wxCommandEvent& event);
	void abrirFormularioControlVolumen();
	void CambiarIdiomaPrograma(wxCommandEvent& event);
	void ReiniciarSonido();
	void Minimizar(wxIconizeEvent& event);


	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
	// menu items
	ID_ARCHIVO_SALIR = wxID_EXIT,

	ID_AYUDA_ACERCA = wxID_ABOUT,
	ID_AYUDA_AYUDA,
	ID_ABRIR_PANEL_DISPOSITIVOS_AUDIO,
	ID_PANTALLA_CONTROL_VOLUMEN,
	ID_CAMBIO_IDIOMA,

	//Elementos panel principal
	ID_CONTENEDOR_DISPOSITIVO_ENTRADA,
	ID_CONTENEDOR_DISPOSITIVO_SALIDA,

	ID_COMBOBOX_DISPOSITIVO_ENTRADA,
	ID_COMBOBOX_DISPOSITIVO_SALIDA,

	ID_STATICTEXT_L_CANALES_ENTRADA,
	ID_STATICTEXT_L_FRECUENCIA_MUESTREO_ENTRADA,

	ID_STATICTEXT_L_CANALES_SALIDA,
	ID_STATICTEXT_L_FRECUENCIA_MUESTREO_SALIDA,

	ID_STATICTEXT_LDE_CANALES,
	ID_STATICTEXT_LDE_FRECUENCIA_MUESTREO,

	ID_STATICTEXT_LDS_CANALES,
	ID_STATICTEXT_LDS_FRECUENCIA_MUESTREO,

	ID_BOTON_REFRESCAR,
	ID_BOTON_CODIFICAR,
	ID_BOTON_DETENER,

	ID_STATICBITMAP_DPLII,
	ID_STATICBITMAP_DPLIIX,
	ID_STATICBITMAP_ME6TO2,
	ID_STATICBITMAP_ME8TO2,
	ID_STATICBITMAP_ADVERTENCIA_FRECUENCIA_MUESTREO,

	ID_PANEL_PRINCIPAL,

};

//Se Usa esta puntero como referencia a la pantalla principal
//porque se usa para distintas manipulaciones como la del icono
//de barra el servidor interno y los eventos de audio
static PantallaPrincipal* formularioPrincipal = nullptr;
#endif