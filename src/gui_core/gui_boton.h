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
#ifndef __GUI_BOTON_H__
#define __GUI_BOTON_H__

#include "gui_widget.h"

namespace gui{
/*!
 *  \brief  Es un pulsador (al pulsar se ejecuta una acción).
 *
 *  A través de los botones el usuario de la aplicación ejecuta funciones
 *  del programa.
 *
 *  Ejemplo:
 *  \code
 *	    gui::Boton bt_graba{"&Graba", cb_graba};
 *
 *	    // callbacks
 *	    static void cb_graba(void*, void* ventana)
 *	    { static_cast<Ventana_plano_intensidad*>(ventana)->graba(); }
 *   
 *	    void graba();
 *  \endcode
 */
class Boton:public Widget{
public:
    explicit Boton(const std::string& etiqueta, Callback f);

    /// Colocamos el widget en la ventana v en la posición p.
    void coloca(Ventana& v, Posicion p) override;

    /// Le indicamos al boton que lo hemos colocado en este grupo de controles.
    void coloca(Grupo_de_controles& g) override;

    // Al introducir coloca, perdemos coloca del Widget. Los recuperamos:
    void coloca(Coordenada x, Coordenada y) override {Widget::coloca(x, y);}
    void coloca(Posicion p)			{Widget::coloca(p);}

    /// Pulsamos el botón. Equivalente a que el usuario pulse el botón.
    void click();

    /// Cambiamos la etiqueta del botón
    void etiqueta(const std::string& et){Widget::etiqueta(et);}

private:
    Callback cb;

};


}// namespace

#endif



