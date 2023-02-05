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
#ifndef __GUI_INPUT_STRING_H__
#define __GUI_INPUT_STRING_H__

#include "gui_widget_etcon.h"

namespace gui{


/*!
 *  \brief  Para el programador es una string, para el usuario es un Input.
 *
 *  Doy dos interfaces para acceder a la string:
 *
 *  1.- De forma explícita, usando paréntesis. La necesito para poder
 *	consultar cosas como: 
 *	\code
 *	    Input_string a{...};
 *	    if(a().empty()) ...
 *	\endcode
 *
 *  2.- De forma implícita. A fin de cuentas quiero que este Input sea un 
 *	string para el programador.
 */
class Input_string:public Widget_etcon{
public:
    explicit Input_string( const std::string& etiqueta // etiqueta del control
		  , Ancho ancho_input	    // ancho del control input
		  , const std::string& v0 = "");// valor inicial del input

    /// Leemos el string
    std::string operator()() const	    {return w()->value();}

    /// Escribimos en el string
    void operator()(const std::string& v)   {w()->value(v.c_str());}

    /// Conversión por defecto de Input_string a std::string
    operator std::string() const	    {return w()->value();}

    /// Asignamos una std::string
    void operator=(const std::string& s)    {w()->value(s.c_str());}


    // No está funcionando:
    // std::string a;
    // if (a == input_string) <--- la conversión no funciona ¿¿¿por qué???
    // Por ello, defino este operador.
    friend bool operator==(const Input_string& a, const std::string& b)
    {
	return (a.w()->value() == b);
    }
};

inline bool operator==(const std::string& a, const Input_string& b)
{return b == a;}

/// Volcamos el valor de la cadena en el flujo
inline std::ostream& operator<<(std::ostream& out, const Input_string& str)
{
    return out << static_cast<std::string>(str);
}

}// namespace

#endif
