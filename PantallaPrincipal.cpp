#include "PantallaPrincipal.h"


int CanalesaProcesar = 0;



//Conexion Servidor
//Servidor
//bool ConexionServidor::OnExecute(const wxString& topic, const void *data, size_t size, wxIPCFormat format)
bool ConexionServidor::OnExecute(const wxString& topic, const void *, size_t , wxIPCFormat)
{
	if (topic == IPC_TOPIC)
	{
		formularioPrincipal->MostrarVentana();
		return true;
	}
	else
	{
		return false;
	}
}

bool ConexionServidor::OnDisconnect()
{
	formularioPrincipal->DesconectarServidorInterno();
	return true;
}

//Servidor
Servidor::Servidor()
{
	m_ConexionServidor = NULL;
}

Servidor::~Servidor()
{
	Desconectar();
}

void Servidor::Desconectar()
{
	if (m_ConexionServidor)
	{
		wxDELETE(m_ConexionServidor);
	}
}

bool Servidor::EstadoConexion()
{
	return m_ConexionServidor != NULL;
}

ConexionServidor * Servidor::ObtenerConexion()
{
	return m_ConexionServidor;
}

wxConnectionBase* Servidor::OnAcceptConnection(const wxString& topic)
{
	if (topic == IPC_TOPIC)
	{
		m_ConexionServidor = new ConexionServidor;
		return m_ConexionServidor;
	}
	else
	{
		return nullptr;
	}
}

void PantallaPrincipal::AjusteFormularioporIdioma(wxLanguage IdiomaenUso)
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
		XajusteporIdioma = 45;
		break;
	case wxLANGUAGE_CHINESE:
		XajusteporIdioma = 55;
		break;
	case wxLANGUAGE_ENGLISH:
		XajusteporIdioma = 45;
		break;
	case wxLANGUAGE_FRENCH:
		XajusteporIdioma = 0;
		break;
	case wxLANGUAGE_GERMAN:
		XajusteporIdioma = 45;
		break;
	case wxLANGUAGE_HINDI:
		XajusteporIdioma = 25;
		break;
	case wxLANGUAGE_PORTUGUESE:
		XajusteporIdioma = 0;
		break;
	case wxLANGUAGE_RUSSIAN:
		XajusteporIdioma = 0;
		break;
	case wxLANGUAGE_SPANISH:
		XajusteporIdioma = 0;
		break;
	default:
		break;
	}
}

PantallaPrincipal::PantallaPrincipal(const wxString& Titulo, wxLocale& Localizacion, wxLanguage Idioma) : wxFrame(NULL, wxID_ANY, Titulo), LocalizacionPantallaPrincipal(Localizacion), Idiomaenuso(Idioma)
{
	this->SetSize(wxSize(TamanoVentanaX, TamanoVentanaY));
	this->SetMinSize(wxSize(TamanoVentanaX, TamanoVentanaY));
	this->SetMaxSize(wxSize(TamanoVentanaX, TamanoVentanaY));
	Icono.CopyFromBitmap(wxBitmap(MatrixEncoderIcon_1));
	this->SetIcon(Icono);

	AjusteFormularioporIdioma(Idioma);

	//Estilo de letras
	wxFont FondoLetras(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, _T("Microsoft Sans Serif"), wxFONTENCODING_DEFAULT);

	//Menu pantalla Principal.
	Archivo = new wxMenu();
	Archivo->Append(ID_ARCHIVO_SALIR, _("Cerrar"), _("Cierra el programa"));

	Opciones = new wxMenu();
	Opciones->Append(ID_ABRIR_PANEL_DISPOSITIVOS_AUDIO, _("Panel de Dispositivos de Audio"));
	Opciones->Append(ID_PANTALLA_CONTROL_VOLUMEN, _("Control de Volumen"), _("Le permite ajustar el volumen de la mezcla"));
	Opciones->Append(ID_CAMBIO_IDIOMA, _("Cambiar Idioma"));

	Ayuda = new wxMenu();
	Ayuda->Append(ID_AYUDA_ACERCA, _("Acerca"), _("Informacion del Programa"));
	Ayuda->Append(ID_AYUDA_AYUDA, _("Ayuda"), _("Ayuda del programa"));

	BarraMenuPatallaPrincipal = new wxMenuBar();
	BarraMenuPatallaPrincipal->Append(Archivo, _("Archivo"));
	BarraMenuPatallaPrincipal->Append(Opciones, _("Opciones"));
	BarraMenuPatallaPrincipal->Append(Ayuda, _("Ayuda"));

	this->SetMenuBar(BarraMenuPatallaPrincipal);


	//Panel Principal
	PanelPrincipal = new wxPanel(this, ID_PANEL_PRINCIPAL, wxPoint(0, 0), wxSize(TamanoVentanaX, TamanoVentanaY), NULL, wxString("Panel Principal"));
	PanelPrincipal->SetBackgroundColour(wxColor(255, 255, 255));

	//ContenedorDispositivoEntrada

	ContenedorDispositivoEntrada = new wxStaticBox(PanelPrincipal, ID_CONTENEDOR_DISPOSITIVO_ENTRADA, _("Dispositivo de Entrada"), wxPoint(12, 12), wxSize(490, 52), 0, _T("ID_CONTENEDOR_DISPOSITIVO_ENTRADA"));
	ContenedorDispositivoEntrada->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	ContenedorDispositivoEntrada->SetFont(FondoLetras);

	cbDispositivoEntrada = new wxComboBox(ContenedorDispositivoEntrada, ID_COMBOBOX_DISPOSITIVO_ENTRADA, wxEmptyString, wxPoint(10, 20), wxSize(250, 45), 0, 0, wxCB_READONLY | wxCB_DROPDOWN, wxDefaultValidator, _T("ID_COMBOBOX_DISPOSITIVO_ENTRADA"));
	cbDispositivoEntrada->SetFont(FondoLetras);


	LCanalesEntrada = new wxStaticText(ContenedorDispositivoEntrada, ID_STATICTEXT_L_CANALES_ENTRADA, _("Canales"), wxPoint(280, 10), wxDefaultSize, 0, _T("ID_STATICTEXT_L_CANALES_ENTRADA"));
	LCanalesEntrada->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LCanalesEntrada->SetFont(FondoLetras);


	LFrecuenciaMuestreoEntrada = new wxStaticText(ContenedorDispositivoEntrada, ID_STATICTEXT_L_FRECUENCIA_MUESTREO_ENTRADA, _("Frecuencia de Muestreo"), wxPoint(350 + XajusteporIdioma, 10), wxDefaultSize, 0, _T("ID_STATICTEXT_L_FRECUENCIA_MUESTREO_ENTRADA"));
	LFrecuenciaMuestreoEntrada->SetFont(FondoLetras);
	
	LDECanales = new wxStaticText(ContenedorDispositivoEntrada, ID_STATICTEXT_LDE_CANALES, "0", wxPoint(300, 30), wxDefaultSize, 0, _T("ID_STATICTEXT_LDE_CANALES"));
	LDECanales->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUTEXT));
	LDECanales->SetFont(FondoLetras);
	
	LDEFrecuenciaMuestreo = new wxStaticText(ContenedorDispositivoEntrada, ID_STATICTEXT_LDE_FRECUENCIA_MUESTREO, "0", wxPoint(435, 30), wxDefaultSize, 0, _T("ID_STATICTEXT_LDE_FRECUENCIA_MUESTREO"));
	LDEFrecuenciaMuestreo->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUTEXT));
	LDEFrecuenciaMuestreo->SetFont(FondoLetras);
	LDEFrecuenciaMuestreo->SetToolTip(_("Altas frecuencias de muestreo pueden incrementar el uso del CPU"));

	//Contenedor Dispositivo Salida
	ContenedorDispositivoSalida = new wxStaticBox(PanelPrincipal, ID_CONTENEDOR_DISPOSITIVO_SALIDA, _("Dispositivo de Salida"), wxPoint(12, 80), wxSize(490, 52), 0, _T("ID_CONTENEDOR_DISPOSITIVO_SALIDA"));
	ContenedorDispositivoSalida->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));


	cbDispositivoSalida = new wxComboBox(ContenedorDispositivoSalida, ID_COMBOBOX_DISPOSITIVO_SALIDA, wxEmptyString, wxPoint(10, 20), wxSize(250, 45), 0, 0, wxCB_READONLY | wxCB_DROPDOWN, wxDefaultValidator, _T("ID_COMBOBOX_DISPOSITIVO_SALIDA"));
	cbDispositivoSalida->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_DESKTOP));
	cbDispositivoSalida->SetFont(FondoLetras);

	LCanalesSalida = new wxStaticText(ContenedorDispositivoSalida, ID_STATICTEXT_L_CANALES_SALIDA, _("Canales"), wxPoint(280, 10), wxDefaultSize, 0, _T("ID_STATICTEXT_L_CANALES_SALIDA"));
	LCanalesSalida->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LCanalesSalida->SetFont(FondoLetras);

	LFrecuenciaMuestreoSalida = new wxStaticText(ContenedorDispositivoSalida, ID_STATICTEXT_L_FRECUENCIA_MUESTREO_SALIDA, _("Frecuencia de Muestreo"), wxPoint(350 + XajusteporIdioma, 10), wxDefaultSize, 0, _T("ID_STATICTEXT_L_FRECUENCIA_MUESTREO_ENTRADA"));
	LFrecuenciaMuestreoSalida->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
	LFrecuenciaMuestreoSalida->SetFont(FondoLetras);

	LDSCanales = new wxStaticText(ContenedorDispositivoSalida, ID_STATICTEXT_LDS_CANALES, "0", wxPoint(300, 30), wxDefaultSize, 0, _T("ID_STATICTEXT_LDS_CANALES"));
	LDSCanales->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUTEXT));
	LDSCanales->SetFont(FondoLetras);

	LDSFrecuenciaMuestreo = new wxStaticText(ContenedorDispositivoSalida, ID_STATICTEXT_LDS_FRECUENCIA_MUESTREO, "0", wxPoint(435, 30), wxDefaultSize, 0, _T("ID_STATICTEXT_LDS_FRECUENCIA_MUESTREO"));
	LDSFrecuenciaMuestreo->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUTEXT));
	LDSFrecuenciaMuestreo->SetFont(FondoLetras);
	LDSFrecuenciaMuestreo->SetToolTip(_("Altas frecuencias de muestreo pueden incrementar el uso del CPU"));

	//Botones
	btnRefrescar = new wxButton(PanelPrincipal, ID_BOTON_REFRESCAR, _("Refrescar"), wxPoint(18, 160), wxSize(80, 28), 0, wxDefaultValidator, _T("ID_BOTON_REFRESCAR"));
	btnRefrescar->SetBackgroundColour(wxColor(255, 255, 255));
	btnCodificar = new wxButton(PanelPrincipal, ID_BOTON_CODIFICAR, _("Codificar"), wxPoint(100, 160), wxSize(80, 28), 0, wxDefaultValidator, _T("ID_BOTON_CODIFICAR"));
	btnCodificar->SetBackgroundColour(wxColor(255, 255, 255));
	btnDetener = new wxButton(PanelPrincipal, ID_BOTON_DETENER, _("Detener"), wxPoint(182, 160), wxSize(80, 28), 0, wxDefaultValidator, _T("ID_BOTON_DETENER"));
	btnDetener->SetBackgroundColour(wxColor(255, 255, 255));
	btnDetener->Enable(false);

	
	//Imagenes
	pbMatrixEncoder6to2 = new wxStaticBitmap(PanelPrincipal, ID_STATICBITMAP_ME6TO2, wxBitmap(MatrixEncoderl6to2), wxPoint(275, 155), wxDefaultSize, 0, _T("ID_STATICBITMAP_ME6TO2"));
	pbMatrixEncoder8to2 = new wxStaticBitmap(PanelPrincipal, ID_STATICBITMAP_ME8TO2, wxBitmap(MatrixEncoderl8to2), wxPoint(275, 155), wxDefaultSize, wxNO_BORDER, _T("ID_STATICBITMAP_ME8TO2"));
	pbMatrixEncoder8to2->Hide();

	//pbAdvertenciaFrecuenciaMuestreo = new wxStaticBitmap(PanelPrincipal, ID_STATICBITMAP_ADVERTENCIA_FRECUENCIA_MUESTREO, wxBitmap(wxImage(_T("F:\\Programacinn\\Proyectos\\Proyecto Pro Logic II\\Imagenes\\\Wxwidget\\Advertencia.bmp"))), wxPoint(400, 108), wxDefaultSize, 0, _T("ID_STATICBITMAP_ADVERTENCIA_FRECUENCIA_MUESTREO"));
	pbAdvertenciaFrecuenciaMuestreo = new wxStaticBitmap(PanelPrincipal, ID_STATICBITMAP_ADVERTENCIA_FRECUENCIA_MUESTREO, wxBitmap(advertencia), wxPoint(400, 108), wxDefaultSize, 0, _T("ID_STATICBITMAP_ADVERTENCIA_FRECUENCIA_MUESTREO"));
	pbAdvertenciaFrecuenciaMuestreo->Hide();


	RutaArchivoDispositivo = getenv(Enviro.c_str()) + finalRuta + ArchivoDispositivo;
	
	this->Centre();
	formularioPrincipal = this;

	IncializarServidorInterno();
	InicializarVolumen();
	InicializarAudio();
	

	MiIconodeBarra = new IconoBarra();

	MiIconodeBarra->SetIcon(wxICON(sample), "Matrix Encoder");
	
	InicilizarMonitorDispositivoPredeterminado();
}

