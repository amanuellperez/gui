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

#ifndef __GUI_VENT_MENSAJE_AVISO_H__
#define __GUI_VENT_MENSAJE_AVISO_H__

#include <gui_base.h>
#include <gui_boton.h>
#include <gui_etiqueta.h>

#include "gui_vent_modal.h"

namespace gui{

/*!
 *  \brief Muestra un mensaje de aviso al usuario.
 *
 */
class Ventana_mensaje_aviso:public Ventana_modal{
public:
    /// Construye una ventana con el título indicado, mostrando el 
    /// mensaje msg al usuario. Opcionalmente se le puede pasar la
    /// etiqueta que muestra el botón OK.
    Ventana_mensaje_aviso( const std::string& titulo
			 , const std::string& msg
			 , const std::string& et_boton = "&OK");

    ~Ventana_mensaje_aviso() {}

private:
    Etiqueta aviso_;
    Boton bt_ok_;

    static void cb_ok(void*, void* ventana)
    {static_cast<Ventana_mensaje_aviso*>(ventana)->ok();}

    void ok() { hide(); }
};


}// namespace gui

#endif
