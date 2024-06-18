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


#include "gui_grupo_de_controles.h"


using namespace std;

using alp::split_lineas_ancho;
using alp::num_lineas;

namespace gui{

/***************************************************************************
 *				TEXTO
 ***************************************************************************/
Varias_lineas::Varias_lineas(const std::string& s, Size sz)
    :Texto{new Fl_Multiline_Output{0,0
	    //, fltk_to_int(ancho_en_pixeles(sz.ancho))
	    , fltk_to_int(sz.ancho)
	    , fltk_to_int(sz.alto)}}
{
    texto(s);

    // TODO: usar Texto.align(); 
    w()->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);

//  borde(Tipo_borde::solido); <-- mejor???
}

// a = número máximo de caracteres de ancho de cada línea
// OJO: a no es un Ancho!!! Es un ancho pero no de GUI!!!
Varias_lineas::Varias_lineas(const std::string& txt 
	    , unsigned a, alp::Maximo<unsigned> h)
    :Varias_lineas{txt, Size{Ancho::en_car(a), Alto::en_pix(h)}}
{
    // redimensionamos de forma adecuada
    std::string msg = split_lineas_ancho(txt, a);

    texto(msg);
    
    alto(min(Alto::en_pix(num_lineas(msg)), Alto::en_pix(h)));
}


/***************************************************************************
 *			    GRUPO_DE_CONTROLES
 ***************************************************************************/
Grupo_de_controles::Grupo_de_controles(const std::string& titulo)
    :Widget(new Fl_Group{0,0, 10, 10})
    , titulo_{titulo}
{
    Fl_Group* g = dynamic_cast<Fl_Group*>(w_);

    // no permito que se añadan por defecto widgets a este grupo.
    // Fltk los añade, lo cual hace que se comporte de forma rara
    // si creo los controles dentro de una ventana. Todos los controles
    // definidos después de un grupo, se añaden automáticamente!!!
    g->end();

    // por defecto, al redimensionar el grupo no admito que se redimensionen
    // Eso es lo que necesito para las Opciones. 
    // TODO: mejorar: crear la función resizable(true/false) publica
    g->resizable(NULL);   

    // si nos pasan título, lo añadimos
    if(!titulo.empty())
	fltk_add(titulo_);
}

// Esto es syntactic sugar
void Grupo_de_controles::fltk_add(Widget& w)
{
    Fl_Group* g = dynamic_cast<Fl_Group*>(w_);

    // lo añadimos al grupo de fltk
    g->add(w.w_);	
}


void Grupo_de_controles::push_back(Widget& w)
{
    // lo añadimos al grupo de fltk
    fltk_add(w);

    // lo añadimos como hijo
    child_.push_back(&w);

    // le indicamos al widget que lo hemos colocado en el grupo
    w.coloca(*this);
}


void Grupo_de_controles::coloca(Ventana& v, Posicion p)
{
    Widget::coloca(v, p);

    if(tiene_titulo())
	coloca_con_el_titulo(p);
    else
	coloca_sin_el_titulo(p);
}

// Colocamos el grupo, añadiéndole el título
void Grupo_de_controles::coloca_con_el_titulo(Posicion p)
{
    // La primera línea del grupo es el título, el resto los childs
    //titulo_.p0(p); BORRAR 27/12/17
    titulo_.coloca(p);

    p += {0_pix, titulo_.alto()};

    auto sz_childs = coloca_childs(p);

    // redimensionamos el título o el grupo al ancho mayor
    auto ancho = max(sz_childs.ancho, titulo_.ancho());
    titulo_.ancho(ancho);

    // marcamos el grupo con el tamaño adecuado
    size(ancho, sz_childs.alto + titulo_.alto());
}

// Colocamos el grupo, sin ningún título
void Grupo_de_controles::coloca_sin_el_titulo(Posicion p)
{
    auto sz = coloca_childs(p);

    size(sz.ancho, sz.alto);
}


/***************************************************************************
 *			    GRUPO HORIZONTAL
 ***************************************************************************/
Grupo_horizontal::Grupo_horizontal(const std::string& titulo)
    :Grupo_de_controles{titulo}
{
}

Ancho Grupo_horizontal::ancho_grupo() const
{
    Ancho s = 0_pix;
    for(auto child: *this)
	s += child->ancho();

    return s;
}

Alto Grupo_horizontal::alto_grupo() const
{
    // DUDA: ¿En lugar de precondición, devolver el alto de una letra?
    alp::precondicion(size() > 0
	    , __FILE__, __LINE__, "Grupo_horizontal::alto_grupo"
	    , "Has definido un Grupo_horizontal sin widgets!!! Vacío. "
	      "Hay que llamar a la función push_back en el constructor"
	      " (antes de colocar el grupo)");

    // El alto del grupo será el alto del widget más grande
    Alto M = 0_pix;
    for(auto child: *this)
	if(M < child->alto())
	    M = child->alto();

    return M;
}

Size Grupo_horizontal::coloca_childs(Posicion pa)
{
    // pa = posición actual donde colocamos el siguiente widget
    for(auto child: *this){
	// child->p0(pa);
	child->coloca(pa);
	pa += {child->ancho(), 0_pix};
    }

    return Size{ancho_grupo(), alto_grupo()};
}




/***************************************************************************
 *			    GRUPO VERTICAL
 ***************************************************************************/
Grupo_vertical::Grupo_vertical(const std::string& titulo)
    :Grupo_de_controles{titulo}
{
}

Ancho Grupo_vertical::ancho_grupo() const
{
    // DUDA: ¿En lugar de precondición, devolver el alto de una letra?
    alp::precondicion(size() > 0
	    , __FILE__, __LINE__, "Grupo_vertical::ancho_grupo"
	    , "Has definido un Grupo_vertical sin widgets!!! Vacío. "
	      "Hay que llamar a la función push_back en el constructor"
	      " (antes de colocar el grupo)");

    // El ancho del grupo será el ancho del widget más grande
    Ancho M = 0_pix;
    for(auto child: *this)
	if(M < child->ancho())
	    M = child->ancho();

    return M;
}

// el alto es la suma de todos los altos + el margen entre lineas
Alto Grupo_vertical::alto_grupo() const
{
    Alto s = 0_pix;
    for(auto child: *this)
	s += child->alto() + margen_entre_lineas();

    return s;
}

// Precondición: los childs del grupo se han añadido al grupo
Size Grupo_vertical::coloca_childs(Posicion pa)
{
    // pa = posición actual donde colocamos el siguiente widget
    for(auto child: *this){
	// child->p0(pa);
	child->coloca(pa);
	pa += {0_pix, child->alto() + margen_entre_lineas()};
    }

    return Size{ancho_grupo(), alto_grupo()};
}




}// namespace gui
