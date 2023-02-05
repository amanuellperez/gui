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
#ifndef __ALP_GUI_TIPOS_H__
#define __ALP_GUI_TIPOS_H__
/****************************************************************************
 *
 *   - DESCRIPCION: Tipos usados en GUI.
 *
 *   - COMENTARIOS: 
 *
 *   - HISTORIA:
 *           alp  - 18/04/2017 Escrito
 *
 ****************************************************************************/
#include <alp_cast.h>

namespace gui{


class Longitud;
/*!
 *  \brief  Una coordenada es una distancia con signo.
 *
 *  El objetivo es definir Coordenadas y Longitudes. Las coordenadas tienen
 *  signo, mientras que las longitudes (= distancias) no lo tienen. Quedaría
 *  muy bien definir una template Longitud y usar los siguientes alias:
 *  \code
 *	using Coordenada = Longitud<int>;
 *	using Distancia	 = Longitud<unsigned>;
 *  \endcode
 *
 *  Sin embargo, haciendo esto no puedo definir un operator""_pix, que
 *  funcione con los dos tipos. Por ello, defino coordenada primero, y 
 *  luego Longitud como una coordenada que la construyo garantizando que
 *  es mayor o igual que cero. <--- en la práctica tengo que definir dos 
 *  operadores diferentes, así que, de momento, no es necesario hacerlo así.
 *
 *  DUDA: Merece la pena considerar coordenadas negativas? A fin de cuentas, 
 *  los widgets siempre van a estar en una ventana ==> sus coordenadas son
 *  positivas. Pero, podemos sacar una ventana fuera del escritorio ==> sus
 *  coordenadas son negativas!!! (???)
 *
 *  Observar:
 *	Una longitud es un número positivo, que por definición es también un
 *	número entero. Esto es, podemos convertir de forma implícita una
 *	longitud en coordenada:
 *	    Longitud d;
 *	    Coordenada c = d;
 *	==> tiene que haber un constructor por defecto Coordenada(Longitud);
 *
 *	En cambio, una coordenada es un número entero, que en general no tiene
 *	por que ser positivo. Así que no se debería de convertir por defecto
 *	una coordenada en longitud!!!
 *
 *	Esto sugiere que sería mejor heredar Coordenada de Longitud,  y no 
 *	como lo he hecho aquí. Pero si lo he hecho así es por culpa de _pix.
 */
class Coordenada{
public:
    /// Conversión implícita de una Longitud en Coordenada. Matemáticamente 
    /// esto siempre es correcto. En programa necesita hacer un narrow_cast.
    Coordenada(const Longitud&);

    /// Devuelve el número de pixeles en que está medido este ancho.
    int pix() const {return num_pixeles_;}

    // Devuelve el número de cm en que está medido este ancho.
    // unsigned cm() const {return x_;}
    

    /// Devuelve el Coordenada asociado a x pixeles.
    /// Ejemplo:
    /// \code
    ///	    int x = 350;
    ///	    auto a = Coordenada::en_pix(x);
    /// \endcode
    static Coordenada en_pix(int num_pixeles);


    Coordenada& operator+=(Coordenada a);
    Coordenada& operator-=(Coordenada a);

    friend Coordenada operator+(Coordenada a, Coordenada b);
    friend Coordenada operator-(Coordenada a, Coordenada b);

    /// Multiplicación por la derecha de un entero: n*a.
    friend Coordenada operator*(float n, Coordenada a);

    /// División por un número: a/n.
    friend Coordenada operator/(Coordenada a, float n);

    /// Comparación de dos coordenadas: ¿this == b?
    bool operator==(Coordenada b) const {return num_pixeles_ == b.num_pixeles_;}

    /// Comparación de dos coordenadas: ¿this != b?
    bool operator!=(Coordenada b) const {return !(*this == b);}

