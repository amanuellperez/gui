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


#include "gui_circular_bool.h"

#include <FL/Fl_Radio_Round_Button.H>

namespace gui{

Circular_bool::Circular_bool(const std::string& etiqueta0, bool b0)
    :Widget{new Fl_Radio_Round_Button{0,0, ancho_por_defecto(etiqueta0)
			    , fltk_to_int(Letra::alto())}}
{
    auto wdg = dynamic_cast<Fl_Radio_Round_Button*>(fl_widget());

    etiqueta(etiqueta0);
    wdg->value(b0);
}


int Circular_bool::ancho_por_defecto(const std::string& s)
{ return fltk_to_int(Ancho{s +"xx"}); }



// Devuelve el valor del Check.
bool Circular_bool::valor() const
{
    auto wdg = dynamic_cast<const Fl_Radio_Round_Button*>(fl_widget());
    return wdg->value();
}

// Asignamos b al valor del Check.
void Circular_bool::valor(bool b)
{
    auto wdg = dynamic_cast<Fl_Radio_Round_Button*>(fl_widget());
    wdg->value(b);
}

}