PantallaPrincipal::~PantallaPrincipal()
{
	delete MiIconodeBarra;
}

void PantallaPrincipal::MostrarVentana()
{
	this->Iconize(false);
	this->Show(true);
	this->Raise();
	this->SetFocus();
	this->Show(true);

}

void PantallaPrincipal::IncializarServidorInterno()
{
	ServidorInterno = new Servidor;
	EstadoServidorInterno = ServidorInterno->Create(IPC_HOST);
	if (EstadoServidorInterno == false)
	{
		wxDELETE(ServidorInterno);
	}
}


void PantallaPrincipal::DesconectarServidorInterno()
{
	ServidorInterno->Desconectar();
}


int PantallaPrincipal::obtenerIndiceDispositivoSalida()
{
	return DispositivoSalida;
}

void PantallaPrincipal::CambiosDispositivoPredeterminadoEntrada()
{
	PaError Error;
	const PaDeviceInfo *InformacionDispositivoPredeterminadoEntrada;
	PaDeviceIndex IndiceDispositivoPredeterminadoEntrada;
	//Para que no se vuelva a llamar
	ptrFuncionMonitorDispositivoEntrada = nullptr;
	ptrFuncionMonitorDispositivoSalida = nullptr;

	//DetenerAudio();
	Error = Pa_Terminate();

	if (Error != paNoError)
	{
		return;
	}

	Pa_Sleep(500);

	Error = Pa_Initialize();

	if (Error != paNoError)
	{
		return;
	}

	IndiceDispositivoPredeterminadoEntrada = (Pa_GetHostApiInfo(Pa_HostApiTypeIdToHostApiIndex(ApiaUsar))->defaultOutputDevice + 1);

	InformacionDispositivoPredeterminadoEntrada = Pa_GetDeviceInfo(IndiceDispositivoPredeterminadoEntrada);
	
	//Se revisa que cambios ocurrieron.
	if (InformacionDispositivoEntrada.NombreDispositivo.compare(InformacionDispositivoPredeterminadoEntrada->name) != 0)
	{
		//Cambio El dispositivo Predeterminado
		Pa_Terminate();
		InicializarAudio();
		return;
	}
	else if (InformacionDispositivoEntrada.FrecuenciaMuestreo != InformacionDispositivoPredeterminadoEntrada->defaultSampleRate)
	{
		//Caso de desconexion o eliminacion del dispositivo
		
		Pa_Terminate();
		MensajeError(ceCambioFrecuenciaMuestreoDispositivoPredeterminado);
		InicializarAudio();
		return;
	}
	else if (InformacionDispositivoEntrada.NumCanales != InformacionDispositivoPredeterminadoEntrada->maxInputChannels)
	{
		if (InformacionDispositivoPredeterminadoEntrada->maxInputChannels < 6 || InformacionDispositivoPredeterminadoEntrada->maxInputChannels > 8 || InformacionDispositivoPredeterminadoEntrada->maxInputChannels == 7)
		{
			Pa_Terminate();
			InicializarAudio();
			return;
		}
		else if (InformacionDispositivoPredeterminadoEntrada->maxInputChannels == 6 || InformacionDispositivoPredeterminadoEntrada->maxInputChannels == 8)
		{
			Pa_Terminate();
			Codificar();
			return;
		}
		
	}
	else 
	{
		//Cambio de profundidad de bits
		Pa_Terminate();
		Codificar();
		return;
	}
}

void PantallaPrincipal::CambiosDispositivoSalida()
{
	PaError Error = NULL;
	const PaDeviceInfo *informaciondelDispositivoSalida = nullptr;

	//Para que no se vuelva a llamar
	ptrFuncionMonitorDispositivoEntrada = nullptr;
	ptrFuncionMonitorDispositivoSalida = nullptr;

	Error = Pa_Terminate();
	Pa_Sleep(500);
	if (Error != paNoError)
	{
		return;
	}

	Error = Pa_Initialize();

	if (Error != paNoError)
	{
		Pa_Terminate();
		return;
	}

	informaciondelDispositivoSalida = Pa_GetDeviceInfo(DispositivoSalida);


	if (ListaDispositivosSalida[IndicecbDispositivoSalida].NombreDispositivo.compare(informaciondelDispositivoSalida->name) != 0)
	{
		Pa_Terminate();
		//Mensaje
		InicializarAudio();
		return;
	}
	else if (ListaDispositivosSalida[IndicecbDispositivoSalida].FrecuenciaMuestreo != informaciondelDispositivoSalida->defaultSampleRate)
	{
		Pa_Terminate();
		MensajeError(ceCambioFrecuenciaMuestreoDispositivoSalida);
		InicializarAudio();
		return;
	}
	else if (informaciondelDispositivoSalida->maxOutputChannels != 2)
	{
		Pa_Terminate();
		MensajeError(ceCambioNumeroCanaelesDispositivoSalida);
		InicializarAudio();
		return;
	}
	else
	{
		Pa_Terminate();
		Codificar();
		return;
	}
}