    bool operator<(Coordenada b) const {return num_pixeles_ < b.num_pixeles_;}
    bool operator<=(Coordenada b) const {return (*this < b or *this == b);}
    bool operator>=(Coordenada b) const {return !(*this < b);}
    bool operator>(Coordenada b) const {return (*this >= b and *this != b);}


    friend std::ostream& operator<<(std::ostream& out, const Coordenada& c);

protected:
    // Es private para que el usuario esté obligado a pasar las unidades!!!
    Coordenada(int num_pixeles) : num_pixeles_{num_pixeles}{}


private:
    // valor del ancho en pixeles y en caracteres.
    // La 'Coordenada' usa únicamente num_pixeles_, así que para que esté 
    // bien creada este número tiene que estar calculado. Usamos el
    // num_caracteres_ para que se puedan crear los anchos y altos como
    // 25_car.
    int num_pixeles_;
};

// ------------------------------------------
// Interfaz que no accede a la implementación
// ------------------------------------------
/// Multiplición por la izquierda de un entero: a*n.
Coordenada operator*(Coordenada a, float n);


/// Imprime una coordenada en el fluto out.
std::ostream& operator<<(std::ostream& out, const Coordenada& c);


// ----------------------------
// Implementación de Coordenada
// ----------------------------
// Forma en que abreviamos las coordenadas
//using Coord = Coordenada;


// Implementación de Coordenada!!!
inline Coordenada Coordenada::en_pix(int num_pixeles)
{ return Coordenada{num_pixeles}; }


/// inline namespace. Para usar estos literales, escribir 
/// using namespace gui::literals;
inline namespace literals{
    /// \brief Devuelve el Coordenada asociado a x pixeles positivos!!!
    ///
    /// Ejemplo:
    /// \code
    ///	    Coordenada a = 200_pix;
    /// \endcode
    inline Coordenada operator""_pix(const char* num_pixeles)
    { return Coordenada::en_pix(alp::to<int>(num_pixeles));}

    /// \brief Devuelve el Coordenada asociado a x pixeles (positivos 
    /// o negativos).
    ///
    /// Ejemplo:
    /// \code
    ///	    Coordenada a = "-200"_pix;
    /// \endcode
    ///
    /// \todo Es un engorro tener que poner entre comillas el -200, pero
    /// de momento no se cómo quitarlos (el estandar creo que no lo admite
    /// aunque pudiera ser posible crear un literal template (ver 
    /// Stroustrup, pagi 560)).
    inline Coordenada operator""_pix(const char* num_pixeles, size_t n)
    { return Coordenada::en_pix(alp::to<int>(num_pixeles));}

}// namespace literals


inline Coordenada& Coordenada::operator+=(Coordenada a)
{ 
    num_pixeles_+= a.num_pixeles_; 
    return *this;
}

inline Coordenada operator+(Coordenada a, Coordenada b)
{ return a+=b;}

inline Coordenada& Coordenada::operator-=(Coordenada a)
{ 
    num_pixeles_-= a.num_pixeles_; 
    return *this;
}

inline Coordenada operator-(Coordenada a, Coordenada b)
{ return a-=b; }


// -----------------------------------
// Implementación del interfaz público
// -----------------------------------
// Imprime una coordenada en el fluto out.
inline std::ostream& operator<<(std::ostream& out, const Coordenada& c)
{return out << c.num_pixeles_;}

// Multiplicación por la derecha de un entero: n*a.
inline Coordenada operator*(float n, Coordenada a)
{
    a.num_pixeles_*= n;
    return a;
}

// Multiplición por la izquierda de un entero: a*n.
inline Coordenada operator*(Coordenada a, float n)
{ return n*a; }

/// División por un número: a/n.
inline Coordenada operator/(Coordenada a, float n)
{
    a.num_pixeles_/=n;
    return a;
}

/*!
 *  \brief  Longitudes que manejamos en GUI.
 *
 *  Una longitud la podemos medir usando diferentes medidas: mm, cm, m...
 *  , pixeles o caracteres. Esta clase suministra el interfaz para manejar 
 *  longitudes medidas en pixeles, que es la unidad por defecto que se usa
 *  a la hora de dibujar los widgets. (no suministro mm, cm, pero sería muy 
 *  fácil añadirlo en el futuro).
 *
 *  La ventaja de esto es que el usuario puede elegir las unidades que quiere
 *  manejar: pixeles o caracteres, y que no hay que dejarlo documentado en
 *  ninguna parte (a esta función pásale pixeles, mientras que a esta otra
 *  pasale caracteres! <--- esto es error prone!!!)
 */

class Longitud:public Coordenada{
public:
    /// Conversión implícita de Coordenada a Longitud. Fundamental que sea
    /// implícita para que funcione Longitud a = 23_pix;
    Longitud(Coordenada c);
    
