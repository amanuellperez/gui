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


#include "gui_tipos.h"
#include "gui_fl.h"

#include <string>

#include <FL/Fl_Box.H>

using alp::narrow_cast;

namespace gui{


// dimensiones por defecto de los botones
int Cfg::boton_alto = 40;
// int Cfg::boton_alto = alto_en_pixeles(1)*1.5;

// en pixeles!!!
unsigned Cfg::menu_alto = 25; //Cfg::letra_alto;
int Cfg::linea_de_texto_alto = 25; //Cfg::letra_alto;




// Voy a usar el truco de usar Fl_Box para medir la longitud. Por supuesto,
// que esto solo vale mientras solo use un tipo de fuente en todas las
// ventanas y controles.
namespace local{
static Fl_Box box{0,0,0,0};
}

// TODO: que se le pase el font???
unsigned Alto::alto_en_pixeles(unsigned num_lineas)
{
    const std::string s = "A";   // calculamos la altura de la letra A

    // FUNDAMENTAL: inicializarlo a 0 y llamar a fl_font!!!
    int w = 0, h = 0;
    fl_font(local::box.labelfont(), local::box.labelsize());
    fl_measure(s.c_str(), w, h, 0);

    // El +10 procede por prueba y error (Luego lo he encontrado en la 
    // página de Ercolano). Es el margen que le deja FLTK
    // Cotillear la función fl_draw, para ver cómo dibuja las etiquetas
    return num_lineas*(narrow_cast<unsigned>(h)+8);
}


// TODO: que se le pase el font???
unsigned Ancho::ancho_en_pixeles(const std::string& s)
{
    // TODO: cuando se quiera crear una etiqueta vacía, crearla como
    //	Etiqueta = Etiqueta::vacia(); <--- de esta forma el programador
    //	tiene que hacerlo explícitamente y no define una etiqueta vacía por
    //	error.
    if(s.empty()){
//	cerr << "Estas intentando calcular la longitud de una cadena 0!\n"
//		"Posiblemente sea un error\n";
	return 0;
    }

    // FUNDAMENTAL: inicializarlo a 0 y llamar a fl_font!!!
    int w = 0, h = 0;
    fl_font(local::box.labelfont(), local::box.labelsize());
    fl_measure(s.c_str(), w, h, 0);

    // El +10 procede por prueba y error (Luego lo he encontrado en la 
    // página de Ercolano). Es el margen que le deja FLTK
    // Cotillear la función fl_draw, para ver cómo dibuja las etiquetas
    return (narrow_cast<unsigned>(w)+8);
}

}// namespace gui
