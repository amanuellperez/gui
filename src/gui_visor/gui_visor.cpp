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


#include "gui_visor.h"

#include <img_image.h>

namespace gui{


// Dejamos el Visor totalmente construido, a falta de colocarlo en una ventana
Visor::Visor(Size sz)
	: Widget{new Fl_Visor{0,0
		, fltk_to_int(sz.ancho)
		, fltk_to_int(sz.alto)}}
{
    visor()->enlaza(this);
}


// Lo colocamos en la ventana
void Visor::coloca(Ventana& v, Posicion p0)
{
    Widget::coloca(v, p0);

    // por defecto hacemos los visores resizable
    resizable();
}







}// namespace

