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

#ifndef __GUI_INPUT_INT_H__
#define __GUI_INPUT_INT_H__

#include "gui_widget_etcon.h"

namespace gui{

/*!
 *  \brief  Para el programador es un int, para el usuario un Input.
 *
 *  Todas las operaciones que hacemos sobre un Input_int, son operaciones
 *  que hacemos sobre el valor del input, no sobre el widget!!!
 *  Así, si comparamos dos inputs a y b, if(a == b), lo que estamos
 *  preguntando es ¿tienen el mismo valor? Esto tiene sentido si concebimos
 *  que a y b son enteros para el programador y no widgets. 
 *
 *  Cuando el programador quiera acceder al widget, usará las funciones
 *  propias de los widgets (entre las cuales no entran las de +=, ==, ...)
 *
 *
 *  Ejemplo 1: crear solo un Input_int.
 *  \code
 *	// Creamos un Input_int que pone 'incr = ', de  4 caracteres de ancho
 *	el input, y con el valor inicial de 50.
 *	gui::Input_int incr1{"incr = ", 4_car, 50};  
 *	gui::Input_int incr2{"incr = ", 4_car, 50};  
 *	
 *	// A la hora de manejarlo se maneja como un int
 *	x += incr1;
 *	y -= incr1;
 *	...
 *	incr2 = incr1;	// OJO: para el programador son int, así que
 *			// esto lo que hace es iguala el valor de incr2
 *			// con el valor de incr1.
 *  \endcode
 *
 *  Ejemplo 2: creamos un vector de Input_int.
 *  \code
 *	std::array<gui::Input_int, 5> x;
 *
 *	// Antes de colocarlo en la ventana hay que construirlos
 *	for(size_t i = 0; i < x.size(); ++i)
 *	    x[i].construye("x = ", 4_car, -50 + i*50);
 *
 *	Maquetadro m{*this};
 *	m.debajo(x[0]);
 *	...
 *	// Luego se usa como si fuera un array de ints
 *	x[0] += incr;
 *	...
 *  \endcode
 *  
 *  TODO: ¡Tiene problemas de eficiencia al acceder al valor!
 *	No usar la conversión implícita a int dentro de algoritmos, ya que 
 *	sin medir, se nota que va mucho más lento.
 *	De momento usarlo para configurar los algoritmos, pero no acceder a
 *	estos ints montones de veces, sino solo de vez en cuando.
 */
class Input_int:public Widget_etcon{
public:
    /// Este constructor es para crear vectores de inputs.
    /// ¡No olvidarlo construirlo llamando a construye!
    Input_int();

    /// Construye el Input. Este es el "constructor" a usar cuando se
    /// quiere construir un vector de Inputs. 
    void construye(const std::string& etiqueta, Ancho num_cifras_input
		    , int v0);



    /// \param[in] etiqueta: etiqueta que va delante del input
    /// \param[in] num_cifras_input: número de cifras que vamos a escribir
    ///		    en el input.
    /// \param[in] v0: valor inicial del input
    Input_int( const std::string& etiqueta
		  , Ancho num_cifras_input	// número de cifras del input
		  , int v0);


    /// Conversión por defecto de Input_int a int.
    operator int() const	{return valor();}

    /// Asignamos un entero al input.
    void operator=(int x)	{valor(x);}

    /// Copiamos los valores, no los widgets!!!
    void operator=(const Input_int& x)	{valor(x.valor());}

    // Operadores básicos para concebir Input_int como int
    // CUIDADO: no tiene sentido sumar dos Input_ints, salvo que el resultado
    // sea un int!!! Los operadores += y -= lo que hacen es modificar el valor
    // del int, no tocan el widget!!!
    // Ejemplo:
    //	    Input_int a, b;
    //	    a += b; // al valor de a le sumamos el valor de b, pero
    //		    // los widgets no los tocamos.
    //
    //	    Input_int c = a+b; ???? NO TIENE SENTIDO!!! No podemos crear
    //			    otro widget así!!!
    //
    //	    int c = a+b;    // sí tiene sentido: c es la suma de los valores
    //			    // de a y b.
    Input_int& operator+=(const Input_int& b)
    {valor(valor()+b.valor()); return *this;}

    Input_int& operator-=(const Input_int& b)
    {valor(valor()-b.valor()); return *this;}
    
    Input_int& operator+=(int b)
    {valor(valor()+b); return *this;}