    /// Devuelve el número de pixeles en que está medido este ancho.
    unsigned pix() const {return alp::narrow_cast<unsigned>(Coordenada::pix());}

    /// No se puede restar cualquier longitud, solo una mayor de una menor.
    /// Por eso sobrecargamos este operador, para que introduzca esta
    /// precondición.
    Longitud& operator-=(Longitud a);

protected:
    Longitud(unsigned a)
	:Coordenada{alp::narrow_cast<int>(a)}{}
};

// conversión de Coordenada a Longitud. Esto no tiene sentido matemáticamente.
// Estoy obligado a implementarlo porque he heredado Longitud de Coordenada.
// (me permite construir: Longitud a = 23_pix; // 23_pix = Coordenada)
inline Longitud::Longitud(Coordenada c)
	    :Coordenada{c}
{
    alp::precondicion(c.pix() >= 0, __FILE__, __LINE__
		    , "Longitud::Longitud(Coordenada)"
		    , "Intentando crear una longitud negativa!!!"
		      " Las longitudes son, por definición, positivas");
}

// conversión de Longitud a Coordenada. Matemáticamente siempre es correcto.
inline Coordenada::Coordenada(const Longitud& a)
    :num_pixeles_{alp::narrow_cast<int>(a.pix())}
{ }

inline Longitud& Longitud::operator-=(Longitud a)
{ 
    alp::precondicion(pix() >= a.pix(), __FILE__, __LINE__, 
	    "Longitud::operator-=", 
	    "Se está intentando restar una longitud [" 
	    + alp::to_string(pix())
	    + "] de [" + alp::to_string(a.pix()) + "]");

    Coordenada::operator-=(a); 
    return *this;
}

/// Devuelve la longitud como int. Nunca llamar a esta función
/// dentro de código mío o cliente. Es para convertirla con fltk.
/// \todo ¿Cómo dejar esta función de implementación, invisible
/// para el cliente de GUI?
//
// Es fundamental pasarle un const Longitud& y no por valor, ya que 
// no podemos construir una Longitud a partir de un Ancho. Si se pasa
// por valor, falla:
// Ancho a = 30_pix;
// fltk_to_int(a);  // Error: no es posible convertir Ancho en Longitud
inline int fltk_to_int(const Longitud& a) 
{return alp::narrow_cast<int>(a.pix());}


/*!
 *  \brief  Distancia es la medida que existe entre dos puntos.
 *
 *  Una cosa es distancia(A,B), que será la distancia que hay entre los
 *  puntos A y B, y otra cosa es la Coordenada que mide esta distancia. A esta
 *  Coordenada la llamamos también, por abuso del lenguaje, Distancia.
 *
 */
using Distancia = Longitud;

/*!
 *  \brief  Un ancho en GUI (medidos en pixeles o caracteres).
 *
 *  Un Ancho es una longitud que se puede medir en caracteres.
 *
 */
class Ancho:public Longitud{
public:
    // Devuelve el número de caracteres en que está medido este ancho.
    // unsigned car() const {return x_;}


