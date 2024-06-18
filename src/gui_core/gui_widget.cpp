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


#include "gui_widget.h"
#include "gui_ventana.h"

#include <alp_cast.h>


using namespace std;



namespace gui{

Size Widget::fltk_measure_label() const
{
    if(etiqueta().empty()){
	cerr << "Estas intentando calcular la longitud de una cadena 0!\n"
		"Posiblemente sea un error\n";
	return Size{0_pix,0_pix};
    }

    // FUNDAMENTAL: inicializarlo a 0 y llamar a fl_font!!!
    int ancho = 0, alto = 0;
    fl_font(w_->labelfont(), w_->labelsize());
    w_->measure_label(ancho, alto);
    
    // El +10 procede por prueba y error (Luego lo he encontrado en la 
    // página de Ercolano). Es el margen que le deja FLTK
    // Cotillear la función fl_draw, para ver cómo dibuja las etiquetas
    return Size{Ancho::en_pix(alp::narrow_cast<unsigned>(ancho)+10)
	, Alto::en_pix(alp::narrow_cast<unsigned>(alto)+10)};
}


// coloca el widget en la ventana v, en la posición p0
// Este widget tiene que estar creado
void Widget::coloca(Ventana& v, Posicion p)
{
    alp::precondicion(w_ != nullptr
		, __FILE__, __LINE__, "Widget::coloca"
			  , "Intentando colocar un widget no creado!!!");

    v_ = &v;
    v_->add(w_);    // lo añadimos al grupo

    // Lo colocamos. OJO: no puedo llamar a p0, ya que es virtual, y es el 
    // principio del widget, pero fltk coloca un Input_xxx donde empieza el 
    // Input, no donde empieza el widget
    w_->position(p.x.pix(), p.y.pix());
//    p0(p);	    // lo recolocamos
}




void Widget::resizable() 
{
    alp::precondicion(v_ != nullptr, 
	    __FILE__, __LINE__, "Widget::resizable"
	    , "No se puede llamar a resizable hasta que no se haya colocado "
		"el widget en una ventana");

    v_->resizable(w_);
}    




/***************************************************************************
 *			    FUNCIONES AUXILIARES
 ***************************************************************************/
// Redimensiona el ancho de los dos widgets al de mayor ancho.
void mismo_ancho_mayor(Widget& w1, Widget& w2)
{
    auto a = std::max(w1.ancho(), w2.ancho());

    w1.ancho(a);
    w2.ancho(a);
}

// Redimensiona el alto de los dos widgets al de mayor alto.
void mismo_alto_mayor(Widget& w1, Widget& w2)
{
    auto h = std::max(w1.alto(), w2.alto());

    w1.alto(h);
    w2.alto(h);
}


}// namespace gui

