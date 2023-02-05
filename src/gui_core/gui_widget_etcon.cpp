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


#include "gui_widget_etcon.h"


namespace gui{

// OJO: A Fl_Input se le pasa el ancho del input, no de la label!!!
Widget_etcon::Widget_etcon ( Fl_Widget* widget
		    , const std::string& etiqueta0
		    , Ancho input_ancho )
	:Widget{widget}
	, ancho_{0_pix}
	, et_ancho_{etiqueta0}
{
    define(etiqueta0, input_ancho);
}


void Widget_etcon::define(const std::string& etiqueta0, Ancho input_ancho)
{
    et_ancho_ = Ancho{etiqueta0};
    ancho_ = et_ancho_ + input_ancho;
    etiqueta(etiqueta0);
}



// Colocamos el widget en la ventana v
// Comentarios: A Fl_Input se le pasa la posición de input, no de la etiqueta. 
// Así que hay que recalcular la posición (x0,y0) que se le pasa a coloca
void Widget_etcon::coloca(Ventana& v, Posicion p)
{
    x0_ = p.x;

    Widget::coloca(v, Posicion{x0_+ et_ancho_, p.y});
}


// p = posición del input
// A Fl_Input se le pasa la posición de input, no de la etiqueta. 
// Así que hay que recalcular la posición (x0,y0) que se le pasa a coloca
void Widget_etcon::coloca_input(Ventana& v, Posicion p)
{
    Widget::coloca(v, p);
    // fl_widget()->position(p.x(), p.y());

    // posición en la que empieza el widget = etiqueta + input
    x0_ = p.x - et_ancho_;
}

}// namespace
