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

#ifndef __GUI_VENT_MODAL_H__
#define __GUI_VENT_MODAL_H__

#include <gui_ventana.h>

namespace gui{

/*!
 *  \brief  Es una ventana modal, una ventana que se coloca encima
 *	de las demás y no suelta el foco hasta que se cierra.
 *
 */
class Ventana_modal:public Ventana{
public:
    Ventana_modal(Size sz, const std::string& titulo);

    /// Mostramos la ventana en la posición que la aplicación decida.
    void show() override;

    /// Mostramos la ventana en la posición indicada.
    void show(Coordenada x, Coordenada y) override;
    void show(Posicion p) override {show(p.x, p.y);}

};


inline Ventana_modal::Ventana_modal(Size sz, const std::string& titulo)
	:Ventana{sz, titulo}
{modal();}

inline void Ventana_modal::show(Coordenada x, Coordenada y)
{
    Ventana::show(x, y);
    wait();
}

inline void Ventana_modal::show()
{
    Ventana::show();
    wait();
}

}// namespace

#endif
