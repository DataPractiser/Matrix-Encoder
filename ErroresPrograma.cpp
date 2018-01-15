#include "ErroresPrograma.h"
#include "portaudio.h"


void MensajeError(int CodigoError)
{
	//System::String^ MensajedeError;
	wxString MensajedeError;

	switch (CodigoError)
	{
	case ceDispositivodeEntradaNoCompatible:
		MensajedeError = _("El dispositivo Predeterminado de entrada no es compatible");
		break;

	case ceNumerodeCanalesDispositivoEntradaNoSoportados:
		MensajedeError = _("El numero de canales del dispositivo de audio no es compatible");
		break;

	case ceFrecuenciasdeMuestreoNoIguales:
		MensajedeError = _("La frecuencias de muestreo de los dispositivos de audio deben ser iguales");
		break;

	case ceDispositivodeSalidaNoEncontrado:
		MensajedeError = _("Se cambio o elimino el dispositivo de Salida usado durante la ultima Ejecucion");
		break;

	case ceDispositivoSalidaNODisponible:
		MensajedeError = _("Este dispositivo de audio no se encuentra disponible o hubo cambios en los dispositivos de audio");
		break;

	case ceExcesoDispositivosAudio:
		MensajedeError = _("Hay demasiados dispositivos de audio en el sistema, desactive los que no use");
		break;

	case ceNoDispositivosEnElEQuipo:
		MensajedeError = _("No hay dispositivos de audio compatibles en el sistema, instalelos o activelos por favor");
		break;

	case ceNoDispositivoCon2canalesdeSalida:
		MensajedeError = _("No se encontraron dispositivos con 2 canales de Salida, configure alguno y presione el boton Refrescar");
		break;

	case ceNumerodeCanalesNoSoportado:
		MensajedeError = _("El numero de canales del dispositivo de audio no es compatible");
		break;

	case ceNingunDispositivodeAudioSeleccionado:
		MensajedeError = _("Ningun dispositivo de Entrada o Salida ha sido seleccionado");
		break;

	case ceNoDispositivoEntradaSeleccionado:
		MensajedeError = _("El dispositivo de Predeterminado no esta configurado en modo 5.1 o 7.1");
		break;

	case ceNoDispositivoSalidaSeleccionado:
		MensajedeError = _("No se ha seleccionado un dispositivo de Salida");
		break;

	case ceErrorProcesarAudio:
		MensajedeError = _("Error al procesar el audio");
		break;

	case ceFalloAbrirPanelDispositivoAudio:
		MensajedeError = _("No se pudo abrir el panel de dispositivos de audio");
		break;

	case ceFalloCierreProcesoAudio:
		MensajedeError = _("No se pudo cerrar el proceso de audio");
		break;

	case ceFalloCierreEngineAudio:
		MensajedeError = _("No se pudo cerrar el Engine de audio");
		break;

	case paInvalidDevice:
		MensajedeError = _("Dispositivo no compatible, elija otro por favor");
		break;

	case ceCambioFrecuenciaMuestreoDispositivoPredeterminado:
		MensajedeError = _("Cambio la frecuencia de muestreo del dispositivo predeterminado");
		break;

	case ceCambioFrecuenciaMuestreoDispositivoSalida:
		MensajedeError = _("Cambio la frecuencia de muestreo del dispositivo de salida");
		break;

	case ceCambioNumeroCanaelesDispositivoSalida:
		MensajedeError = _("Cambio el numero de canales del dispositivo de salida");
		break;

	default:
		MensajedeError = _("Codigo de error no existente");
		break;
	}

	if (CodigoError > 0  && CodigoError <= ceCambioNumeroCanaelesDispositivoSalida)
	{
		wxMessageBox(MensajedeError, _("Advertencia"), wxICON_WARNING);
	}
}