void PantallaPrincipal::CambioDispositivoPrincipal()
{
	PaError Error = NULL;
	cambio_dispositivo = true;

	DetenerAudio();

	Error = InicializarAudio();
	if (Error != paNoError)
	{
		MensajeError(Error);
		MostrarVentana();
	}
}



//Funciones de la ventana


PaError PantallaPrincipal::InicializarAudio()
{
	PaError Error = NULL, ErrorSalida = NULL, ErrorPredeterminado = NULL;
	wxString NombreDispositivoSalidaObtenido;
	wxString NombreDispositivoListado;

	Error = Pa_Initialize();

	if (Error != paNoError)
	{
		Pa_Terminate();
		return Error;
	}

	Error = verificarNumerodeDispositivosEnSistema(ApiaUsar);

	if (Error != paNoError)
	{
		Pa_Terminate();
		/*
		*Dispositivo vacios
		* para evitar los grandes combo box inicializados
		*/
		cbDispositivoEntrada->Append(" ");
		cbDispositivoSalida->Append(" ");
		MensajeError(Error);
		this->Show(true);
		return Error;
	}

	ErrorPredeterminado = establecerDispositivoPredeterminadoEntrada(MinimoNumeroCanalesEntrada, MaximoNumeroCanalesEntrada, ApiaUsar);

	//Como no termina esta funcion solo se informa del error
	if (ErrorPredeterminado != paNoError)
	{
		MensajeError(ErrorPredeterminado);
	}

	ErrorSalida = establecerDispositivosdeSalida(MaximoNumeroCanalesSalida, ApiaUsar);

	if (ErrorSalida != paNoError)
	{
		Pa_Terminate();
		MensajeError(ErrorSalida);

		activarElementosPantallaPrincipal();
		cbDispositivoSalida->SetSelection(-1);
		formatoEtiquetaCanales();

		MostrarVentana();
		return Error;
	}

	Error = Pa_Terminate();

	if (Error != paNoError)
	{
		return Error;
	}

	if (ConteoDispositivosSalida == 1 && ErrorPredeterminado == paNoError)
	{
		DispositivoSalida = ListaDispositivosSalida[0].IDdispositivo;
		cbDispositivoSalida->SetSelection(0);
		IndicecbDispositivoSalida = cbDispositivoSalida->GetSelection();
		Error = TransformarAudio(DispositivoSalida);
	}
	else if (ErrorPredeterminado == paNoError)
	{
		//Se verifica si el dispositivo usado la ultima ves esta todavia disponible
		//de ser positivo la conversion de audio se ejecuta automaitcamente sino 
		// a elegir dispositivio;

		if (ArchivoDatosDispositivoSalidaAudio.LeerArchivoDatosDispositivo((char*)RutaArchivoDispositivo.c_str()) == true)//Se verifica que exista el archivo.
		{
			NombreDispositivoSalidaObtenido = ArchivoDatosDispositivoSalidaAudio.obtenerNombreDispositivoSalidaAudio();

			for (int x = 0; x < ConteoDispositivosSalida; x++)
			{
				NombreDispositivoListado = ListaDispositivosSalida[x].NombreDispositivo;

				//Aqui se verifica si son el mismo dispositivo usado la ultima ves.
				if (ListaDispositivosSalida[x].NumCanales == ArchivoDatosDispositivoSalidaAudio.obtenerNumeroCanalesAudio() &&
					(ListaDispositivosSalida[x].FrecuenciaMuestreo == ArchivoDatosDispositivoSalidaAudio.obtenerFrecuenciadeMuestreo()
						|| ListaDispositivosSalida[x].FrecuenciaMuestreo == InformacionDispositivoEntrada.FrecuenciaMuestreo) &&
					ListaDispositivosSalida[x].Api == ArchivoDatosDispositivoSalidaAudio.obtenerApiDispositivo() &&
					strcmp(NombreDispositivoListado, NombreDispositivoSalidaObtenido) == 0)
				{
					DispositivoSalida = ListaDispositivosSalida[x].IDdispositivo;
					cbDispositivoSalida->SetSelection(x);
					IndicecbDispositivoSalida = x;
					Error = TransformarAudio(DispositivoSalida);
					break; //Ya lo encontro para que seguir el bucle?
				}
				else
				{
					Error = ceDispositivodeSalidaNoEncontrado;
				}
			}
		}
		else
		{
			Error = ceDispositivodeSalidaNoEncontrado;
		}
	}

	if (Error != paNoError || ErrorPredeterminado != paNoError || ErrorSalida != paNoError)
	{
		activarElementosPantallaPrincipal();
		cbDispositivoSalida->SetSelection(-1);
		formatoEtiquetaCanales();

		if (Error != paNoError)
		{
			MensajeError(Error);
		}

		MostrarVentana();
		return Error;
	}
	else
	{
		desactivarElementosPantallaPrincipal();
		formatoEtiquetaCanales();

		if (this->IsShown() == true)
		{
			this->Iconize(false);
			this->Raise();
		}
		else
		{
			this->Iconize(); //esta funcion mininiza la ventana
		}
		//this->Show(false);
		Error = paNoError;
		return Error;
	}
}

PaError PantallaPrincipal::Codificar()
{
	PaError Error = 0;
	if (cbDispositivoEntrada->GetSelection() < 0 && cbDispositivoSalida->GetSelection() < 0)
	{
		MensajeError(ceNingunDispositivodeAudioSeleccionado);
		return Error = ceNingunDispositivodeAudioSeleccionado;
	}

	else if (cbDispositivoEntrada->GetSelection() < 0 && cbDispositivoSalida->GetSelection() >= 0)
	{
		MensajeError(ceNoDispositivoEntradaSeleccionado);
		return Error = ceNoDispositivoEntradaSeleccionado;
	}

	else if (cbDispositivoEntrada->GetSelection() >= 0 && cbDispositivoSalida->GetSelection() < 0)
	{
		MensajeError(ceNoDispositivoSalidaSeleccionado);
		return Error = ceNoDispositivoSalidaSeleccionado;
	}

	else if (cbDispositivoEntrada->GetSelection() >= 0 && cbDispositivoSalida->GetSelection() >= 0)
	{
		desactivarElementosPantallaPrincipal();

		DispositivoSalida = ListaDispositivosSalida[cbDispositivoSalida->GetSelection()].IDdispositivo;

		Error = TransformarAudio(DispositivoSalida);

		if (Error == ceFrecuenciasdeMuestreoNoIguales)
		{
			DetenerAudio();
			errorFrecuenciadeMuestreo();
			return Error;
		}
		else if (Error == paNoError)
		{
			return Error;
		}
		else
		{
			DetenerAudio();
			MensajeError(Error);
			errorFrecuenciadeMuestreo();
			return Error;
		}
	}

	return Error;
}

PaError PantallaPrincipal::Refrescar()
{
	PaError Error = NULL;

	pbAdvertenciaFrecuenciaMuestreo->Hide();

	Error = Pa_Initialize();

	if (Error != paNoError)
	{
		Pa_Terminate();
		return Error;
	}

	Error = verificarNumerodeDispositivosEnSistema(ApiaUsar);

	if (Error != paNoError)
	{
		cbDispositivoEntrada->Clear();
		LDECanales->SetLabel("0");
		LDEFrecuenciaMuestreo->SetLabel("0");
		Pa_Terminate();
		MensajeError(Error);
		return Error;
	}

	Error = establecerDispositivoPredeterminadoEntrada(MinimoNumeroCanalesEntrada, MaximoNumeroCanalesEntrada, ApiaUsar);

	if (Error != paNoError)
	{
		MensajeError(Error);
	}

	Error = establecerDispositivosdeSalida(MaximoNumeroCanalesSalida, ApiaUsar);

	if (Error != paNoError)
	{
		Pa_Terminate();
		MensajeError(Error);
		return Error;
	}


	Error = Pa_Terminate();


	cbDispositivoSalida->SetSelection(wxNOT_FOUND);

	formatoEtiquetaCanales();

	return Error;
}

