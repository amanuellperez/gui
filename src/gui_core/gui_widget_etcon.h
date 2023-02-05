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
#ifndef __GUI_WIDGET_ETCON_H__
#define __GUI_WIDGET_ETCON_H__


#include "gui_widget.h"

namespace gui{

/*!
 *  \brief  Son widgets que tienen dos controles: 
 *		    etiqueta + control
 *
 *  Ejemplos:
 *		Input_xxx	    = es una etiqueta + input
 *		Combo_strings   = es una etiqueta + combobox
 *
 *  El ancho del widget (realmente, del control) es 
 *		ancho = et_ancho + input_ancho
 *
 *	    Estos controles los podemos colocar en la ventana, bien usando
 *	    la posición p0 del control, o bien usando la posición p0 del input
 *	    (de esta forma podemos alinear varios de estos Widget_etcon). Por eso
 *	    doy dos coloca.
 */
class Widget_etcon:public Widget{
public:
    virtual ~Widget_etcon(){}

    /// Coloca el widget en la ventana v, en la posicion p0
    void coloca(Ventana& v, Posicion p0) override;

    /// \brief Colocamos el widget en la ventana v,
    /// siendo pi la posición del input, no la del widget.
    void coloca_input(Ventana& v, Posicion pi);

    /// x0 en la que empieza el widget
    Coordenada x0() const override {return x0_;}

    /// Colocamos el widget en la posición p0(x,y).
    // void p0(Coordenada x, Coordenada y) override;
    void coloca(Coordenada x, Coordenada y) override;

    /// Colocamos el widget en la posición p0.
    // void p0(Posicion p) {p0(p.x, p.y);}
    void coloca(Posicion p) {coloca(p.x, p.y);}


    /// posición x0 en la que empieza el input
    Coordenada input_x0() const {return x0_ + et_ancho_;}

    /// ancho del widget (etiqueta + input)
    Ancho ancho() const override {return ancho_;}


protected:
    // El cliente no puede construir Widget_etcon, sino Input_string, Input_int...
    explicit Widget_etcon( Fl_Widget* w
		  ,  const std::string& etiqueta // etiqueta del control
		  , Ancho ancho_input);		// ancho del control input 


    // Si quiero definir un vector de Input_int, voy a dar un constructor por
    // defecto en el Input_int. Es necesario que después crear el vector
    // se defina la etiqueta y la dimensión del input de cada uno de los 
    // Inputs del vector. Importante: primero llamar a esta función,
    // después colocar el widget en la ventana. En caso contrario queda
    // undefined cómo quedará colocado el widget.
    void define(const std::string& etiqueta0, Ancho input_ancho);


    Fl_Input* w(){ return dynamic_cast<Fl_Input*>(fl_widget());}
    const Fl_Input* w() const { return dynamic_cast<const Fl_Input*>(fl_widget());}


private:
    Coordenada x0_ = "-1"_pix;// posición en la que empieza el widget (etiqueta+input)
    Ancho ancho_;	// ancho del widget
    Ancho et_ancho_;	// ancho de la etiqueta



    // La defino para que no de un warning el compilador
    void coloca(Grupo_de_controles& g) override 
    {Widget::coloca(g);}
};


// inline void Widget_etcon::p0(Coordenada x, Coordenada y)
inline void Widget_etcon::coloca(Coordenada x, Coordenada y)
{
    x0_ = x;
    // Widget::p0(x+et_ancho_, y);
    Widget::coloca(x+et_ancho_, y);
}


}// namespace 

#endif