    /// Devuelve el Ancho en pixeles que ocupa la cadena s.
    /// Ejemplo:
    /// \code
    ///	    Ancho a{"mi cadena"};   // a = ancho que ocupa 'mi cadena'
    /// \endcode
    Ancho(const std::string& s);

    /// Convertimos, por defecto de forma implicita, todas las Longitudes en 
    /// Anchos.
    Ancho(Longitud a);

    /// Convertimos, por defecto de forma implicita, todas las Coordenadas en 
    /// Anchos.
    Ancho(Coordenada a);


    /// Devuelve el Ancho asociado a x caracteres.
    /// Ejemplo:
    /// \code
    ///	    unsigned x = 10;
    ///	    Ancho a = Longitud::en_car(x);
    /// \endcode
    static Ancho en_car(unsigned num_caracteres);


private:
    // Devuelve el Ancho, pasado el número de pixeles como parámetro
    Ancho(unsigned num_pixeles):Longitud{num_pixeles}{}

    // Calcula la longitud, en pixeles, de n caracteres.
    static unsigned ancho_en_pixeles(unsigned n)
    { return ancho_en_pixeles(std::string(n,'A')); }

    // Calcula la longitud, en pixeles, que ocupa la cadena s.
    static unsigned ancho_en_pixeles(const std::string& s);


};


inline Ancho::Ancho(Longitud a)
    :Longitud{a}
{}

inline Ancho::Ancho(Coordenada a)
    :Longitud{a}
{}


inline Ancho::Ancho(const std::string& s)
    :Ancho{ancho_en_pixeles(s)}
{}


inline Ancho Ancho::en_car(unsigned num_caracteres)
{ return Ancho{ancho_en_pixeles(num_caracteres)}; }



/// inline namespace. Para usar estos literales, escribir 
/// using namespace gui::literals;
inline namespace literals{

/// Devuelve el Ancho asociado a x caracteres.
/// Ejemplo:
/// \code
///	    Ancho a = 200_car;
/// \endcode
inline Ancho operator""_car(const char* num_caracteres)
{ return Ancho::en_car(alp::to<unsigned>(num_caracteres)); }

}// namespace literals



/*!
 *  \brief  Un ancho en GUI (medidos en pixeles o caracteres).
 *
 *  Un Alto es una longitud que se puede medir en líneas.
 *
 */
class Alto:public Longitud{
public:
    /// Convertimos, por defecto de forma implicita, todas las Coordenadas en 
    /// Altos.
    Alto(Coordenada a)	
	:Longitud{a}{}

    /// Convertimos, por defecto de forma implicita, todas las Longitudes en 
    /// Altos.
    Alto(Longitud a)	
	:Longitud{a}{}

    
    /// Devuelve el Alto asociado a n lineas.
    /// Ejemplo:
    /// \code
    ///	    unsigned n = 10;
    ///	    Alto a = Alto::en_lin(n);
    /// \endcode
    static Alto en_lin(unsigned num_caracteres);



private:
    // Devuelve el Alto, pasado el número de pixeles como parámetro
    Alto(unsigned num_pixeles):Longitud{num_pixeles}{}

    // Calcula el alto que ocupan n lineas.
    static unsigned alto_en_pixeles(unsigned num_lineas);
};




inline Alto Alto::en_lin(unsigned num_lineas)
{ return Alto{alto_en_pixeles(num_lineas)}; }



/// inline namespace. Para usar estos literales, escribir 
/// using namespace gui::literals;
inline namespace literals{

/// Devuelve el Alto asociado a n lineas.
/// Ejemplo:
/// \code
///	    Alto a = 200_lin;
/// \endcode
inline Alto operator""_lin(const char* num_lineas)
{ return Alto::en_lin(alp::to<unsigned>(num_lineas)); }

}// namespace literals






/*!
 *  \brief  Tamaños que usamos en GUI. 
 *
 *  Tamaños de ventanas, de widgets, ..., de cualquier cosa.
 *
 */
struct Size{
    Ancho ancho;
    Alto alto;