HRESULT PantallaPrincipal::InicilizarMonitorDispositivoPredeterminado()
{
	HRESULT Resultado = NULL;

	MonitorDispositivoPredeterminado = new ClienteMonitor;

	Resultado = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)&ptrEnumeradorDispositivosAudio);

	if (SUCCEEDED(Resultado))
	{
		Resultado = ptrEnumeradorDispositivosAudio->RegisterEndpointNotificationCallback(MonitorDispositivoPredeterminado);


		if (FAILED(Resultado))
		{
			Resultado =  ptrEnumeradorDispositivosAudio->UnregisterEndpointNotificationCallback(MonitorDispositivoPredeterminado);

			if (SUCCEEDED(Resultado))
			{
				ptrEnumeradorDispositivosAudio->Release();
				ptrEnumeradorDispositivosAudio = nullptr;
				MonitorDispositivoPredeterminado->Release();
				MonitorDispositivoPredeterminado = nullptr;
			}
		}
	}

	return Resultado;
}

HRESULT PantallaPrincipal::EliminarMonitorDispositivoPredeterminado()
{
	HRESULT Resultado = E_NOTIMPL;

	Resultado = ptrEnumeradorDispositivosAudio->UnregisterEndpointNotificationCallback(MonitorDispositivoPredeterminado);

	if (SUCCEEDED(Resultado))
	{
		ptrEnumeradorDispositivosAudio->Release();
		ptrEnumeradorDispositivosAudio = nullptr;
		MonitorDispositivoPredeterminado->Release();
		MonitorDispositivoPredeterminado = nullptr;
	}

	return Resultado;
}

bool PantallaPrincipal::BotonDetenerPresionado()
{
	return BotonDetenerHaSidoPresionado;
}

PaError PantallaPrincipal::verificarNumerodeDispositivosEnSistema(PaHostApiTypeId Api)
{
	PaError Error = NULL;
	int NumeroDispositivosCompatibles = 0;
	const PaDeviceInfo *InformacionDispositivos = nullptr;
	int num = Pa_GetDeviceCount();

	for (int i = 0; i < num; i++)
	{
		InformacionDispositivos = Pa_GetDeviceInfo(i);

		if (InformacionDispositivos->maxOutputChannels > 0 && InformacionDispositivos->hostApi == Pa_HostApiTypeIdToHostApiIndex(Api))
		{
			NumeroDispositivosCompatibles += 1;
		}
	}

	if (NumeroDispositivosCompatibles == 0)
	{
		Error = ceNoDispositivosEnElEQuipo;
		return Error;
	}
	else
	{
		Error = paNoError;
		return Error;
	}
}

PaError PantallaPrincipal::establecerDispositivoPredeterminadoEntrada(int NumeroCanalesMinimo, int NumeroCanalesMaximo, PaHostApiTypeId Api)
{
	PaError Error = NULL;
	const PaDeviceInfo* InformacionDispositivoPredeterminadoEntrada = nullptr;
	wxString NombreDispositivo, numeroCanales, frecuenciaMuestreo;
	InformacionDispositivoEntrada.IDdispositivo = (Pa_GetHostApiInfo(Pa_HostApiTypeIdToHostApiIndex(Api))->defaultOutputDevice + 1);


	InformacionDispositivoPredeterminadoEntrada = Pa_GetDeviceInfo(InformacionDispositivoEntrada.IDdispositivo);

	//incializacion;
	cbDispositivoEntrada->Clear();
	LDECanales->SetLabel("0");
	/**/
	LDEFrecuenciaMuestreo->SetLabel("0");

	if ((InformacionDispositivoPredeterminadoEntrada->maxInputChannels == NumeroCanalesMinimo || InformacionDispositivoPredeterminadoEntrada->maxInputChannels == NumeroCanalesMaximo)
		&& InformacionDispositivoPredeterminadoEntrada->hostApi == Pa_HostApiTypeIdToHostApiIndex(Api))
	{
		InformacionDispositivoEntrada.NombreDispositivo = InformacionDispositivoPredeterminadoEntrada->name;
	
		cbDispositivoEntrada->Append(InformacionDispositivoEntrada.NombreDispositivo.c_str());
		InformacionDispositivoEntrada.NumCanales = InformacionDispositivoPredeterminadoEntrada->maxInputChannels;

		numeroCanales << InformacionDispositivoPredeterminadoEntrada->maxInputChannels;
		if (numeroCanales == '6' || numeroCanales == '\x6')
		{
			CanalesaProcesar = 6;
			numeroCanales = "5.1";
		}
		else if (numeroCanales == '8' || numeroCanales == '\x8')
		{
			CanalesaProcesar = 8;
			numeroCanales = "7.1";
		}
		else
		{
			numeroCanales = "0";
		}
		LDECanales->SetLabel(numeroCanales);
		frecuenciaMuestreo << InformacionDispositivoPredeterminadoEntrada->defaultSampleRate;
		InformacionDispositivoEntrada.FrecuenciaMuestreo = InformacionDispositivoPredeterminadoEntrada->defaultSampleRate;

		InformacionDispositivoEntrada.Api = Api;
		LDEFrecuenciaMuestreo->SetLabel(frecuenciaMuestreo);
		cbDispositivoEntrada->SetSelection(0);
		Error = paNoError;
		return Error;
	}
	else if (InformacionDispositivoPredeterminadoEntrada->maxInputChannels != NumeroCanalesMinimo || InformacionDispositivoPredeterminadoEntrada->maxInputChannels != NumeroCanalesMaximo)
	{
		cbDispositivoEntrada->Append(" ");
		Error = ceNoDispositivoEntradaSeleccionado;
		return Error;
	}
	else
	{
		cbDispositivoEntrada->SetSelection(wxNOT_FOUND);
		Error = ceDispositivodeEntradaNoCompatible;
		return Error;
	}
}

PaError PantallaPrincipal::establecerDispositivosdeSalida(int CanalesSalida, PaHostApiTypeId Api)
{
	PaError Error = NULL;
	const PaDeviceInfo* InformacionDispositivosSalida =nullptr;
	wxString NombreDispositivo; //Variable usada para convertir las cadenas de texto a unformato compatible con CLI

	int NumeroTotalDispositivos = 0;
	int DesplazamientoListaDispositivosSalida = 0;


	ListaDispositivosSalida.clear();

	//	delete ListaDispositivosSalida;
	cbDispositivoSalida->Clear();
	LDSCanales->SetLabel("0");
	LDSFrecuenciaMuestreo->SetLabel("0");
	ConteoDispositivosSalida = 0;

	//Se comprueba que no hayan mas de 256 dispositivos, debido a la limitacion de la variables ConteoDispositivosSalida por ser unsigned char;

	NumeroTotalDispositivos = Pa_GetDeviceCount();

	if (NumeroTotalDispositivos > 255 || NumeroTotalDispositivos < 0)
	{
		cbDispositivoSalida->SetSelection(wxNOT_FOUND);
		Error = ceExcesoDispositivosAudio;
		return Error;
	}


	for (int i = 0; i < NumeroTotalDispositivos; i++)
	{
		InformacionDispositivosSalida = Pa_GetDeviceInfo(i);

		//Se verifica que sea de 2 canales de salida y su api sea wasapi
		if (InformacionDispositivosSalida->maxOutputChannels == CanalesSalida && InformacionDispositivosSalida->hostApi == Pa_HostApiTypeIdToHostApiIndex(Api) && i != Pa_GetHostApiInfo(Pa_HostApiTypeIdToHostApiIndex(Api))->defaultOutputDevice)
		{
			ConteoDispositivosSalida += 1;
		}
	}

	if (ConteoDispositivosSalida == 0)
	{
		cbDispositivoSalida->SetSelection(wxNOT_FOUND);
		cbDispositivoSalida->Append(" ");
		//MessageBox::Show("No se encontro ningun dispositivo con 2 canales de salida");
		Error = ceNoDispositivoCon2canalesdeSalida;
		return Error;
	}

	ListaDispositivosSalida.clear();
	ListaDispositivosSalida.resize(ConteoDispositivosSalida);

	for (int y = 0; y < NumeroTotalDispositivos; y++)
	{
		InformacionDispositivosSalida = Pa_GetDeviceInfo(y);

		if (InformacionDispositivosSalida->maxOutputChannels == CanalesSalida && InformacionDispositivosSalida->hostApi == Pa_HostApiTypeIdToHostApiIndex(Api) && y != Pa_GetHostApiInfo(Pa_HostApiTypeIdToHostApiIndex(Api))->defaultOutputDevice)
		{
			ListaDispositivosSalida[DesplazamientoListaDispositivosSalida].IDdispositivo = y;
			ListaDispositivosSalida[DesplazamientoListaDispositivosSalida].NumCanales = InformacionDispositivosSalida->maxOutputChannels;
			ListaDispositivosSalida[DesplazamientoListaDispositivosSalida].FrecuenciaMuestreo = InformacionDispositivosSalida->defaultSampleRate;
			ListaDispositivosSalida[DesplazamientoListaDispositivosSalida].Api = InformacionDispositivosSalida->hostApi;

			ListaDispositivosSalida[DesplazamientoListaDispositivosSalida].NombreDispositivo = InformacionDispositivosSalida->name;

			NombreDispositivo = ListaDispositivosSalida[DesplazamientoListaDispositivosSalida].NombreDispositivo;
			cbDispositivoSalida->Append(ListaDispositivosSalida[DesplazamientoListaDispositivosSalida].NombreDispositivo.c_str());
			DesplazamientoListaDispositivosSalida += 1;
		}
	}

	Error = paNoError;

	return Error;
}



