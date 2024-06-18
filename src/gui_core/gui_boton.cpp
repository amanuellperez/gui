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


#include "gui_boton.h"

#include <FL/Fl_Button.H>

namespace gui{

// Dejamos el Boton totalmente construido, a falta de colocarlo en una ventana
Boton::Boton(const std::string& etiqueta0, Callback f)
	: Widget{new Fl_Button{0,0
		, fltk_to_int(Ancho{etiqueta0})
		, Cfg::boton_alto}}
	, cb(f)
{
    etiqueta(etiqueta0);

    // Por defecto, al pulsar enter sobre el ratón se llama a click!
    // FLTK no funciona así, sino que por defecto pasa al siguiente widget.
    // auto wdg = dynamic_cast<Fl_Button*>(fl_widget());
    //	wdg->when(FL_WHEN_ENTER_KEY); <--- NO FUNCIONA???
}


void Boton::coloca(Ventana& v, Posicion p)
{
    Widget::coloca(v, p);

    auto wdg = dynamic_cast<Fl_Button*>(fl_widget());
    wdg->callback(reinterpret_cast<Fl_Callback*>(cb), &v);
}


void Boton::coloca(Grupo_de_controles& g)
{
//    Widget::coloca(g); // Widget no hace nada
    auto wdg = dynamic_cast<Fl_Button*>(fl_widget());
    wdg->callback(reinterpret_cast<Fl_Callback*>(cb), &g);
}

void Boton::click() 
{
    auto wdg = dynamic_cast<Fl_Button*>(fl_widget());
    wdg->do_callback();
}

}// namespace 
