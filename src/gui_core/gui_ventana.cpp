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


#include "gui_ventana.h"

#include "gui_tipos.h"

namespace gui{
// coloco la ventana en la posición (10,10), que es la posición inicial
// de todas las ventanas.  En principio, el idioma es que se llame siempre
// a show(p0) la primera vez que se quiere mostrar la ventana, así que no 
// debería de usarse nunca esta (10,10), pero al dar un show() admito que
// el cliente no quiera colocar la ventana inicialmente.
Ventana::Ventana(Size sz, const std::string& ttitulo)
    :v{std::make_unique<Fl_Ventana>(this
			, 10, 10, fltk_to_int(sz.ancho), fltk_to_int(sz.alto))}
{
    titulo(ttitulo);
    v->end();   // fundamental, para que FLTK no agregue todos 
		// los widgets y ventanas que incluya dentro de la 
		// definición de Ventana!!!
}

void Ventana::show(Coordenada x, Coordenada y)
{
    p0(x,y);
    show();
}


// TRUCO: si llamo exit(0), no se llaman los destructores de los objetos
// creados, lo cual no es buena cosa. Para llamarlos y que el programa se
// cierre de forma controlada lanzo una excepción que capturo en gui_main,
// siendo totalmente trasparente al usuario. De esta forma se cierra el
// programa de forma ordenada.
void Ventana::cb_exit(Fl_Widget*, void*)
{
    throw impl::Fin_programa{};
}


}// namespace