void  PantallaPrincipal::errorFrecuenciadeMuestreo()
{
	int FrecuenciaMuestreoDispositivoEntrada = 0, FrecuenciaMuestreoDispositivoSalida = 0;

	FrecuenciaMuestreoDispositivoEntrada = wxAtoi(LDEFrecuenciaMuestreo->GetLabel());
	FrecuenciaMuestreoDispositivoSalida = wxAtoi(LDSFrecuenciaMuestreo->GetLabel());

	if (cbDispositivoEntrada->GetSelection() >= 0 && cbDispositivoSalida->GetSelection() >= 0)
	{
		if (FrecuenciaMuestreoDispositivoEntrada != 0 || FrecuenciaMuestreoDispositivoSalida != 0)
		{
			if (FrecuenciaMuestreoDispositivoEntrada != FrecuenciaMuestreoDispositivoSalida)
			{
				pbAdvertenciaFrecuenciaMuestreo->Show();
				btnCodificar->Enable(false);
				MensajeError(ceFrecuenciasdeMuestreoNoIguales);
			}
			else if (FrecuenciaMuestreoDispositivoSalida == FrecuenciaMuestreoDispositivoEntrada)
			{
				pbAdvertenciaFrecuenciaMuestreo->Hide();
				btnCodificar->Enable(true);
			}
		}

	}
}

static void InterrupcionAudioDispositivoPredeterminado(void *)
{
	bool BotonDetenerPresionado = NULL;

	
	BotonDetenerPresionado = formularioPrincipal->BotonDetenerPresionado();

	if (BotonDetenerPresionado == false)
	{
		formularioPrincipal->CambiosDispositivoPredeterminadoEntrada();
	}
}

static void InterrupcionAudioDispositivoSalida(void *)
{
	bool BotonDetenerPresionado = NULL;

	BotonDetenerPresionado = formularioPrincipal->BotonDetenerPresionado();

	if (BotonDetenerPresionado == false)
	{
		formularioPrincipal->CambiosDispositivoSalida();
	}
}

PaError PantallaPrincipal::TransformarAudio(PaDeviceIndex DispositivoSalidaAudio)
{
	PaError Error = NULL;
	PaStreamParameters parametrosEntrada = {NULL, NULL, NULL, NULL, NULL}; 
	PaStreamParameters  parametrosSalida = { NULL, NULL, NULL, NULL, NULL };
	const PaDeviceInfo *informacionDispositivoEntrada = nullptr, *informacionDispositivoSalida = nullptr;
	wxString CanalesEntrada, CanalesSalida, FrecuenciaEntrada , FrecuenciaSalida;
	std::string NombreDispositvioaGuardar;

	/*
	* El valor de la latencia es el que al parecer, hace que sucedar los 
	* cortes de audio en las versiones mas recientes de windows 10 empezando
	* con windows 10 2004, esta latencia más alta de lo habitual es 
	* el compromiso para garantizar sonido continuo
	*/
	float Latencia = 1.0;


	//esta variable se usara para selecionar cual de las dos funciones callback a utilizar se usara
	//ya que hay dos una para procesar 5.1 y otra para procesar 7.1;
	PaStreamCallback *punteroFuncionDeProceso;

	//InicializarVolumen();

	float FrecuenciaMuestreo = 0;
	Error = Pa_Initialize();

	if (Error != paNoError)
	{
		Pa_Terminate();
		return Error;
	}
	//Se verifica si el dispositivo de Entrada por si acaso;
	Error = establecerDispositivoPredeterminadoEntrada(MinimoNumeroCanalesEntrada, MaximoNumeroCanalesEntrada, ApiaUsar);

	if (Error != paNoError)
	{
		Pa_Terminate();
		return Error;
	}

	//Establecer la infornmacion de los dispositivos de Entrada Y Salida

	informacionDispositivoEntrada = Pa_GetDeviceInfo(InformacionDispositivoEntrada.IDdispositivo);
	informacionDispositivoSalida = Pa_GetDeviceInfo(DispositivoSalidaAudio);

	//Parametros Entrada
	parametrosEntrada.device = InformacionDispositivoEntrada.IDdispositivo;

	if (informacionDispositivoEntrada->maxInputChannels == 6 || informacionDispositivoEntrada->maxInputChannels == 8)
	{
		parametrosEntrada.channelCount = informacionDispositivoEntrada->maxInputChannels;
	}
	else
	{
		parametrosEntrada.channelCount = informacionDispositivoEntrada->maxInputChannels;
		CanalesEntrada << parametrosEntrada.channelCount;
		cbDispositivoEntrada->Append(informacionDispositivoEntrada->name);
		LDECanales->SetLabel(CanalesEntrada);
		Error = ceNumerodeCanalesDispositivoEntradaNoSoportados;
		Pa_Terminate();
		return Error;
	}

	parametrosEntrada.channelCount = informacionDispositivoEntrada->maxInputChannels;
	parametrosEntrada.sampleFormat = paFloat32;
	parametrosEntrada.suggestedLatency = Latencia;
	parametrosEntrada.hostApiSpecificStreamInfo = NULL;

	//Verificar que el dispositivo de Salida tenga el mismo nombre que el registrado al inicalizar;
	if (informacionDispositivoSalida != NULL)
	{
		if (ListaDispositivosSalida[cbDispositivoSalida->GetSelection()].NombreDispositivo.compare(informacionDispositivoSalida->name) != 0)
		{
			Pa_Terminate();
			Error = ceDispositivoSalidaNODisponible;
			return Error;
		}
	}
	else
	{
		Pa_Terminate();
		Error = ceDispositivoSalidaNODisponible;
		return Error;
	}


	//Parametros Salida
	parametrosSalida.device = DispositivoSalidaAudio;
	parametrosSalida.channelCount = informacionDispositivoSalida->maxOutputChannels;
	parametrosSalida.sampleFormat = paFloat32;
	parametrosSalida.suggestedLatency = Latencia;
	parametrosSalida.hostApiSpecificStreamInfo = NULL;// &WasapiInformacionEspecificaSalida;

	//La frecuencias de muestreo de los dos dispositivos debe ser la misma para funcionar
	if (informacionDispositivoEntrada->defaultSampleRate != informacionDispositivoSalida->defaultSampleRate)
	{
		FrecuenciaEntrada << informacionDispositivoEntrada->defaultSampleRate;
		Pa_Terminate();
		LDEFrecuenciaMuestreo->SetLabel(FrecuenciaEntrada);
		Error = ceFrecuenciasdeMuestreoNoIguales;
		return Error;
	}
	pbAdvertenciaFrecuenciaMuestreo->Hide(); //por si acaso esta mostrada.

	FrecuenciaMuestreo = informacionDispositivoSalida->defaultSampleRate;

	/*Esta mejora es parte de la implementacion de un filtro de bajas frecuencias para el canal LFE
	* Se redujo al estandar de corte de 80hz.
	*/
	CodificadorMatriz->inicializarFiltroPaseBajo(FrecuenciaMuestreo, 80.00);
	//////////////////////////////////////////////////////////////////////////////////////////////


	//inicializar el buffer que contendra las muestra para el retraso
	CodificadorMatriz->establecerRetrasoEnvolventes(FrecuenciaMuestreo, RetrasoEnMilisegundos, (parametrosEntrada.channelCount - 4));


	//Fijar valores de canales y frecuencia de muestreo en las etiquetas
	if (parametrosEntrada.channelCount == 6)
	{
		LDECanales->SetLabel("5.1");
		CanalesaProcesar = 6;

	}
	else if (parametrosEntrada.channelCount == 8)
	{
		LDECanales->SetLabel("7.1");
		CanalesaProcesar = 8;
	}
	else
	{
		LDECanales->SetLabel("N/C");
		return ceNumerodeCanalesDispositivoEntradaNoSoportados;
	}

	if (parametrosSalida.channelCount == 2)
	{
		LDSCanales->SetLabel("2.0");
	}
	else
	{
		LDSCanales->SetLabel("N/C");
		cbDispositivoSalida->SetSelection(wxNOT_FOUND);
		return ceNumerodeCanalesNoSoportado;
	}

	FrecuenciaEntrada << informacionDispositivoEntrada->defaultSampleRate;
	FrecuenciaSalida << informacionDispositivoSalida->defaultSampleRate;
	LDEFrecuenciaMuestreo->SetLabel(FrecuenciaEntrada);
	LDSFrecuenciaMuestreo->SetLabel(FrecuenciaSalida);

	//Este punto determina el callback en base a los caneles de audio

	if (parametrosEntrada.channelCount == 6)
	{
		punteroFuncionDeProceso = SurroundSeisCanalesFlotante;
		CanalesaProcesar = 6;
		pbMatrixEncoder8to2->Hide();
	}
	else if (parametrosEntrada.channelCount == 8)
	{

		punteroFuncionDeProceso = SurroundOchoCanalesFlotante;
		CanalesaProcesar = 8;
		pbMatrixEncoder8to2->Show();
	}
	else
	{
		Error = ceNumerodeCanalesNoSoportado;
		return Error;
	}

	if (EstadoFormularioControlVolumen == true)
	{
		controlVolumen->refrescarFormularioControlVolumen(parametrosEntrada.channelCount);
	}

	
	/*
	* Esta funcion es para abrir un stream que se usa para monitorear cambios en el dispositvo principal de audio
	*/
	Error = Pa_OpenStream(&FlujoMonitorDispositivoEntrada, &parametrosEntrada, NULL, FrecuenciaMuestreo, 128, NULL, callbacknulo, NULL);

	ptrFuncionMonitorDispositivoEntrada = InterrupcionAudioDispositivoPredeterminado;
	Error = Pa_SetStreamFinishedCallback(FlujoMonitorDispositivoEntrada, ptrFuncionMonitorDispositivoEntrada);

	Error = Pa_StartStream(FlujoMonitorDispositivoEntrada);


	/*
	* Callback Principal el cual se encargar de tomar y procesar el audio.
	*/
	Error = Pa_OpenStream(&Flujo, &parametrosEntrada, &parametrosSalida, FrecuenciaMuestreo, 1, paClipOff && paDitherOff, punteroFuncionDeProceso, NULL);

	ptrFuncionMonitorDispositivoSalida = InterrupcionAudioDispositivoSalida;
	Pa_SetStreamFinishedCallback(Flujo, ptrFuncionMonitorDispositivoSalida);


	if (Error != paNoError)
	{
		Pa_Terminate();
		return Error;
	}

	Error = Pa_StartStream(Flujo);

	if (Error != paNoError)
	{
		Pa_Terminate();
		return Error;
	}
	else if (Error == paNoError)
	{
		//Salva el dispositivo usado la ultima ves
		NombreDispositvioaGuardar = informacionDispositivoSalida->name;
		ArchivoDatosDispositivoSalidaAudio.GuardarDatosDispositivoSalidaAudio(RutaArchivoDispositivo,
			DispositivoSalida,
			informacionDispositivoSalida->maxOutputChannels,
			informacionDispositivoSalida->defaultSampleRate,
			informacionDispositivoSalida->hostApi,
			NombreDispositvioaGuardar);

		//Establecer que se monitoree el estado dispositivo que se esta usando
		//para salida de audio
		InformacionDispositivo InfoDispositivoSalida;
		InfoDispositivoSalida.NombreDispositivo = ListaDispositivosSalida[cbDispositivoSalida->GetSelection()].NombreDispositivo;
		InfoDispositivoSalida.NumCanales = ListaDispositivosSalida[cbDispositivoSalida->GetSelection()].NumCanales;
		InfoDispositivoSalida.FrecuenciaMuestreo = ListaDispositivosSalida[cbDispositivoSalida->GetSelection()].FrecuenciaMuestreo;
	}


	return Error;
}