    Input_int& operator-=(int b)
    {valor(valor()-b); return *this;}

    Input_int& operator*=(int b)
    {valor(valor()*b); return *this;}

    Input_int& operator/=(int b)
    {valor(valor()/b); return *this;}

    friend bool operator==(const Input_int& a, const Input_int& b);

protected:
    // Devuelve el valor del Input
    int valor() const;

    // Asignamos v al valor del Input
    void valor(int v);
};

inline bool operator==(const Input_int& a, const Input_int& b)
{return a.valor() == b.valor();}

inline bool operator!=(const Input_int& a, const Input_int& b)
{return !(a == b);}


/// Indica si x pertenece al intervalo [x0, x1].
template <typename Int>
struct esta{
    explicit esta(Int xx):x{xx}{}

    bool entre(const gui::Input_int& a, const gui::Input_int& b)
    {return (a <= x) and (x <= b);}

    Int x;
};

inline bool esta_entre(int x
	, const gui::Input_int& x0, const gui::Input_int& x1)
{ return (x0 <= x) and (x <= x1); }


/// Convierte el int a string
inline std::string to_string(const Input_int& x)
{
    return alp::to_string(static_cast<int>(x));
}


/*!
 *  \brief  Es un Input_int acotado.
 *
 *  El valor del int está comprendido entre un rango [min, max].
 *
 *  Ejemplo:
 *  \code
 *	// Por defecto las cotas son [0, int_max]
 *	Input_int_acotado inp{"rojo", 3_car, 0};
 *	...
 *
 *	// definimos las cotas
 *	inp.min(-5);
 *	inp.max(250);
 *
 *	// si se van a definir las dos cotas, es más corto
 *	inp.entre(-e, 250); // mismo efecto que min(-5); max(250);
 *
 *  \endcode
 *
 */
class Input_int_acotado:public Input_int{
public:
    /// \param[in] etiqueta: Etiqueta que va delante del input
    /// \param[in] num_cifras_input: Número de cifras que vamos a escribir
    ///		    en el input.
    /// \param[in] v0: Valor inicial del input
    Input_int_acotado( const std::string& etiqueta
		  , Ancho num_cifras_input	// número de cifras del input
		  , int v0);


    /// Definimos la cota inferior. 
    /// En caso de que el input valiese menos que min, hace que valga min.
    void min(int m);

    /// Definimos la cota superior.
    /// En caso de que el input valiese mas que max, hace que valga max.
    void max(int M);

    /// Definimos las cotas [min, max] de este input
    void entre(int minimo, int maximo);

    /// Conversión por defecto de Input_int a int.
    operator int() const	{return valor();}

    /// Asignamos un entero al input.
    void operator=(int x)	{valor(x);}

    /// Copiamos los valores, no los widgets!!!
    void operator=(const Input_int_acotado& x)	{valor(x.valor());}


    // Operadores básicos para concebir Input_int_acotado como int
    // CUIDADO: no tiene sentido sumar dos Input_int_acotados, salvo que el resultado
    // sea un int!!! Los operadores += y -= lo que hacen es modificar el valor
    // del int, no tocan el widget!!!
    // Ejemplo:
    //	    Input_int_acotado a, b;
    //	    a += b; // al valor de a le sumamos el valor de b, pero
    //		    // los widgets no los tocamos.
    //
    //	    Input_int_acotado c = a+b; ???? NO TIENE SENTIDO!!! No podemos crear
    //			    otro widget así!!!
    //
    //	    int c = a+b;    // sí tiene sentido: c es la suma de los valores
    //			    // de a y b.
    Input_int_acotado& operator+=(const Input_int_acotado& b);
    Input_int_acotado& operator-=(const Input_int_acotado& b);
    Input_int_acotado& operator+=(int b);
    Input_int_acotado& operator-=(int b);
    Input_int_acotado& operator*=(int b);
    Input_int_acotado& operator/=(int b);

    friend bool operator==( const Input_int_acotado& a
			  , const Input_int_acotado& b);

private:
    int min_, max_; // cotas del int
};


// Definimos las cotas [min, max] de este input
inline void Input_int_acotado::entre(int minimo, int maximo)
{
    min(minimo);
    max(maximo);
}


inline bool operator==(const Input_int_acotado& a, const Input_int_acotado& b)
{return a.valor() == b.valor();}

inline bool operator!=(const Input_int_acotado& a, const Input_int_acotado& b)
{return !(a == b);}


}// namespace

#endif
