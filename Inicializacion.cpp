#include "Inicializacion.h"

void CodificadorMatrizTiempoReal::ElegirUnIdioma()
{
	int IdiomadelSistema = NULL;
	short int IdiomaGuardado = NULL;


	RutaArchivoLenguaje = getenv(VaraibleAmbiente.c_str()) + finalRuta + ArchivoLenguaje;
	

	IdiomaGuardado = obtenerIdiomaPrograma((char*)RutaArchivoLenguaje.c_str());

	

	IdiomadelSistema = wxLocale::GetSystemLanguage();

	if (IdiomaGuardado == wxLANGUAGE_DEFAULT)
	{
		IdiomadelSistema = wxLocale::GetSystemLanguage();
	}
	else if (IdiomaGuardado == wxLANGUAGE_UNKNOWN)
	{
		IdiomadelSistema = wxLocale::GetSystemLanguage();
	}
	if (IdiomaGuardado == wxLANGUAGE_ARABIC || IdiomaGuardado == wxLANGUAGE_GERMAN
		|| IdiomaGuardado == wxLANGUAGE_FRENCH || IdiomaGuardado == wxLANGUAGE_ENGLISH
		|| IdiomaGuardado == wxLANGUAGE_SPANISH || IdiomaGuardado == wxLANGUAGE_HINDI
		|| IdiomaGuardado == wxLANGUAGE_PORTUGUESE || IdiomaGuardado == wxLANGUAGE_RUSSIAN
		|| IdiomaGuardado == wxLANGUAGE_CHINESE)
	{
		IdiomadelSistema = IdiomaGuardado;
	}

	if (IdiomadelSistema >= wxLANGUAGE_ARABIC && IdiomadelSistema <= wxLANGUAGE_ARABIC_YEMEN)
	{
		Lenguaje = wxLANGUAGE_ARABIC;
	}
	else if (IdiomadelSistema == wxLANGUAGE_CATALAN || IdiomadelSistema == wxLANGUAGE_VALENCIAN || IdiomadelSistema == wxLANGUAGE_GALICIAN || (IdiomadelSistema >= wxLANGUAGE_SPANISH && IdiomadelSistema <= wxLANGUAGE_SPANISH_VENEZUELA))
	{
		Lenguaje = wxLANGUAGE_SPANISH;
	}
	else if (IdiomadelSistema >= wxLANGUAGE_CHINESE && IdiomadelSistema <= wxLANGUAGE_CHINESE_TAIWAN)
	{
		Lenguaje = wxLANGUAGE_CHINESE;
	}
	else if (IdiomadelSistema >= wxLANGUAGE_ENGLISH && IdiomadelSistema <= wxLANGUAGE_ENGLISH_ZIMBABWE)
	{
		Lenguaje = wxLANGUAGE_ENGLISH;
	}
	else if (IdiomadelSistema >= wxLANGUAGE_FRENCH && IdiomadelSistema <= wxLANGUAGE_FRENCH_SWISS)
	{
		Lenguaje = wxLANGUAGE_FRENCH;
	}
	else if (IdiomadelSistema >= wxLANGUAGE_GERMAN && IdiomadelSistema <= wxLANGUAGE_GERMAN_SWISS)
	{
		Lenguaje = wxLANGUAGE_GERMAN;
	}
	else if (IdiomadelSistema == wxLANGUAGE_HINDI)
	{
		Lenguaje = wxLANGUAGE_HINDI;
	}
	else if (IdiomadelSistema == wxLANGUAGE_PORTUGUESE || IdiomadelSistema == wxLANGUAGE_PORTUGUESE_BRAZILIAN)
	{
		Lenguaje = wxLANGUAGE_PORTUGUESE;
	}
	else if (IdiomadelSistema == wxLANGUAGE_RUSSIAN || IdiomadelSistema == wxLANGUAGE_RUSSIAN_UKRAINE)
	{
		Lenguaje = wxLANGUAGE_RUSSIAN;
	}
	else
	{
		Lenguaje = wxLANGUAGE_ENGLISH;
	}

	Localizacion.Init(Lenguaje, wxLOCALE_DONT_LOAD_DEFAULT);


	wxLocale::AddCatalogLookupPathPrefix("Translation/");

	if(!Localizacion.AddCatalog("MatrixEncoder"))
	{
		Lenguaje = wxLANGUAGE_SPANISH;
	}
}

bool CodificadorMatrizTiempoReal::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	estadoInstancia = new wxSingleInstanceChecker;

	if (estadoInstancia->IsAnotherRunning())
	{
		delete estadoInstancia;
		estadoInstancia = NULL;
		m_Cliente = new Cliente;
		EstadoConexion = m_Cliente->Conectar(IPC_HOST, IPC_SERVICIO, IPC_TOPIC);

		//por si falla la conexion
		if (EstadoConexion == false)
		{
			wxDELETE(m_Cliente);
			if (!wxApp::OnInit())
			{
				return false;
			}
			
			ElegirUnIdioma();

			Ventana = new PantallaPrincipal("Matrix Encoder", Localizacion, Lenguaje);
			this->SetAppName("Matrix Encoder");
			this->SetAppDisplayName("Matrix");
			Ventana->SetIcon(wxICON(Matrix_Encoder_Icon.ico));
			return true;
		}
		else
		{
			wxString Instruccion = wxT("Mostrar");

			if (m_Cliente->EstaConectado())
			{
				m_Cliente->obtenerConexion()->Execute(Instruccion);
				m_Cliente->Desconectar();
			}

			wxDELETE(m_Cliente);
		}

		return false;
	}

	ElegirUnIdioma();

	Ventana = new PantallaPrincipal("Matrix Encoder", Localizacion, Lenguaje);
	this->SetAppName("Matrix Encoder");
	this->SetAppDisplayName("Matrix Encoder");


	Ventana->SetIcon(wxICON(sample));

	return true;
}

PantallaPrincipal * CodificadorMatrizTiempoReal::ObtenerPantallaPrincipal()
{
	return Ventana;
}


//Conexiones

//Cliente
bool ConexionCliente::DoExecute(const void *data, size_t size, wxIPCFormat format)
{
	bool EstadoConexion = wxConnection::DoExecute(data, size, format);
	return EstadoConexion;
}



Cliente::Cliente()
{
	m_ConexionCliente = NULL;
}

Cliente::~Cliente()
{
	Desconectar();
}

bool Cliente::Conectar(const wxString & sHost, const wxString & sService, const wxString & sTopic)
{
	m_ConexionCliente = (ConexionCliente*)MakeConnection(sHost, sService, sTopic);
	return m_ConexionCliente != NULL;
}

void Cliente::Desconectar()
{
	if (m_ConexionCliente)
	{
		m_ConexionCliente->Disconnect();
		wxDELETE(m_ConexionCliente);
	}
}

bool Cliente::EstaConectado()
{
	return m_ConexionCliente != NULL;
}

ConexionCliente * Cliente::obtenerConexion()
{
	return m_ConexionCliente;
}

wxConnectionBase* Cliente::OnMakeConnection()
{
	return new ConexionCliente;
}