void PantallaPrincipal::InicializarVolumen()
{

	PerfilVolumen PerfilObtenido;

	RutaArchivoVolumen = getenv(Enviro.c_str()) + finalRuta + ArchivoVolumen;
	

	PerfilObtenido = ObtenerPerfilVolumen((char*)RutaArchivoVolumen.c_str());

	RutaArchivoVolumen.erase();

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
	FiltrarLFE = PerfilObtenido.LowPassFilter;

	CodificadorMatriz->IncluirCanalBajasFrecuencias(IncluirLFE);
	CodificadorMatriz->FiltrarCanalBajasFrecuencias(FiltrarLFE);

	ModoRangoDinamico = PerfilObtenido.ModoRangoDinamico;

	if (ModoRangoDinamico == false)
	{
		CodificadorMatriz->comprimirRangoDinamico();
	}
	else if (ModoRangoDinamico == true)
	{
		CodificadorMatriz->eliminarReducciondeRangoDinamico();
	}


}

void PantallaPrincipal::GuardarPerfilVolumen()
{
	PerfilVolumen PerfilaGuardar;

	RutaArchivoVolumen = getenv(Enviro.c_str()) + finalRuta + ArchivoVolumen;

	PerfilaGuardar.volumenL = volumenL * 100;
	PerfilaGuardar.volumenR = volumenR * 100;
	PerfilaGuardar.volumenC = volumenC * 100;
	PerfilaGuardar.volumenLFE = volumenLFE * 100;
	PerfilaGuardar.volumenSL = volumenSL * 100;
	PerfilaGuardar.volumenSR = volumenSR * 100;
	PerfilaGuardar.volumenRL = volumenRL * 100;
	PerfilaGuardar.volumenRR = volumenRR * 100;
	PerfilaGuardar.volumenLT = volumenLT * 100;
	PerfilaGuardar.volumenRT = volumenRT * 100;
	PerfilaGuardar.IncluirLFE = IncluirLFE;
	PerfilaGuardar.LowPassFilter = FiltrarLFE;
	PerfilaGuardar.ModoRangoDinamico = ModoRangoDinamico;

	GuardarPerfildeVolumen(PerfilaGuardar, (char*)RutaArchivoVolumen.c_str());

	RutaArchivoVolumen.erase();
}

void PantallaPrincipal::DetenerAudio()
{
	PaError Error = NULL;
	PaError ErrorEntrada = NULL;
	PaError ErrorSalida = NULL;
	activarElementosPantallaPrincipal();

	BotonDetenerHaSidoPresionado = true;

	if ((Error = Pa_IsStreamActive(Flujo)) == 1)
	{
		ptrFuncionMonitorDispositivoEntrada = nullptr;

		ptrFuncionMonitorDispositivoSalida = nullptr;

		ErrorSalida = Pa_StopStream(Flujo);

		ErrorEntrada = Pa_StopStream(FlujoMonitorDispositivoEntrada);

		if (ErrorEntrada != paNoError || ErrorSalida != paNoError)
		{
			MensajeError(ceFalloCierreProcesoAudio);
		}

		/*
		* Se cierran los procesos de audio, este paso es importante 
		* para evitar que el programa empieze a dejar memoria sin
		* usar y crezca sin necesidad.
		*/

		if (cambio_dispositivo == false)
		{
			ErrorEntrada = Pa_CloseStream(FlujoMonitorDispositivoEntrada);

			ErrorSalida = Pa_CloseStream(Flujo);

		}

		cambio_dispositivo = false;

		if (ErrorEntrada != paNoError || ErrorSalida != paNoError)
		{
			MensajeError(ceFalloCierreProcesoAudio);
		}


		FlujoMonitorDispositivoEntrada = NULL;

		Flujo = NULL;

		Error = Pa_Terminate();

		if (Error != paNoError)
		{
			MensajeError(ceFalloCierreEngineAudio);
		}

		BotonDetenerHaSidoPresionado = false;
	}
	else
	{
		Pa_Terminate();
		BotonDetenerHaSidoPresionado = false;
	}
}


void PantallaPrincipal::formatoEtiquetaCanales()
{
	wxString numero1 = LDECanales->GetLabel();
	wxString numero = LDSCanales->GetLabel();
	if (LDECanales->GetLabel() == "6" || LDECanales->GetLabel() == "5.1")
	{
		LDECanales->SetLabel("5.1");
	}
	else if (LDECanales->GetLabel() == "8" || LDECanales->GetLabel() == "7.1")
	{
		LDECanales->SetLabel("7.1");
	}
	else if (LDECanales->GetLabel() == "0")
	{
		LDECanales->SetLabel("0");
	}
	else
	{
		LDECanales->SetLabel("N/S");
	}
	//no se de donde sale el \x
	if (LDSCanales->GetLabel() == "2" || LDSCanales->GetLabel() == "2.0" || LDSCanales->GetLabel() == "\x2")
	{
		LDSCanales->SetLabel("2.0");
	}
	else if (LDSCanales->GetLabel() == "0")
	{
		LDSCanales->SetLabel("0");
	}
	else
	{
		LDSCanales->SetLabel("N/S");
	}
}

void PantallaPrincipal::activarElementosPantallaPrincipal()
{
	cbDispositivoEntrada->Enable(true);
	cbDispositivoSalida->Enable(true);
	btnCodificar->Enable(true);
	btnRefrescar->Enable(true);
	btnDetener->Enable(false);
}