    Size(Ancho a, Alto h):ancho{a}, alto{h}{}
};

/*!
 *  \brief  Posiciones que usamos en GUI.
 *
 *  Es la posición de una ventana, un widget... Se mide en pixeles.
 *
 */
struct Posicion{
    Coordenada x;
    Coordenada y;

    Posicion(Coordenada x, Coordenada y):x{x}, y{y}{}

    Posicion& operator+=(Posicion p);
    Posicion& operator-=(Posicion p);

    /// Devuelve la posición del punto (x,y), donde x e y están en píxeles.
    static Posicion en_pix(int x, int y)
    { return Posicion{Coordenada::en_pix(x), Coordenada::en_pix(y)}; }

};


inline Posicion& Posicion::operator+=(Posicion p)
{
    x+=p.x;
    y+=p.y;

    return *this;
}

inline Posicion& Posicion::operator-=(Posicion p)
{
    x-=p.x;
    y-=p.y;

    return *this;
}


/// Suma dos posiciones.
inline Posicion operator+(Posicion a, Posicion b)
{
    a+= b;
    return a;
}

/// Resta dos posiciones.
inline Posicion operator-(Posicion a, Posicion b)
{
    a-= b;
    return a;
}

/// Trazamos una posición.
inline std::ostream& operator<<(std::ostream& out, Posicion p)
{ return out << '(' << p.x << ", " << p.y << ')'; }


/*!
 *  \brief  Un rectángulo de una ventana.
 *
 *  Un rectángulo representa una región de una ventana.
 *
 *  Como no sé como implementarlo (¿uso x0, x1, y0, y1? ó ¿p0 y p1?)
 *  voy a dar funciones para acceder a los elementos. A parte quiero 
 *  garantizar que el rectángulo está bien construido, esto es, 
 *  que x0 <= x1 e y0 <= y1. Si permitiese acceso al usuario a las x,y
 *  directamente podría violar este invariante.
 *
 */
class Rectangulo{
public:
    Rectangulo(Posicion p0, Posicion p1);

    Posicion p0() const {return p0_;}
    Posicion p1() const {return p1_;}

    Coordenada x0() const {return p0_.x;}
    Coordenada y0() const {return p0_.y;}
    Coordenada x1() const {return p1_.x;}
    Coordenada y1() const {return p1_.y;}

private:
    Posicion p0_;
    Posicion p1_;
};

inline Rectangulo::Rectangulo(Posicion p0, Posicion p1)
    :p0_{p0}, p1_{p1}
{
    alp::precondicion((p0.x <= p1.x) and  (p0.y <= p1.y)
	    , __FILE__, __LINE__, "Rectangulo::Rectangulo(p0, p1)"
	    , "Intentando construir un rectángulo mal definido");
}


/// ¿p pertenece al rectángulo r?
inline bool pertenece(const Posicion& p, const Rectangulo& r)
{
    if(	   (r.x0() <= p.x) && (p.x <= r.x1())
	&& (r.y0() <= p.y) && (p.y <= r.y1())) return true;

    return false;
}




// TODO: eliminar esta clase
// Configuración del gui
class Cfg{
public:
    // Todas estas dimensiones están en pixeles.
    // dimensiones por defecto de los botones
    static int boton_alto;

    static unsigned menu_alto;
    static int linea_de_texto_alto;
};




namespace Letra{

inline Ancho ancho(){return Ancho::en_car(1);}
inline Alto alto(){return Alto::en_lin(1);}

}

/// Callbacks de FLTK
using Callback = void(*)(void*, void*);


namespace impl{
// Excepción que lanzo para terminar de forma ordenada el programa
// Nunca capturarla!!! (la captura gui_main)
struct Fin_programa{};
}

}// namespace gui

#endif

