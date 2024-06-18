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


#include "gui_boton_bool.h"

#include <FL/Fl_Button.H>

namespace gui{

Boton_bool::Boton_bool(const std::string& etiqueta0, bool b)
	: Widget{new Fl_Button{0,0
		, fltk_to_int(Ancho{etiqueta0})
		, Cfg::boton_alto}}
{ 
    etiqueta(etiqueta0);

    valor(b);

    // Esto hace que al pulsar el botón se quede pulsado.
    auto wdg = dynamic_cast<Fl_Button*>(fl_widget());
    wdg->type(FL_TOGGLE_BUTTON);
}



// Devuelve el valor del Check.
bool Boton_bool::valor() const
{
    auto wdg = dynamic_cast<const Fl_Button*>(fl_widget());
    return wdg->value();
}

// Asignamos b al valor del Check.
void Boton_bool::valor(bool b)
{
    auto wdg = dynamic_cast<Fl_Button*>(fl_widget());
    wdg->value(b);
}


}// namespace
