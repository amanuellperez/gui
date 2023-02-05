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

#ifndef __GUI_MENU_BAR_H__
#define __GUI_MENU_BAR_H__

#include "gui_ventana.h"

#include <FL/Fl_Menu_Bar.H>

namespace gui{

/*****************************************************************************
 * 
 *   - CLASE: Menu_bar
 *
 *   - DESCRIPCIÓN: Es un menu.
 *	    Lo voy a definir de ancho igual a la de la ventana, así que
 *	    realmente es un menubar.
 *
 ***************************************************************************/
class Menu_bar:public Widget{
public:
    Menu_bar();

    /// Colocamos el menu_bar en la ventana, no elegimos la posición
    void coloca(Ventana& v);	

    void add(const std::string& etiqueta, const std::string& shortcut
	    , Callback f);

private:
    // La función coloca que defino public, hide las 2 siguientes funciones
    // que son virtuales. El compilador da un warning si no se definen. Las
    // defino aquí, para dejar de forma explícita que es realmente lo que
    // quiero hacer.
    // Le indicamos al widget que lo hemos colocado en el grupo de controles g
    void coloca(Grupo_de_controles& g) override {}

    // Coloca el widget en la ventana v, en la posición p0.
    void coloca(Ventana& v, Posicion p0) override { Widget::coloca(v, p0); }

    // conversión a fltk
    Fl_Menu_Bar* w(){ return dynamic_cast<Fl_Menu_Bar*>(fl_widget());}


    // La defino para que no de un warning
    void coloca(Coordenada x, Coordenada y) override
    {Widget::coloca(x,y);}
};

inline Menu_bar::Menu_bar()
	: Widget{new Fl_Menu_Bar{0,0, 0, fltk_to_int(Letra::alto())}}
{}

inline void Menu_bar::coloca(Ventana& v)
{
    // Los menu_bar todos van arriba
    // DUDA: ¿dar la posibilidad de colocarlo abajo? ¿a la derecha? ¿izda?
    // ¿medio? @_@
    Widget::coloca(v, Posicion{0_pix,0_pix});
    ancho(v.ancho());	// el ancho del menu es toda la ventana
}

inline void Menu_bar::add(const std::string& etiqueta, const std::string& shortcut
	, Callback f)
{
    w()->add( etiqueta.c_str()
	    , shortcut.c_str()
	    , reinterpret_cast<Fl_Callback*>(f), ventana_no_usar());
}


}// namespace

#endif

