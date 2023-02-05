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

#ifndef __GUI_VENTANA_H__
#define __GUI_VENTANA_H__

#include "gui_tipos.h"
#include "gui_fl.h"	// Fl_Ventana

#include <memory>

namespace gui{

/*****************************************************************************
 * 
 *   - CLASE: Ventana
 *
 *   - DESCRIPCIÓN: Clase padre de todas las ventanas.
 *	    Una ventana es un contenedor de Widgets.
 *
 ***************************************************************************/
class Ventana{
public:
    /// Construimos una ventana de tamaño sz y título ttitulo
    Ventana(Size sz, const std::string& titulo);

    // Al crear un destructor por defecto no se crean los move constructors.
    // Al definir un constructor, no se definen los constructores de copia por
    // defecto. Con todo prefiero ponerlos de forma explícita. Buena
    // práctica!!!
    Ventana(const Ventana&)		= delete;
    Ventana& operator=(const Ventana&)	= delete;
    Ventana(Ventana&&)			= delete;
    Ventana& operator=(Ventana&&)	= delete;


    virtual ~Ventana(){}

    /// Marca la ventana como principal (al cerrarla, se cierra la aplicación).
    void es_principal(){v->callback(cb_exit);}

    /// Colocamos la ventana en el punto p(x,y).
    void p0(Coordenada x, Coordenada y) {v->position(x.pix(), y.pix());}

    /// Redimensionamos la ventana al tamaño (w, h).
    void size(Ancho w, Alto h) {v->size(w.pix(), h.pix());}

    /// Cambiamos el título de la ventana.
    void titulo(const std::string& s) { v->copy_label(s.c_str()); }

    Coordenada x0() const {return Coordenada::en_pix(v->x());}
    Coordenada y0() const {return Coordenada::en_pix(v->y());}

    /// Esquina superior izquierda de la ventana
    Posicion p0() const {return Posicion{x0(), y0()};}

    Ancho ancho() const {return Ancho::en_pix(v->w());}
    Alto alto()  const  {return Alto::en_pix(v->h());}

    // NOTA: las funciones show y hide tienen que ser virtuales, ya que si una
    // ventana tiene ventanas hijas, al ocultar a la padre, hay que ocultar a
    // las hijas (o quizás no, lo decidirá el programador). Por esto tienen
    // que ser virtuales.
    /// Muestra la ventana en la última posición que tenía
    virtual void show() { v->show();}

    /// Muestra la ventana en la posición p indicada.
    virtual void show(Posicion p) {show(p.x, p.y);}

    /// Muestra la ventana en la posición (x, y) indicada.
    virtual void show(Coordenada x, Coordenada y);

    /// Oculta la ventana. No la destruye, solo la oculta.
    virtual void hide() { v->hide(); }

    /// Redibujamos la ventana.
    void redraw() {v->redraw();}

    /// Hacemos la ventana toda la pantalla (true) o no (false).
    void fullscreen(bool b = true);

    /// Marcamos la ventana como modal.
    void modal(){v->set_modal();}

    /// Espera mientras la ventana está abierta.
    void wait(){while(v->shown()) Fl::wait();}


    /// Indica que la ventana se puede redimensionar (true)  o no (false).
    /// TODO: no funciona el hacer la ventana no redimensionable!!!
    void resizable(bool redimensionar = true);

    // cogemos el foco: TODO: No funciona bien!!!
    void take_focus(){v->focus(v.get());} //v->take_focus();}

protected:
    // ----------------------
    // manejadores de eventos
    // ----------------------
    // 1. - manejador de teclado
    // devuelve 0 si no procesa la tecla, 1 si la procesa
    // Devuelve:
    //	    true    = procesa la tecla
    //	    false   = no la procesa
    // s = texto que ha escrito el usuario
    // key = codigo int de la tecla (por ejemplo, para flechas, ctrl, alt...)
    //	     Este código está en la clase Teclado:
    //		Teclado::flecha_izda, Teclado::flecha_dcha...
    virtual bool pulsa_tecla(const std::string& s, int key) {return false;} 

    // 2. - manejadores del raton
    virtual bool push_left(Posicion p)    {return false;};
    virtual bool push_middle(Posicion p)  {return false;};
    virtual bool push_right(Posicion p)   {return false;};

    virtual bool drag_left(Posicion p)    {return false;};
    virtual bool drag_middle(Posicion p)  {return false;};
    virtual bool drag_right(Posicion p)   {return false;};

    virtual bool release_left(Posicion p)    {return false;};
    virtual bool release_middle(Posicion p)  {return false;};
    virtual bool release_right(Posicion p)   {return false;};

    virtual void draw(){}

private:
    friend Fl_Ventana;
    std::unique_ptr<Fl_Ventana> v;

    // TRUCO: si llamo exit(0), no se llaman los destructores de los objetos
    // creados, lo cual no es buena cosa. Para llamarlos y que el programa se
    // cierre de forma controlada lanzo una excepción que capturo en gui_main,
    // siendo totalmente trasparente al usuario. De esta forma se cierra el
    // programa de forma ordenada.
    static void cb_exit(Fl_Widget*, void*);


    // FUNCIONES QUE NO DEBEN DE LLAMARSE
    // Las uso en gui, pero no las debe de usar el cliente final
    // ¿cómo poder hacerlas private?
public:
    void begin(){ v->begin();}
    void add(Fl_Widget* w){ v->add(w);}
    void end(){ v->end();}

    void resizable(Fl_Widget* w){v->resizable(w);}
};


// si b = true, la muestra pantalla completa; si b = false, la muestra a
// tamaño normal
inline void Ventana::fullscreen(bool b) 
{if(b) v->fullscreen(); else v->fullscreen_off();}
 
// Indica que la ventana se puede redimensionar (true)  o no (false).
inline void Ventana::resizable(bool redimensionar)
{
    if(redimensionar)
	v->resizable(v.get());
    else
	v->resizable(NULL);
}


}// namespace

#endif
