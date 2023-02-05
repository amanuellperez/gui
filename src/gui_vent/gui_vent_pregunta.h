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

#ifndef __GUI_VENT_PREGUNTA_H__
#define __GUI_VENT_PREGUNTA_H__

#include <gui_boton.h>
#include <gui_input_string.h>

#include "gui_vent_modal.h"

namespace gui{

/*!
 *  \brief  Es una ventana que sirve para preguntar algo, donde el 
 *	usuario tiene que responder escribiendo la respuesta en un Input.
 *   
 *   El usuario puede responder a la pregunta o cancelar.
 *
 *   Ejemplo:
 *   \code
 *	Ventana_pregunta v{"Nombre fichero:", "Grabando..."};
 *
 *	v.show();
 *	if(v.ha_respondido()){
 *	    auto nombre_fichero = v.respuesta();
 *	    visor.write(nombre_fichero);
 *	    cout << "Fichero " << nombre_fichero << " guardado" << endl;
 *	}
 *  \endcode
 *
 *  \see pregunta, Ventana_pregunta_sino
 *
 ***************************************************************************/
class Ventana_pregunta:public Ventana_modal{
public:
    Ventana_pregunta( const std::string& titulo 
		    , const std::string& pregunta);
 
    /// Indica si el usuario ha respondido la pregunta.
    bool ha_respondido() const {return ha_respondido_;}

    /// Indica si el usuario ha cancelado, no respondiendo.
    bool ha_cancelado() const {return !ha_respondido();}

    /// Devuelve la respuesta escrita por el usuario.
    std::string respuesta() const{return input();}

private:
    Input_string input;//{"Error: Falta inicializar!!!", 100};
    Boton bt_aceptar{"&Aceptar", cb_aceptar};
    Boton bt_cancelar{"&Cancelar", cb_cancelar};

    // indica si el usuario pulsa aceptar o cancelar
    bool ha_respondido_ = false;

    static void cb_aceptar(void*, void* ventana)
    { static_cast<Ventana_pregunta*>(ventana)->aceptar(); }

    void aceptar() 
    {
	if(!input().empty()) ha_respondido_ = true; 
	hide();
    }

    static void cb_cancelar(void*, void* ventana)
    { static_cast<Ventana_pregunta*>(ventana)->cancelar(); }

    void cancelar() {ha_respondido_ = false; hide();}
};


/*!
 *  \brief  Abre una ventana pregunta, preguntando la pregunta pasada 
 *	como parámetro.
 *
 *  Ejemplo mínimo:
 *	\code 
 *	    string respuesta;
 *	    bool ha_respondido;
 *	    tie(ha_respondido, respuesta) 
 *		    = pregunta("¿Qué quieres responder?", "Mi pregunta");
 *
 *	    if(ha_respondido)
 *		cout << "Has respondido [" << respuesta << "]\n";
 *	    else
 *		cout << "Cancelaste\n";
 *	\endcode
 *
 *  \see Ventana_pregunta
 *
 *  \todo Gestionar de forma automática la posición inicial de esta ventana.
 *	¿Si el usuario no pasa la posición que la calcule de alguna forma?
 *
 *
 */
inline std::pair<bool, std::string> 
pregunta( const std::string& titulo
	    , const std::string& pregunta
	    , Posicion p0 = Posicion{100_pix, 100_pix})
{
    Ventana_pregunta v{titulo, pregunta};

    v.show(p0);

    return {v.ha_respondido(), v.respuesta()};
}


}// namespace

#endif 
