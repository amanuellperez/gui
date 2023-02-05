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

#ifndef __GUI_BOTON_DOBLE_H__
#define __GUI_BOTON_DOBLE_H__

#include "gui_widget.h"
#include "gui_grupo_de_controles.h"
#include "gui_boton.h"

namespace gui{
/*!
 *  \brief  Un botón doble son dos botones colocados en el mismo sitio.
 *	Al pulsar, se cambia de un botón al otro, ejecutándose cosas 
 *	diferentes.
 *
 */
class Boton_doble:public Grupo_de_controles{
public:
    /// Construye en boton doble, perteneciente a la ventana v.
    ///
    /// El botón 1 es {boton1, f1}, mientras que el 2 es {boton2, f2}.
    Boton_doble( Ventana* v
		, const std::string& boton1,  Callback f1
		, const std::string& boton2,  Callback f2);

private:
    Boton bt1_;
    Boton bt2_;
    
    // TODO: en lugar de callbacs serían mejor functores.
    Ventana* v_;    // Ventana a la que pertenecen los dos botones
    Callback cb1_;
    Callback cb2_;

    Size coloca_childs(Posicion p) override;

    // callbacks
    static void cb_click_boton1(void*, void* boton)
    { static_cast<Boton_doble*>(boton)->click_boton1(); }
    
    void click_boton1();

    static void cb_click_boton2(void*, void* boton)
    { static_cast<Boton_doble*>(boton)->click_boton2(); }
    
    void click_boton2();
};

}// namespace

#endif 

