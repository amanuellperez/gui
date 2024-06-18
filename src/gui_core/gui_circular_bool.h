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

#ifndef __GUI_CIRCULAR_BOOL_H__
#define __GUI_CIRCULAR_BOOL_H__

#include "gui_widget.h"

namespace gui{
/*!
 *  \brief  GUI de un bool con forma de radio_button.
 *
 *	Para el usuario del programa es un radio_button, mientras que
 *	para el programador es un bool. De hecho, el programador
 *	solo considera el Circular_bool como Radio_button cuando lo 
 *	define.
 *
 *	Todos los checks de este tipo dentro de un mismo grupo
 *	están vinculados: solo se puede seleccionar uno de ellos a la vez.
 *	Son para elegir una opción.
 *
 *	¿Esto realmente es una lista de bools donde solo puedo seleccionar
 *	un bool?
 *	    No, realmente es una enumeración!!!!
 *	    enum Opciones {subir, bajar};
 *	    Opciones opcion;
 *	    switch(opcion){...}
 *
 *  \todo Convertir esto en una enumeración.
 *
 *  Ejemplo:
 *	\code
 *	    // Creación
 *	    Circular_bool subir{"subir", true};
 *	    Circular_bool bajar{"bajar", false};
 *
 *	    Grupo_horizontal opciones;
 *	    opciones << subir << bajar;
 *
 *	    // uso
 *	    if(subir) ...
 *	    
 *	\endcode
 *
 */
class Circular_bool:public Widget{
public:
    explicit Circular_bool(const std::string& etiqueta, bool b=false);


    /// Conversión implícita a bool.
    operator bool() const	{return valor();}

    /// Asignamos un bool al check.
    void operator=(bool b)	{valor(b);}
    

    /// Comparamos el valor del check a un bool.
    friend bool operator==(const Circular_bool& b1, bool b2);

    
private:
    // Devuelve el valor del Check.
    bool valor() const;

    // Asignamos b al valor del Check.
    void valor(bool b);

    // Funciones auxiliares
    static int ancho_por_defecto(const std::string& s);
};


/// Comparamos el valor del check a un bool.
inline bool operator==(const Circular_bool& b1, bool b2)
{ return b1.valor() == b2; }

/// El operador == es simétrico.
inline bool operator==(bool b2, const Circular_bool& b1)
{ return b1 == b2; }

/// Comparamos el valor del check a un bool.
inline bool operator!=(const Circular_bool& b1, bool b2)
{return !(b1 == b2);}

/// El operador != es simétrico.
inline bool operator!=(bool b2, const Circular_bool& b1)
{return !(b1 == b2);}

}// namespace

#endif
