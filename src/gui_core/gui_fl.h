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

#ifndef __GUI_FL_H__
#define __GUI_FL_H__
/****************************************************************************
 *
 *   - DESCRIPCION: Clases que dependen completamente de FLTK. De hecho, son
 *	    clases hijas de clases de FLTK.
 *
 *   - COMENTARIOS: 
 *	    No distribuir este fichero. Depende directamente de FLTK,así que
 *	debería quedar para la implementación.
 *
 *   - HISTORIA:
 *           alp  - 19/07/2016 Escrito
 *
 ****************************************************************************/

#include <FL/Fl_Window.H>
#include <FL/Fl_Input_Choice.H>
#include "gui_tipos.h"

#include <alp_math.h>

namespace gui{


/*****************************************************************************
 * 
 *   - CLASE: Teclado
 *
 *
 ***************************************************************************/
/*!
 *  \brief  Contiene los códigos de las teclas que son caracteres de control. 
 *
 *  Son los códigos que devuelve Fl::event_key.
 *  
 *  TODO: sería mejor una enum!!!
 *
 */

class Teclado{   
public:
    static constexpr int escape = FL_Escape;
    static constexpr int retorno_carro= FL_Enter; 

    static constexpr int flecha_dcha = FL_Right;
    static constexpr int flecha_izda= FL_Left;
    static constexpr int flecha_arriba= FL_Up;
    static constexpr int flecha_abajo= FL_Down;
};



/*****************************************************************************
 * 
 *   - CLASE: Fl_Ventana
 *
 *   - DESCRIPCIÓN: En lugar de usar handle para manejar los eventos, le
 *	añadimos pulsa_tecla
 *
 ***************************************************************************/
class Ventana;


class Fl_Ventana:public Fl_Window{
public:
    Fl_Ventana(Ventana* v, int x, int y, int w, int h)
	:Fl_Window{x, y, w, h}, v_{v}{}
    ~Fl_Ventana(){}

    void draw() override;

private:
    Ventana* v_;    // necesito un puntero a la ventana, para que al llamar
		    // a handle, se llame a la función v_->pulsa_tecla
		    // de la Ventana correspondiente (es virtual esta función)

    int handle(int event) override;
};



/*****************************************************************************
 * 
 *   - CLASE: Fl_Control
 *
 *   - DESCRIPCIÓN: En lugar de usar handle para manejar los eventos, le
 *	añadimos pulsa_tecla
 *
 ***************************************************************************/
// Quería hacer algo parecido a lo que he hecho con Ventana, para
// gestionar los eventos. Sin embargo, no sirve, ya que Widget tiene un
// puntero a Fl_Widget, que puede ser, por ejemplo, Fl_Button, que no es hijo
// de mi Fl_Control!!! 
//
// En lugar de crear Fl_Control, voy a ir creando poco a poco las clases
// equivalentes a mi jerarquía. Ejemplo:
//	1.- Como tengo Boton, creo Fl_Boton hijo de Fl_Button.
//	2.- Como tengo Combo_strings, creo Fl_Combo_strings, hijo de
//	Fl_Input_Choice.
//	...
//  y en cada uno de estas clases manejo los eventos.
//
//class Widget;
//
//
//class Fl_Control:public Fl_Widget{
//public:
//    Fl_Control(Widget* w, int x, int y, int a, int h)
//	:Fl_Widget{x, y, a, h}, w_{w}{}
//
//private:
//    Widget* w_;	    // necesito un puntero al widget, para que al llamar
//		    // a handle, se llame a la función w_->pulsa_tecla
//		    // w_->push_left, ..., correspondiente del Widget.
//
//    int handle(int event);
//};
//

class Combo_strings;
// TODO: No me funciona la función handle!!!. ¿Cómo implementarla?
class Fl_Combo_strings:public Fl_Input_Choice{
public:
    Fl_Combo_strings(Combo_strings* w, int x, int y, int a, int h)
	:Fl_Input_Choice{x, y, a, h}{} //, w_{w}{}

private:
//    Combo_strings* w_;// necesito un puntero al widget, para que al llamar
//		    // a handle, se llame a la función w_->pulsa_tecla
//		    // w_->push_left, ..., correspondiente del Widget.

//    int handle(int event);
};



/***************************************************************************
 *			FUNCIONES QUE DEPENDEN DE FLTK
 ***************************************************************************/
/// Indica si el punto p de la ventana pertenece al widget.
/// p está dado respecto de la ventana.
/// Observar que p es la posición de un punto dentro de una ventana donde está
/// colocado el widget w.
inline bool pertenece(const Posicion& p, const Fl_Widget& wdg)
{
    return (alp::esta_entre(p.x.pix(), wdg.x(), wdg.x() + wdg.w() - 1)
	   and  alp::esta_entre(p.y.pix(), wdg.y(), wdg.y() + wdg.h() - 1));
}

// misma función que la anterior
inline bool pertenece(int x, int y,  const Fl_Widget& wdg)
{
    return (alp::esta_entre(x, wdg.x(), wdg.x() + wdg.w() - 1)
	   and  alp::esta_entre(y, wdg.y(), wdg.y() + wdg.h() - 1));
}

}// namespace gui


#endif

