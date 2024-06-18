// Copyright (C) 2020 Manuel Perez <manuel2perez@proton.me>
//
// This file is part of the ALP Library.
//
// ALP Library is a free library: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#pragma once

#ifndef __GUI_VENT_PREGUNTA_SINO_H__
#define __GUI_VENT_PREGUNTA_SINO_H__

#include <gui_boton.h>
#include <gui_etiqueta.h>

#include "gui_vent_modal.h"

namespace gui{

/*!
 *  \brief  Ventana que hace una pregunta de sí o no al usuario.
 *
 *  Esto es, la pregunta solo tiene dos posibles respuestas: o sí o no.
 *  Por ello en lugar de un Input donde escribir, se dan dos botones: sí/no.
 *  
 *  Ejemplo:
 *  \code 
 *	Ventana_pregunta_sino v{"Pregunta", "¿Quieres salir?"};
 *	v.show(100, 100);
 *	if(v.ha_respondido_si())
 *	    cout << "Quiere salir!\n";
 *	else
 *	    cout << "No quiere salir!\n";
 *
 *  \endcode
 *
 *  \see Ventana_pregunta
 */
class Ventana_pregunta_sino:public Ventana_modal{
public:
    /// Construye una ventana pregunta del 'título' indicado, preguntando
    /// la 'pregunta' correspondiente. Opcionalmente se le pueden dar nombres
    /// diferentes a los botones Sí/No.
    Ventana_pregunta_sino( const std::string& titulo
		, const std::string& pregunta
		, const std::string& et_si = "&Sí"
		, const std::string& et_no = "&No");

    ~Ventana_pregunta_sino() {}

    /// Indica si el usuario ha respondido que sí.
    bool ha_respondido_si() const {return respuesta_;}

    /// Indica si el usuario ha respondido que no.
    bool ha_respondido_no() const {return !ha_respondido_si();}

private:
    // TODO: que admita varias lineas de texto!!! (máximo 3)
//    Texto pregunta_;
    Etiqueta pregunta_;
    Boton bt_si_;
    Boton bt_no_;
    bool respuesta_ = false;

    static void cb_si(void*, void* ventana)
    {static_cast<Ventana_pregunta_sino*>(ventana)->si_click();}

    static void cb_no(void*, void* ventana)
    {static_cast<Ventana_pregunta_sino*>(ventana)->no_click();}

    void si_click() { respuesta_ = true; hide(); }
    void no_click() { respuesta_ = false; hide();}
};


/// Muestra una ventana al usuario preguntándole la 'pregunta', pregunta
/// que solo puede tener dos posibles respuestas: sí/no.
///
/// \return Devuelve true si el usuario responde 'sí', y false si responde
/// 'no'.
inline bool pregunta_sino( const std::string& titulo
	    , const std::string& pregunta
	    , Posicion p0 = Posicion{100_pix, 100_pix})
{
    Ventana_pregunta_sino v{titulo, pregunta};

    v.show(p0);

    return v.ha_respondido_si();
}


inline bool pregunta_sino( const std::string& pregunta
	    , Posicion p0 = Posicion{100_pix, 100_pix})
{ return pregunta_sino("", pregunta, p0); }



}// namespace

#endif
