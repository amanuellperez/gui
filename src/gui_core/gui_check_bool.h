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
#ifndef __GUI_CHECK_BOOL_H__
#define __GUI_CHECK_BOOL_H__

#include "gui_widget.h"

namespace gui{

/*!
 *  \brief  GUI de un bool con forma de check_box.
 *
 *  Para el usuario del programa es un Check_box, mientras que
 *  para el programador es un bool. De hecho, el programador
 *  solo considera el Check_bool como un Check_box cuando lo define. 
 *  En el resto del programa es un bool.
 *
 *  Ejemplo:
 *  \code
 *	Check_bool b{"rojo", true};
 *	...
 *	if(b) {...}
 *	...
 *	b = false;
 *
 *  \endcode
 */
class Check_bool:public Widget{
public:
    /// Creamos un Check_box con la 'etiqueta' indicada. 
    /// 'marcado' indica si queremos que por defecto esté marcado o no.
    explicit Check_bool(const std::string& etiqueta, bool marcado=false);

    /// Conversión implícita a bool.
    operator bool() const	{return valor();}

    /// Asignamos un bool al check.
    void operator=(bool b)	{valor(b);}
    
    /// Comparamos el valor del check a un bool.
    friend bool operator==(const Check_bool& b1, bool b2);


    /// Modificamos dinámicamente la etiqueta del bool
    void etiqueta(const std::string& et) {Widget::etiqueta(et);}

private:
    // Devuelve el valor del Check.
    bool valor() const;

    // Asignamos b al valor del Check.
    void valor(bool b);

    // Funciones auxiliares
    static int ancho_por_defecto(const std::string& s);
};



/// Comparamos el valor del check a un bool.
inline bool operator==(const Check_bool& b1, bool b2)
{ return b1.valor() == b2; }

/// El operador == es simétrico.
inline bool operator==(bool b2, const Check_bool& b1)
{ return b1 == b2; }

/// Comparamos el valor del check a un bool.
inline bool operator!=(const Check_bool& b1, bool b2)
{return !(b1 == b2);}

/// El operador != es simétrico.
inline bool operator!=(bool b2, const Check_bool& b1)
{return !(b1 == b2);}


}// namespace

#endif

