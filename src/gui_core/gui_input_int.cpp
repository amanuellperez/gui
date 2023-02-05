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


#include "gui_input_int.h"

#include <limits>

#include <FL/Fl_Int_Input.H>


namespace gui{

// Inicializo la etiqueta para que si el usuario de esta clase
// se olvida de inicializarlo, detecte el error inmediatamente.
Input_int::Input_int()
    :Input_int("sin construir!", 5_car, 0)
{}


Input_int::Input_int(const std::string& etiqueta0
	      , Ancho num_cifras_input
	      , int v0)
    :Widget_etcon{new Fl_Int_Input{0,0 
			, fltk_to_int(num_cifras_input)
			, fltk_to_int(Letra::alto())}
	 , etiqueta0, num_cifras_input}
{
    valor(v0);

    // OJO: esto no alínea el input a la derecha, sino la etiqueta!!!
//    w()->align(FL_ALIGN_INSIDE | FL_ALIGN_RIGHT);

//// TODO: no alinea el texto a la derecha (la función align, lo que alinea
////	 es la etiqueta!!!).  Parece ser que FLTK no tiene funciones para
////	 alinear Fl_Int_Input :(
}


// Construye el Input. Este es el "constructor" a usar cuando se
// quiere construir un vector de Inputs. 
void Input_int::construye(const std::string& etiqueta, Ancho num_cifras_input
		, int v0)
{
    define(etiqueta, num_cifras_input);
    valor(v0);
}


int Input_int::valor() const 
    {return alp::to<int>(w()->value());}

void Input_int::valor(int v) 
    {w()->value(alp::to<std::string>(v).c_str());}




Input_int_acotado::Input_int_acotado
	      ( const std::string& etiqueta0
	      , Ancho num_cifras_input
	      , int v0)
    :Input_int{etiqueta0, num_cifras_input, v0}
    , min_{0}
    , max_{std::numeric_limits<int>::max()}
{
}

// Como no puedo garantizar que los valores de b sean positivos (pueden
// ser negativos) en todas estas funciones estoy obligado a mirar que
// el resultado res esté en el intervalo [min_, max_].
Input_int_acotado& Input_int_acotado::operator+=(const Input_int_acotado& b)
{
    auto res = valor()+b.valor();
    if(alp::esta_entre(res, min_, max_))
	valor(res);

    return *this;
}


Input_int_acotado& Input_int_acotado::operator-=(const Input_int_acotado& b)
{
    auto res = valor()-b.valor();
    if(alp::esta_entre(res, min_, max_))
	valor(res);

    return *this;
}

Input_int_acotado& Input_int_acotado::operator+=(int b)
{
    auto res = valor()+b;
    if(alp::esta_entre(res, min_, max_))
	valor(res);

    return *this;
}

Input_int_acotado& Input_int_acotado::operator-=(int b)
{
    auto res = valor()-b;
    if(alp::esta_entre(res, min_, max_))
	valor(res);

    return *this;
}

Input_int_acotado& Input_int_acotado::operator*=(int b)
{
    auto res = valor()*b;
    if(alp::esta_entre(res, min_, max_))
	valor(res);

    return *this;
}

Input_int_acotado& Input_int_acotado::operator/=(int b)
{
    auto res = valor()/b;
    if(alp::esta_entre(res, min_, max_))
	valor(res);

    return *this;
}

// Definimos la cota inferior.
void Input_int_acotado::min(int m) 
{
    min_ = m;

    if(valor() < min_)
	valor(min_);
}

// Definimos la cota superior.
void Input_int_acotado::max(int M) 
{
    max_ = M;
    if(valor() > max_)
	valor(max_);
}


}// namespace