void PantallaPrincipal::desactivarElementosPantallaPrincipal()
{
	cbDispositivoEntrada->Enable(false);
	cbDispositivoSalida->Enable(false);
	btnCodificar->Enable(false);
	btnRefrescar->Enable(false);
	btnDetener->Enable(true);
}

void PantallaPrincipal::abrir_panel_dispositivos_audio()
{
	//Necesita windows.h
	int Error = NULL;
	std::string CadenaComplementaria = { '\\','c','o','n','t','r','o','l','.','e','x','e',' ','m','m','s','y','s','.','c','p','l' };
	const unsigned int TamanoCadena = MAX_PATH;
	TCHAR DireccionDirectorioTemporal[MAX_PATH];
	char DireccionDirectorioSistema[MAX_PATH];

	//MAX_
	GetSystemDirectory(DireccionDirectorioTemporal, TamanoCadena);

	for (int i = 0; i < TamanoCadena; i++)
	{
		DireccionDirectorioSistema[i] = DireccionDirectorioTemporal[i];
	}

	strcat_s(DireccionDirectorioSistema, CadenaComplementaria.c_str());

	//Necesita windows.h
	Error = WinExec(DireccionDirectorioSistema, SW_NORMAL);
	if (Error < 31)
	{
		MensajeError(ceFalloAbrirPanelDispositivoAudio);
	}
}

void PantallaPrincipal::AbrirPanelDispositivosAudio(wxCommandEvent& WXUNUSED(event))
{
	this->abrir_panel_dispositivos_audio();
}



// event handlers
void PantallaPrincipal::CerrarPrograma(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	DesconectarServidorInterno();
	this->Close(true);
}
void PantallaPrincipal::TerminarPrograma(wxCloseEvent& WXUNUSED(event))
{
	DetenerAudio();
	DesconectarServidorInterno();
	//wxDELETE(ServidorInterno);
	delete ServidorInterno;
	CodificadorMatriz->~MatrixEncoder();
	GuardarPerfilVolumen();
	/*delete CodificadorMatriz;
	delete Matriz;
	delete MuestrasdeAudio;*/
	EliminarMonitorDispositivoPredeterminado();
	this->Destroy();
}

void PantallaPrincipal::Minimizar(wxIconizeEvent& WXUNUSED(event))
{
	this->Show(false);
}



void PantallaPrincipal::btnCodificar_clicked(wxCommandEvent& WXUNUSED(event))
{
	Codificar();

}

void PantallaPrincipal::btnRefrescar_clicked(wxCommandEvent& WXUNUSED(event))
{
	Refrescar();
}

void PantallaPrincipal::btnDetener_clicked(wxCommandEvent& WXUNUSED(event))
{
	DetenerAudio();
}

void PantallaPrincipal::cbDispositivoSalida_CambioIndice(wxCommandEvent& WXUNUSED(event))
{
	int IndiceDispositivoSalida = cbDispositivoSalida->GetSelection();
	wxString CanalesSalida, FrecuenciaSalida;
	if (IndiceDispositivoSalida != wxNOT_FOUND)
	{
		DispositivoSalida = ListaDispositivosSalida[IndiceDispositivoSalida].IDdispositivo;
		CanalesSalida << ListaDispositivosSalida[IndiceDispositivoSalida].NumCanales;
		FrecuenciaSalida << ListaDispositivosSalida[IndiceDispositivoSalida].FrecuenciaMuestreo;

		LDSCanales->SetLabel(CanalesSalida);
		LDSFrecuenciaMuestreo->SetLabel(FrecuenciaSalida);

		formatoEtiquetaCanales();
		errorFrecuenciadeMuestreo();
	}
	else if (IndiceDispositivoSalida == wxNOT_FOUND)
	{
		LDSCanales->SetLabel("0");
		LDSFrecuenciaMuestreo->SetLabel("    0");
	}
}

void PantallaPrincipal::abrirFormularioAcerca(wxCommandEvent& WXUNUSED(event))
{
	AcercaFormulario = new FormularioAcerca(this, _("Acerca de este programa"));
	AcercaFormulario->ShowModal();
	AcercaFormulario->Destroy();
	delete AcercaFormulario;
	AcercaFormulario = nullptr;

}

void PantallaPrincipal::abrirFormularioAyuda(wxCommandEvent& WXUNUSED(event))
{
	AyudaFormulario = new FormularioAyuda(this, _("Ayuda de este programa")/*, Idiomaenuso*/);
	AyudaFormulario->ShowModal();
	AyudaFormulario->Destroy();
	delete AyudaFormulario;
	AyudaFormulario = nullptr;
}

void PantallaPrincipal::abrirFormularioControlVolumen(wxCommandEvent& WXUNUSED(event))
{
	abrirFormularioControlVolumen();

}

void PantallaPrincipal::abrirFormularioControlVolumen()
{
	int canalesaprocesar = 0;

	if (LDECanales->GetLabel() == "5.1" || LDECanales->GetLabel() == "6" || LDECanales->GetLabel() == "\x6")
	{
		canalesaprocesar = 6;
	}
	else if (LDECanales->GetLabel() == "7.1" || LDECanales->GetLabel() == "8" || LDECanales->GetLabel() == "\x8")
	{
		canalesaprocesar = 8;
	}

	if (controlVolumen == nullptr && EstadoFormularioControlVolumen == false)
	{
		controlVolumen = new FormularioControlVolumen(this, canalesaprocesar, Idiomaenuso);
		controlVolumen->ShowModal();
	}
	else if(EstadoFormularioControlVolumen == true) //Esta activo
	{
		controlVolumen->SetFocus();
	}
	else if (EstadoFormularioControlVolumen == false)//Hay un formulario que ha sido borrado;
	{
		
		controlVolumen = new FormularioControlVolumen(this, canalesaprocesar, Idiomaenuso);
		controlVolumen->ShowModal();
		
	}

}

void PantallaPrincipal::CambiarIdiomaPrograma(wxCommandEvent& WXUNUSED(event))
{
	wxLanguage LenguajeElejido = wxLANGUAGE_UNKNOWN;
	int Eleccion = NULL;

	RutaArchivoLenguaje = getenv(VaraibleAmbiente.c_str()) + finalRuta + ArchivoLenguaje;


	Eleccion = wxGetSingleChoiceIndex
	(
		_("Por favor elija un idioma:"),
		_("Idiomas disponibles"),
		WXSIZEOF(IdiomasDisponibles),
		IdiomasDisponibles
	);

	if (Eleccion != -1)
	{
		LenguajeElejido = IdiomasSoportados[Eleccion];

		guardarIdiomaenUso((char*)RutaArchivoLenguaje.c_str(), LenguajeElejido);

		wxMessageBox(_("Los cambios se efectuaran despues de que reinicie el programa"), _("Notificacion"), wxICON_INFORMATION);
	}
}

void PantallaPrincipal::ReiniciarSonido()
{
	DetenerAudio();
	InicializarAudio();
}


wxBEGIN_EVENT_TABLE(PantallaPrincipal, wxFrame)
EVT_MENU(ID_ARCHIVO_SALIR, PantallaPrincipal::CerrarPrograma)
EVT_ICONIZE(PantallaPrincipal::Minimizar)
EVT_CLOSE(PantallaPrincipal::TerminarPrograma)
EVT_MENU(ID_AYUDA_ACERCA, PantallaPrincipal::abrirFormularioAcerca)
EVT_MENU(ID_AYUDA_AYUDA, PantallaPrincipal::abrirFormularioAyuda)
EVT_MENU(ID_ABRIR_PANEL_DISPOSITIVOS_AUDIO, PantallaPrincipal::AbrirPanelDispositivosAudio)
EVT_MENU(ID_PANTALLA_CONTROL_VOLUMEN, PantallaPrincipal::abrirFormularioControlVolumen)
EVT_BUTTON(ID_BOTON_CODIFICAR, PantallaPrincipal::btnCodificar_clicked)
EVT_MENU(ID_CAMBIO_IDIOMA, PantallaPrincipal::CambiarIdiomaPrograma)
EVT_BUTTON(ID_BOTON_DETENER, PantallaPrincipal::btnDetener_clicked)
EVT_BUTTON(ID_BOTON_REFRESCAR, PantallaPrincipal::btnRefrescar_clicked)
EVT_COMBOBOX(ID_COMBOBOX_DISPOSITIVO_SALIDA, PantallaPrincipal::cbDispositivoSalida_CambioIndice)
wxEND_EVENT_TABLE()


//////////////ICONO DE BARRA

