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
#ifndef __GUI_BOTON_BOOL_H__
#define __GUI_BOTON_BOOL_H__

#include "gui_widget.h"

namespace gui{
/*!
 *  \brief  Es un interruptor, con dos posibles estados: pulsado o sin pulsar.
 *
 *	Para el usuario es un interruptor, para el programador es un bool:
 *	true = pulsado; false = sin pulsar.
 *
 *	No tiene callback asociado.
 *
 */
class Boton_bool:public Widget{
public:
    /// Construye un Boton_bool con el valor inicial 'b'.
    explicit Boton_bool(const std::string& etiqueta, bool b = false);

    /// Conversión implícita a bool.
    operator bool() const	{return valor();}

    /// Asignamos un bool al botón.
    void operator=(bool b)	{valor(b);}
    

    /// Comparamos el valor del botón a un bool.
    friend bool operator==(const Boton_bool& b1, bool b2);

private:
    // Devuelve el valor del Boton.
    bool valor() const;

    // Asignamos b al valor del Boton.
    void valor(bool b);
};



/// Comparamos el valor del check a un bool.
inline bool operator==(const Boton_bool& b1, bool b2)
{ return b1.valor() == b2; }

/// El operador == es simétrico.
inline bool operator==(bool b2, const Boton_bool& b1)
{ return b1 == b2; }

/// Comparamos el valor del check a un bool.
inline bool operator!=(const Boton_bool& b1, bool b2)
{return !(b1 == b2);}

/// El operador != es simétrico.
inline bool operator!=(bool b2, const Boton_bool& b1)
{return !(b1 == b2);}

}// namespace

#endif



