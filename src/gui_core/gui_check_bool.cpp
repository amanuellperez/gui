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


#include "gui_check_bool.h"

#include <FL/Fl_Check_Button.H>

namespace gui{

Check_bool::Check_bool(const std::string& etiqueta0, bool b)
	: Widget{new Fl_Check_Button{0,0, ancho_por_defecto(etiqueta0),
			fltk_to_int(Letra::alto())}}
{ 
    etiqueta(etiqueta0);
    valor(b);
}


// Devuelve el valor del Check.
bool Check_bool::valor() const
{
    auto wdg = dynamic_cast<const Fl_Check_Button*>(fl_widget());
    return wdg->value();
}

// Asignamos b al valor del Check.
void Check_bool::valor(bool b)
{
    auto wdg = dynamic_cast<Fl_Check_Button*>(fl_widget());
    wdg->value(b);
}


// Al cotillear el código de Fl_Check_Button, da la impresión de que
// asigna 1 caracter al tamaño del cuadradito. Por eso le añado un
// caracter a la etiqueta (no valdría devolver +1 ya que ese 1 sería un
// pixel!!!)
int Check_bool::ancho_por_defecto(const std::string& s)
{
    if(s.length() != 0)
	return fltk_to_int(Ancho{s +"x"});
    else
	return fltk_to_int(Ancho{"xx"});
}

}// namespace
