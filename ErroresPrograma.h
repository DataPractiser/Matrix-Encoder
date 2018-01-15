
#ifndef __ERRORESPROGRAMA_H_INCLUDED__
#define __ERRROESPROGRAMA_H_INCLUDED__

#include <math.h>
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

//Hay varios errores que no se da soporte port audio que son necesarios para este programa
//aqui estan contenidos
enum CodigosdeError
{
	ceDispositivodeEntradaNoCompatible = 1,

	ceNumerodeCanalesDispositivoEntradaNoSoportados,

	ceFrecuenciasdeMuestreoNoIguales,

	ceDispositivodeSalidaNoEncontrado,

	ceDispositivoSalidaNODisponible,

	ceExcesoDispositivosAudio,

	ceNoDispositivosEnElEQuipo,

	ceNoDispositivoCon2canalesdeSalida,

	ceNumerodeCanalesNoSoportado,

	ceNingunDispositivodeAudioSeleccionado,

	ceNoDispositivoEntradaSeleccionado,

	ceNoDispositivoSalidaSeleccionado,

	ceErrorProcesarAudio,

	ceFalloAbrirPanelDispositivoAudio,

	ceFalloCierreProcesoAudio,

	ceFalloCierreEngineAudio,

	ceCambioFrecuenciaMuestreoDispositivoPredeterminado,

	ceCambioFrecuenciaMuestreoDispositivoSalida,

	ceCambioNumeroCanaelesDispositivoSalida
};

void MensajeError(int CodigoError);
#endif