wxMenu *IconoBarra::CreatePopupMenu()
{
	wxMenu *Menu = new wxMenu;
	Menu->Append(ID_MENU_ABRIR_PANTALLA_PRINCIPAL, _("Abrir Pantalla Principal"));
	Menu->AppendSeparator();
	Menu->Append(ID_MENU_REINICIAR_AUDIO, _("Reiniciar Sonido"));
	Menu->AppendSeparator();
	Menu->Append(ID_MENU_ABRIR_FORUMALRIO_CONTROL_VOLUMEN, _("Control de Volumen"));
	Menu->AppendSeparator();
	Menu->Append(ID_MENU_ABRIR_PANEL_DISPOSITIVOS_AUDIO, _("Abrir Panel Dispositivos de Audio"));
	SubMenuModoVolumen = new wxMenu;
	SubMenuModoVolumen->AppendRadioItem(ID_MENU_MODO_JUEGO, _("Modo Juego"), _("Marque para usar todo el rango dinamico disponible. Los juegos usualmente poseen un rango dinamico o volumen muy alto, esto ayuda a usar todo el rango de un mezcla estero"));
	SubMenuModoVolumen->AppendRadioItem(ID_MENU_MODO_PELICULA, _("Modo Pelicula"), _("Marque para no utilizar la compresion del rango dinamico. Usualmente las peliculas o videos tiene un rango dinamico o volumen menor a los juegos. Use esto modo cuando considere que el volumen de lo que esta reproduciendo es muy bajo"));
	Menu->AppendSeparator();
	Menu->Append(ID_MENU_CAMBIAR_MODO_VOLUMEN, _("Modos de Rango Dinamico"), SubMenuModoVolumen);



#ifdef __WXOSX__ 
	if (OSXIsStatusItem())
#endif
	{
		Menu->AppendSeparator();
		Menu->Append(ID_MENU_CERRAR, _("Cerrar Programa"));
	}
	return Menu;
}

void IconoBarra::MonstrarVentanaPrincipal()
{
	formularioPrincipal->MostrarVentana();
}


void IconoBarra::abrirPantallaPrincipal(wxCommandEvent& WXUNUSED(event))
{
	MonstrarVentanaPrincipal();
}

void IconoBarra::ReiniciarSonido(wxCommandEvent& WXUNUSED(event))
{
	formularioPrincipal->ReiniciarSonido();
}

void IconoBarra::Click_Icono(wxTaskBarIconEvent&)
{
	MonstrarVentanaPrincipal();
}


void IconoBarra::CerrarPrograma(wxCommandEvent& WXUNUSED(event))
{
	formularioPrincipal->Close(true);
}

void IconoBarra::AbrirPanelControlVolumen(wxCommandEvent& WXUNUSED(event))
{
	formularioPrincipal->abrirFormularioControlVolumen();
}

void IconoBarra::AbrirPanelDispositivos_Audio(wxCommandEvent& event)
{
	formularioPrincipal->abrir_panel_dispositivos_audio();
}

void IconoBarra::elegirModoJuego(wxCommandEvent& WXUNUSED(event))
{
	ModoRangoDinamico = false;
	CodificadorMatriz->IncluirCanalBajasFrecuencias(IncluirLFE);
	CodificadorMatriz->FiltrarCanalBajasFrecuencias(FiltrarLFE);
	CodificadorMatriz->comprimirRangoDinamico();
}

void IconoBarra::elegirModoPelicula(wxCommandEvent& WXUNUSED(event))
{
	ModoRangoDinamico = true;
	CodificadorMatriz->eliminarReducciondeRangoDinamico();
}


void IconoBarra::actualizarRadioBotonModoJuego(wxUpdateUIEvent& event)
{
	if (ModoRangoDinamico == false)
	{
		event.Check(true);
	}
	else if (ModoRangoDinamico == true)
	{
		event.Check(false);
	}

}

void IconoBarra::actualizarRadioBotonModoPelicula(wxUpdateUIEvent & event)
{
	if (ModoRangoDinamico == true)
	{
		event.Check(true);
	}
	else if (ModoRangoDinamico == false)
	{
		event.Check(false);
	}
}

wxBEGIN_EVENT_TABLE(IconoBarra, wxTaskBarIcon)
EVT_MENU(ID_MENU_ABRIR_PANTALLA_PRINCIPAL, IconoBarra::abrirPantallaPrincipal)
EVT_MENU(ID_MENU_ABRIR_FORUMALRIO_CONTROL_VOLUMEN, IconoBarra::AbrirPanelControlVolumen)
EVT_MENU(ID_MENU_REINICIAR_AUDIO, IconoBarra::ReiniciarSonido)
EVT_MENU(ID_MENU_CERRAR, IconoBarra::CerrarPrograma)
EVT_MENU(ID_MENU_ABRIR_PANEL_DISPOSITIVOS_AUDIO, IconoBarra::AbrirPanelDispositivos_Audio)
EVT_MENU(ID_MENU_MODO_JUEGO, IconoBarra::elegirModoJuego)
EVT_MENU(ID_MENU_MODO_PELICULA, IconoBarra::elegirModoPelicula)
EVT_UPDATE_UI(ID_MENU_MODO_JUEGO, IconoBarra::actualizarRadioBotonModoJuego)
EVT_UPDATE_UI(ID_MENU_MODO_PELICULA, IconoBarra::actualizarRadioBotonModoPelicula)
EVT_TASKBAR_LEFT_UP(IconoBarra::Click_Icono)
EVT_TASKBAR_LEFT_DCLICK(IconoBarra::Click_Icono)
wxEND_EVENT_TABLE()


//Cliente monitor

ClienteMonitor::ClienteMonitor() : Referencia(1), ptrEnumerador(NULL), IDdispositivoPredeterminado(NULL)
{
	getDefaultAudioEndpointId();
}

ClienteMonitor::~ClienteMonitor()
{
	SAFE_RELEASE(ptrEnumerador);
}

/*
* Optiene el dispositivo predeterminado de audio pero desde la 
* las liberias propias de windows 
*/
HRESULT STDMETHODCALLTYPE ClienteMonitor::getDefaultAudioEndpointId()
{
	HRESULT Resultado = NULL;
	IMMDeviceEnumerator *Enumerador = NULL;
	IMMDevice *Dispositivo = NULL;

	Resultado = CoInitialize(NULL);

	if (SUCCEEDED(Resultado))
	{
		Resultado = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)&Enumerador);

		if (SUCCEEDED(Resultado))
		{
			Resultado = Enumerador->GetDefaultAudioEndpoint(eRender, eMultimedia, &Dispositivo);

			if (SUCCEEDED(Resultado))
			{
				Resultado = Dispositivo->GetId(&IDdispositivoPredeterminado);

				if (SUCCEEDED(Resultado))
				{
					Dispositivo->Release();
					Dispositivo = NULL;
					Enumerador->Release();
					Enumerador = NULL;
				}
				else
				{
					/*No se ha encontrado un dispositivo de audio*/
					IDdispositivoPredeterminado = cm_cadena_vacia;
					Dispositivo->Release();
					Dispositivo = NULL;
					Enumerador->Release();
					Enumerador = NULL;
				}
			}
			else
			{
				/*No se ha encontrado un dispositivo de audio*/
				IDdispositivoPredeterminado = cm_cadena_vacia;
				Dispositivo = NULL;
				Enumerador->Release();
				Enumerador = NULL;
			}
		}
	}

	
	CoUninitialize();
	return Resultado;
}

ULONG STDMETHODCALLTYPE ClienteMonitor::AddRef()
{
	return InterlockedIncrement(&Referencia);
}

ULONG  STDMETHODCALLTYPE ClienteMonitor::Release()
{
	ULONG ulRef = InterlockedDecrement(&Referencia);
	if (0 == ulRef)
	{
		delete this;
	}
	return  ulRef;
}

HRESULT  STDMETHODCALLTYPE ClienteMonitor::QueryInterface(REFIID riid, VOID ** ppvInterface)
{
	if (IID_IUnknown == riid)
	{
		AddRef();
		*ppvInterface = (IUnknown*)this;
	}
	else if (__uuidof(IMMNotificationClient) == riid)
	{
		AddRef();
		*ppvInterface = (IMMNotificationClient*)this;
	}
	else
	{
		*ppvInterface = NULL;
		return E_NOINTERFACE;
	}
	return S_OK;
}

HRESULT  STDMETHODCALLTYPE ClienteMonitor::OnDefaultDeviceChanged(EDataFlow Flujo, ERole Rol, LPCWSTR IdDispositivo)
{
	if (Flujo == eRender && Rol == eMultimedia && wcscmp(IdDispositivo, IDdispositivoPredeterminado) != 0)
	{
		formularioPrincipal->CambioDispositivoPrincipal();
		getDefaultAudioEndpointId();
	}

	return S_OK;
}

HRESULT  STDMETHODCALLTYPE ClienteMonitor::OnDeviceAdded(LPCWSTR)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE  ClienteMonitor::OnDeviceRemoved(LPCWSTR)
{
	return E_NOTIMPL;
}

HRESULT  STDMETHODCALLTYPE ClienteMonitor::OnDeviceStateChanged(LPCWSTR, DWORD)
{
	return E_NOTIMPL;
}

HRESULT   STDMETHODCALLTYPE ClienteMonitor::OnPropertyValueChanged(LPCWSTR, const PROPERTYKEY)
{
	return E_NOTIMPL;
}
