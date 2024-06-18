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


#pragma once

#ifndef __GUI_ETIQUETA_H__
#define __GUI_ETIQUETA_H__
/****************************************************************************
 *
 *   - DESCRIPCION: Widgets para mostrar texto
 *
 *   - HISTORIA:
 *           alp  - 15/08/2017 Reestructurado
 *
 ****************************************************************************/
#include "gui_widget.h"
#include "gui_ventana.h"

#include <FL/Fl_Box.H>
#include <FL/Fl_Multiline_Output.H>

namespace gui{

/*!
 *  \brief  Es el widget que usamos para mostrar mensajes al usuario.
 *
 *  Es una clase abstracta, padre de:
 *
 *  Etiqueta: una o dos palabras.
 *
 *  Linea: una línea de texto.
 *
 *  Varias_lineas: varías líneas de texto.
 *
 *  \see Etiqueta, Linea, Varias_lineas.
 *
 *  \todo De momento no implemento funcionalidad. Añadir: align y cuestiones
 *  de formato (tipo de letra? color? ...?)
 *
 */
class Texto:public Widget{
public:
    using Widget::Widget;
    
};


/*!
 *  \brief  Es una std::string de solo lectura para el usuario,
 *	    pero de lectura/escritura para el programador.
 *
 *  Aunque en principio no hay límite de longitud, una etiqueta se concibe
 *  como una o dos palabras (una string pequeña). Son útiles para ponerle
 *  mensajes al usuario.
 *
 */
class Etiqueta:public Texto{
public:
    // TODO: cuando se quiera crear una etiqueta vacía, crearla como
    //	Etiqueta = Etiqueta::vacia(); <--- de esta forma el programador
    //	tiene que hacerlo explícitamente y no define una etiqueta vacía por
    //	error.
    Etiqueta(const std::string& s = "");

    /// Escribimos en la etiqueta un const char*
    // Etiqueta& operator=(const char* c) {return (*this = std::string{c});}
    void operator=(const char* c) {*this = std::string{c};}

    /// Escribimos en la etiqueta una string.
    // Etiqueta& operator=(const std::string& s);
    void operator=(const std::string& s);

    // escribimos TODO: eliminar estas dos a favor de =!!!
    void texto(const std::string& s) { etiqueta(s);}
    void texto(int i) { texto(alp::to<std::string>(i));}

    /// Leemos el contenido de la etiqueta.
    /// TODO: eliminar esta función
    std::string operator()() const {return etiqueta();}

    // volcamos el contenido en el widget
    void flush() {Widget::flush();}
    void flush(const std::string& s);

private:
    Fl_Box* w(){ return dynamic_cast<Fl_Box*>(fl_widget());}

};

inline Etiqueta::Etiqueta(const std::string& s)
    :Texto{new Fl_Box{0,0,  fltk_to_int(Ancho{s})
			 ,  fltk_to_int(Letra::alto())}}
{
    etiqueta(s);

    // TODO: usar Texto.align().
    w()->align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
}

inline void Etiqueta::flush(const std::string& s)
{
    texto(s);
    flush();
}


// Escribimos en la etiqueta una string.
inline void Etiqueta::operator=(const std::string& s)
{ etiqueta(s); }


/*!
 *  \brief  Es una línea de texto. 
 *
 *  La única diferencia con Etiqueta, es que su ancho es igual 
 *  al de la ventana que la contiene.
 *
 */
class Linea:public Etiqueta{
public:
    using Etiqueta::Etiqueta;
    void coloca(Ventana& v, Posicion p) override;


    /// Escribimos en la etiqueta una string.
    void operator=(const std::string& s)
    {Etiqueta::operator=(s);}
};


inline void Linea::coloca(Ventana& v, Posicion p)
{
    Etiqueta::coloca(v, p);
    ancho(v.ancho());	// la linea de texto es igual de ancha que la ventana
}

/*!
 *  \brief  Widget para mostrar varías líneas de texto (sin scroll,...).
 *
 */
class Varias_lineas:public Texto{
public:
    /// Construye un Varias_lineas con el mensaje s, de tamaño sz (en
    /// caracteres).
    Varias_lineas(const std::string& s, Size sz);

    /// Construye un Varias_lineas con el mensaje 's', del ancho 'a'.
    /// 
    /// El alto como mucho es 'h', pero en caso de que el mensaje no 
    /// necesite tanta altura, se ajustará el control a la altura del mensaje.
    /// Ideal, por ejemplo, para poner mensajes en ventanas de aviso,
    /// preguntas...
    /// \param a y h están dados en número de caracteres.
    ///	    CUIDADO: a no es un gui::Ancho. 'a' es el número de caracteres
    /// que queremos que tenga la línea como máximo.
    Varias_lineas(const std::string& s, unsigned a, alp::Maximo<unsigned> h);

    /// Escribimos 's' en el control.
    void texto(const std::string& s) { w()->value(s.c_str());}

private:
  Fl_Multiline_Output* w()
  {
      return dynamic_cast<Fl_Multiline_Output*>(fl_widget());
  }
};


}// namespace

#endif

