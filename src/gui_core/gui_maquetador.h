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

#ifndef __GUI_MAQUETADOR_H__
#define __GUI_MAQUETADOR_H__
/****************************************************************************
 *
 *   - DESCRIPCION: Funciones para maquetar una ventana de forma sencilla.
 *
 *   - COMENTARIOS: 
 *	    El maquetador sirve para maquetar ventanas. 
 *	    
 *   - HISTORIA:
 *           alp  - 01/08/2016 Escrito
 *		    12/04/2017 Reescrito. Añado alinea_dcha/izda...
 *
 ****************************************************************************/
#include "gui_base.h"
#include "gui_widget.h"
#include "gui_menu_bar.h"


namespace gui{
/*!
 *  \brief  Sirve para maquetar una ventana, para colocar los widgets
 *	    en la ventana.
 *  
 *  Permite maquetar una ventana de forma descriptiva, sin necesidad
 *  de pasar explícitamente las posiciones donde colocar los widgets.
 *
 *	+ a_la_dcha, debajo,...:
 *		colocan el widget en la posición indicada dejando 
 *		un margen.
 *
 *	+ La versión justo_ (justo_a_la_dcha,...):
 *		no dejan el margen.
 *
 *	+ a_la_dcha_de(w0, w): coloca el widget w a la derecha de w0.
 *
 *	Por defecto, las funciones 'debajo' alinean a la izda. Si se quiere
 *	alinear a la dcha, usar debajo_alineado_a_la_dcha. Si se quieren
 *	alinear varios widgets todos a la dcha, usar:
 *	
 *	Ejemplo:
 *	\code
 *		Maquetador m;
 *		m.alinea_a_la_dcha();	// a partir de aquí todo alineado dcha
 *		m.debajo(w);		
 *		...
 *	
 *	    // Otra posibilidad podría ser:
 *	    m.en_columna() << alineado_dcha
 *			    << widget01
 *			    << widget02
 *			    << widget03;
 *
 *	    m.en_fila() << alineados_arriba << widget01 << widget02;
 *
 *	    // Incluso podríamos crear grupos:
 *	    m.grupo_columna() << ...
 *
 *	\endcode
 */
class Maquetador{
public:
    /// El maquetador colocará todos los widgets en la ventana v0
    Maquetador(Ventana& v0);

    /// Cuando colocamos los widgets debajo/encima los alineamos a la derecha
    void alinea_a_la_dcha();

    /// Cuando colocamos los widgets debajo/encima los alineamos a la izquierda
    void alinea_a_la_izda();

    /// Cuando colocamos los widgets debajo/encima los alineamos al centro.
    void alinea_al_centro();

    /// Colocamos el primer widget en la posición p0
    void primer_widget(Widget& w, Posicion p0);

    /// Colocamos el primer widget en la posición (margen_horizontal_,
    /// margen_vertical_).
    void primer_widget(Widget& w);

    /// Cuando una ventana tenga menu_bar, colocar el menu como primer widget
    void primer_widget(Menu_bar& w);

    // Si el usuario se confunde y llama ha esta función, le dará un error
    // de compilación, ya que no la defino
    void primer_widget(Menu_bar& w, Posicion p0);

    /// Seleccionamos el widget w para como widget actual
    void selecciona(const Widget& w);

    // ---------
    // a la dcha
    // ---------
    /// Colocamos el widget w a la derecha del último widget colocado
    void a_la_dcha(Widget& w);

    /// Colocamos el widget w justo a la derecha del último widget colocado
    /// Esto es: no dejamos márgenes entre los widgets.
    void justo_a_la_dcha(Widget& w);

    /// Colocamos w a la derecha de w0. Dejamos espacio entre los widgets.
    void a_la_dcha_de(const Widget& w0, Widget& w);

    /// Colocamos w justo a la derecha de w0. No dejamos espacio entre los widgets.
    void justo_a_la_dcha_de(const Widget& w0, Widget& w);

    /// Colocamos w a lal derecha del último widget colocado, dejando el 
    /// espacio_horizontal indicado.
    void a_la_dcha(Widget& w, Distancia espacio_horizontal);

    // ---------
    // a la izda
    // ---------
    /// Colocamos el widget w a la izquierda del último widget colocado
    void a_la_izda(Widget& w);

    /// Colocamos el widget w justo a la derecha del último widget colocado
    /// Esto es: no dejamos márgenes entre los widgets.
    void justo_a_la_izda(Widget& w);

    /// Colocamos w a la izquierda de w0. Dejamos espacio entre los widgets.
    void a_la_izda_de(const Widget& w0, Widget& w);

    /// Colocamos w justo a la izquierda de w0. No dejamos espacio entre los widgets.
    void justo_a_la_izda_de(const Widget& w0, Widget& w);

    /// Colocamos w a la izquierda del último widget colocado, dejando el 
    /// espacio_horizontal indicado.
    void a_la_izda(Widget& w, Distancia espacio_horizontal);

    // --------
    //  debajo
    // --------
    /// Colocamos el widget w debajo del último widget colocado
    void debajo(Widget& w);

    /// Colocamos el widget w justo debajo del último widget colocado
    void justo_debajo(Widget& w);

    /// Colocamos w debajo de w0. Dejamos espacio entre los widgets.
    void debajo_de(const Widget& w0, Widget& w);

    /// Colocamos w justo debajo de w0. No dejamos espacio entre los widgets.
    void justo_debajo_de(const Widget& w0, Widget& w);
 
    /// Colocamos w debajo del último widget colocado, dejando el 
    /// espacio_vertical indicado.
    void debajo(Widget& w, Distancia espacio_vertical);

    /// Colocamos w a la derecha de w0 y debajo de w1
    void a_la_dcha_y_debajo_de(const Widget& w0, const Widget& w1, Widget& w);

    // void debajo_alineado_a_la_dcha(Widget& w);


    // --------
    //  encima 
    // --------
    /// Colocamos el widget w encima del último widget colocado
    void encima(Widget& w);

    /// Colocamos el widget w justo encima del último widget colocado
    void justo_encima(Widget& w);

    /// Colocamos w encima de w0. Dejamos espacio entre los widgets.
    void encima_de(const Widget& w0, Widget& w);

    /// Colocamos w justo encima de w0. No dejamos espacio entre los widgets.
    void justo_encima_de(const Widget& w0, Widget& w);
 
    /// Colocamos w encima del último widget colocado, dejando el 
    /// espacio_vertical indicado.
    void encima(Widget& w, Distancia espacio_vertical);


    // -----------------
    // Sobre el anterior
    // -----------------
    /// Coloca el widget en la misma posición que el último widget colocado.
    /// La idea es colocar dos widgets en la misma posición y ocultar uno de
    /// ellos. Al pulsar alguna tecla, se muestra el ocultado, ocultando el 
    /// que estaba visible.
    void en_la_misma_posicion(Widget& w);


    /// Coloca el widget w en la misma posición que ocupa w0
    void en_la_misma_posicion_que(const Widget& w0, Widget& w);

//    // ---------------------
//    // debajo - Widget_etcon
//    // ---------------------
//    /// Colocamos el widget w debajo del último widget colocado.
//    /// Por defecto, alinea los inputs
//    void debajo(Widget_etcon& w);
//
//    /// Colocamos el widget w justo debajo del último widget colocado
//    void justo_debajo(Widget_etcon& w);
//
//    /// Colocamos w debajo de w0. Dejamos espacio entre los widgets.
//    void debajo_de(const Widget_etcon& w0, Widget_etcon& w);
//
//    /// Colocamos w justo debajo de w0. No dejamos espacio entre los widgets.
//    void justo_debajo_de(const Widget_etcon& w0, Widget_etcon& w);
// 
//    /// Colocamos w debajo del último widget colocado, dejando el 
//    /// espacio_vertical indicado.
//    void debajo(Widget_etcon& w, Distancia espacio_vertical);

    // misma función que antes, pero con el nombre al revés (así no hay que
    // andar recordando en qué orden se escribía esta función)
//    void debajo_y_a_la_dcha_de(const Widget& w0, const Widget& w1, Widget& w);

    // Algunos widgets los alineamos, no a la derecha, sino en un punto xm
    // intermedio. Por ejemplo: los Input, la derecha del widget es donde
    // empieza la etiqueta. Queda mejor alinearlos donde empieza el input.
    // OJO: coloca el xm de w justo debajo del xm de w0!!!
//    void debajo_de_xm(const Widget& w0, Widget& w);


    /// Pegamos el widget w debajo de w0, pero pegado al lado derecho de la
    /// ventana.
//    void pegado_al_lado_dcho_de_la_ventana_y_debajo_de
//				(const Widget& w0, Widget& w);



    // ----------------------------------
    // funciones para mover el maquetador
    // ----------------------------------

    /// Mueve el maquetador una línea hacia abajo.
    void linea_en_blanco() {lineas_en_blanco(1);}

    /// Mueve el maquetador n líneas hacia abajo.
    void lineas_en_blanco(int n);

    /// El maquetador se mueve colocándose justo al lado izquierdo de la
    /// ventana.
    /// \param[in] n: es el número de margenes que deja desde el lado derecho.
    void muevete_al_lado_izdo_de_la_ventana(int n = 1);

    /// El maquetador se mueve hacia la dcha la distancia 'd'.
    /// 
    /// Como 'd' es una coordenada, si se le pasa una coordenada negativa
    /// se moverá hacia la izquierda en lugar de la derecha. 
    void muevete_a_la_dcha(Coordenada d);

//    /// El maquetador se mueve hacia la dcha n margenes x
//    void muevete_a_la_dcha_margen_x(int num_margenes_x = 1);

    /// El maquetador se mueve hacia abajo la distancia 'd'.
    void muevete_abajo(Coordenada d);	

    /// Colocamos el maquetador alineado a la izquierda del w1.
    /// Esta función no modifica la altura en la que se encuentra el
    /// maquetador. Quedará colocado alineado con w1, pero a la altura de w0.
    void alinea_a_la_izda_de(const Widget& w1);


    // --------------------
    // Funciones de formato
    // --------------------
    /// Ancho de la ventana que contiene a este widget como el widget que 
    /// está más a la derecha de la ventana.
    Ancho ancho_ventana(const Widget& mas_a_la_izda);
    
    /// Alto de la ventana que contiene a este widget como el widget que 
    /// está en la parte más inferior de la ventana.
    Alto alto_ventana(const Widget& mas_abajo);


    // -----------------------
    // Maquetación por defecto
    // -----------------------
    /// Devuelve el espacio horizontal que se deja por defecto entre 
    /// widgets colocados uno al lado del otro.
    Distancia espacio_horizontal() const{return espacio_horizontal_;}

    /// Devuelve el espacio vertical que se deja por defecto entre 
    /// widgets colocados uno encima de otro.
    Distancia espacio_vertical() const{return espacio_vertical_;}

    /// Le indicamos al maquetador, que a partir de ahora deje una distancia
    /// 'd' entre widgets, al colocarlos horizontalmente.
    void espacio_horizontal(Distancia d) {espacio_horizontal_ = d;}

    /// Le indicamos al maquetador, que a partir de ahora deje una distancia
    /// 'd' entre widgets, al colocarlos verticalmente.
    void espacio_vertical(Distancia d) {espacio_vertical_ = d;}

    /// Redimensionamos la ventana de tal manera que entren todos los widgets
    /// Deja los márgenes indicados.
    void resize_window(Ancho margen_x = 15_pix, Alto margen_y = 15_pix)
    { v.size(size_ventana.x + margen_x, size_ventana.y + margen_y); }


private:
    // ventana donde colocamos los widgets
    Ventana& v;

    // posiciones actuales (pa) a partir de donde construimos el siguiente Widget
    // Esta es la información clave que me permite calcular las coordenadas
    // del siguiente widget:
    // pa_esquina_II = esquina II del ultimo widget
    // pa_esquina_SD = esquina SD del ultimo widget
    Posicion pa_esquina_II = {0_pix,0_pix};
    Posicion pa_esquina_SD  = {0_pix,0_pix};

    // Alineamiento
    enum class Tipo_alineamiento{dcha, izda, centro};

    // por defecto alineamos a la izda
    Tipo_alineamiento alinea_ = Tipo_alineamiento::izda;


    // margenes de hoja 
    // (¿crear margen_dcho, margen_izdo, margen_superior y margen_inferior?)
    Distancia margen_horizontal_  = 5_pix; // = margen_dcho = margen_izdo
    Distancia margen_vertical_    = 5_pix; // = margen_superior = margen_inferior

    // márgenes entre widgets
    Distancia espacio_horizontal_ = 5_pix;
    Distancia espacio_vertical_   = 5_pix;


    Alto alto_linea;


    // Información para poder redimensionar la ventana despues de colocar
    // todos los widgets, adaptándola al tamaño de los widgets.
    Posicion size_ventana {0_pix, 0_pix};


    // funciones auxiliares para calcular la posición actual del maquetador
    Posicion esquina_SD(const Widget& w);
    Posicion esquina_II(const Widget& w);

    // de implementación
    void debajo_alineado_a_la_dcha(Widget& w, Distancia margen_y);

    // coloca el widget w en la ventana en la posición p0
    // Además, actualiza información para poder calcular el tamaño final
    // de la ventana.
    void coloca(Widget& w, const Posicion& p0);

    void update_size_ventana(const Posicion& p0);
};


inline Maquetador::Maquetador(Ventana& v0)
    :v(v0)
    , alto_linea{Letra::alto()}
{}

inline Posicion Maquetador::esquina_SD(const Widget& w)
{return (w.p0() + Posicion{w.ancho(),0_pix});}

inline Posicion Maquetador::esquina_II(const Widget& w)
{return (w.p0() + Posicion{0_pix,w.alto()});}

// seleccionamos el widget w para como widget actual
inline void Maquetador::selecciona(const Widget& w)
{
    pa_esquina_II = esquina_II(w);
    pa_esquina_SD = esquina_SD(w);
}

inline void Maquetador::coloca(Widget& w, const Posicion& p0)
{
    w.coloca(v, p0); 
    
    //update_size_ventana(p0);
    update_size_ventana(w.p1());
}

inline void Maquetador::update_size_ventana(const Posicion& p0)
{
    size_ventana.x = std::max(size_ventana.x, p0.x);
    size_ventana.y = std::max(size_ventana.y, p0.y);
}

// Funciones genéricas
// espacio = espacio horizontal que dejamos con el anterior widget.
inline void Maquetador::a_la_dcha(Widget& w, Distancia espacio)
{ 
    // w.coloca(v, pa_esquina_SD + Posicion{espacio, 0_pix}); 
    coloca(w, pa_esquina_SD + Posicion{espacio, 0_pix}); 
    selecciona(w);
}


inline void Maquetador::a_la_izda(Widget& w, Distancia margen_x)
{ 
    auto x0 = pa_esquina_II.x - margen_x - w.ancho();
    auto y0 = pa_esquina_SD.y;

    // w.coloca(v, {x0, y0}); 
    coloca(w, {x0, y0}); 

    selecciona(w);
}

inline void Maquetador::debajo(Widget& w, Distancia margen_y)
{ 
    // auto x0 = calcula_x0();	 <--- no me gusta calcula_x0. ¿Cómo llamarlo?
    Coordenada x0 = 0_pix;
    switch(alinea_){
	case Tipo_alineamiento::dcha:
	    x0 = pa_esquina_SD.x-Coordenada{w.ancho()};
	    break;

	case Tipo_alineamiento::izda:
	    x0 = pa_esquina_II.x;
	    break;

	case Tipo_alineamiento::centro:
	    x0 = (pa_esquina_SD.x + pa_esquina_II.x - Coordenada{w.ancho()})/2;
	    break;
    }
    // FIN: auto x0 = calcula_x0();

    auto p = Posicion{x0, pa_esquina_II.y + margen_y};
    coloca(w,  p); 
    selecciona(w);
}

inline void Maquetador::en_la_misma_posicion(Widget& w)
{
    coloca(w,  {pa_esquina_II.x, pa_esquina_SD.y}); 
    selecciona(w);
}


inline void Maquetador::en_la_misma_posicion_que(const Widget& w0, Widget& w)
{
    selecciona(w0);
    en_la_misma_posicion(w);
}


inline void Maquetador::encima(Widget& w, Distancia margen_y)
{ 
    // este calcula_x0 es el mismo que se usa en debajo
    // auto x0 = calcula_x0();	 <--- no me gusta calcula_x0. ¿Cómo llamarlo?
    Coordenada x0 = 0_pix;
    switch(alinea_){
	case Tipo_alineamiento::dcha:
	    x0 = pa_esquina_SD.x-Coordenada{w.ancho()};
	    break;

	case Tipo_alineamiento::izda:
	    x0 = pa_esquina_II.x;
	    break;

	case Tipo_alineamiento::centro:
	    x0 = (pa_esquina_SD.x + pa_esquina_II.x - Coordenada{w.ancho()})/2;
	    break;
    }
    // FIN: auto x0 = calcula_x0();

    auto p = Posicion{x0, pa_esquina_SD.y - margen_y - w.alto()};
    // w.coloca(v,  p); 
    coloca(w,  p); 
    selecciona(w);
}


//inline void Maquetador::debajo_alineado_a_la_dcha(Widget& w, int a, int h, int margen_y)
//{ 
//    Posicion pa {pa_esquina_SD.x()-a, pa_esquina_II.y()+margen_y};
//
//    w.coloca(v, pa); 
//
//    pa_esquina_II = esquina_II(w);
//    pa_esquina_SD  = esquina_SD(w);
//}
//
//
// Funciones particulares
inline void Maquetador::primer_widget(Menu_bar& m)
{ 
    m.coloca(v); 
    selecciona(m);
}

inline void Maquetador::primer_widget(Widget& w)
{ primer_widget(w, Posicion{margen_horizontal_, margen_vertical_}); }


inline void Maquetador::primer_widget(Widget& w, Posicion p0)
{ 
    // w.coloca(v, p0); 
    coloca(w, p0); 
    selecciona(w);
}



// ---------
// a la dcha
// ---------
inline void Maquetador::a_la_dcha(Widget& w)
{ a_la_dcha(w, espacio_horizontal_); }

inline void Maquetador::justo_a_la_dcha(Widget& w)
{ a_la_dcha(w, 0_pix);}

inline void Maquetador::a_la_dcha_de(const Widget& w0, Widget& w)
{
    selecciona(w0);
    a_la_dcha(w);
}

inline void Maquetador::justo_a_la_dcha_de(const Widget& w0, Widget& w)
{
    selecciona(w0);
    justo_a_la_dcha(w);
}


// ---------
// a la izda 
// ---------
inline void Maquetador::a_la_izda(Widget& w)
{ a_la_izda(w, espacio_vertical_); }

inline void Maquetador::justo_a_la_izda(Widget& w)
{ a_la_izda(w, 0_pix); }

inline void Maquetador::a_la_izda_de(const Widget& w0, Widget& w)
{
    selecciona(w0);
    a_la_izda(w);
}

inline void Maquetador::justo_a_la_izda_de(const Widget& w0, Widget& w)
{
    selecciona(w0);
    justo_a_la_izda(w);
}


// --------
//  debajo
// --------
inline void Maquetador::debajo(Widget& w)
{ debajo(w, espacio_vertical_); }

inline void Maquetador::justo_debajo(Widget& w)
{ debajo(w, 0_pix); }


inline void Maquetador::debajo_de(const Widget& w0, Widget& w)
{
    selecciona(w0);
    debajo(w);
}

inline void Maquetador::justo_debajo_de(const Widget& w0, Widget& w)
{
    selecciona(w0);
    justo_debajo(w);
}



//inline void Maquetador::debajo_alineado_a_la_dcha(Widget& w)
//{ debajo_alineado_a_la_dcha(w, w.ancho_por_defecto(v), w.alto_por_defecto(v));}
//
//inline void Maquetador::debajo_alineado_a_la_dcha(Widget& w, int a, int h)
//{ debajo_alineado_a_la_dcha(w, a, h, espacio_vertical_);}
//

inline void Maquetador::a_la_dcha_y_debajo_de(const Widget& w0, const Widget& w1
			      , Widget& w)
{
    Posicion pa{w0.x1(), w1.y1()};

    // w.coloca(v, pa + Posicion{espacio_horizontal_, espacio_vertical_}); 
    coloca(w, pa + Posicion{espacio_horizontal_, espacio_vertical_}); 

    selecciona(w);
}


// --------
//  encima 
// --------
inline void Maquetador::encima(Widget& w)
{ encima(w, espacio_vertical_); }


inline void Maquetador::justo_encima(Widget& w)
{ encima(w, 0_pix); }


inline void Maquetador::encima_de(const Widget& w0, Widget& w)
{
    selecciona(w0);
    encima(w);
}

inline void Maquetador::justo_encima_de(const Widget& w0, Widget& w)
{
    selecciona(w0);
    justo_encima(w);
}


//inline void Maquetador::debajo_y_a_la_dcha_de
//		    (const Widget& w0, const Widget& w1, Widget& w)
//{a_la_dcha_y_debajo_de(w1, w0, w);}
//
//inline void Maquetador::debajo_y_a_la_dcha_de
//		    (const Widget& w0, const Widget& w1 , Widget& w
//		     , int a, int h)
//{a_la_dcha_y_debajo_de(w1, w0, w, a, h);}
//
//inline void Maquetador::debajo_de_xm(const Widget& w0, Widget& w)
//{ debajo_de_xm(w0, w, w.ancho_por_defecto(v), w.alto_por_defecto(v)); }
//
//inline void Maquetador::debajo_de_xm(const Widget& w0, Widget& w, int a, int h)
//{
//    // posición actual Inferior Media
//    Posicion pa_IM{w0.xm(), w0.y0()+w0.alto()};
//
//    w.construye_pm(v, pa_IM + Posicion{0, espacio_vertical_}, a, h); 
//
//    pa_esquina_II = esquina_II(w);
//    pa_esquina_SD  = esquina_SD(w);
//}
//
//
//inline void Maquetador::pegado_al_lado_dcho_de_la_ventana_y_debajo_de
//				(const Widget& w0, Widget& w)
//{
//    muevete_al_lado_dcho_de_la_ventana();
//    debajo_de(w0, w);
//}


//inline void Maquetador::pegado_al_lado_dcho_de_la_ventana_y_debajo_de
//				(const Widget& w0, Widget& w, int a, int h)
//{
//    Posicion pa{v.ancho()-a-espacio_horizontal_, w0.y1()+espacio_vertical_};
//
//    w.coloca(v, pa); 
//
//    pa_esquina_II = esquina_II(w);
//    pa_esquina_SD  = esquina_SD(w);
//}




inline void Maquetador::lineas_en_blanco(int n)
{
    Coordenada incr_y = n*alto_linea;
    pa_esquina_II += Posicion{0_pix, incr_y};
    pa_esquina_SD += Posicion{0_pix, incr_y};
}

inline void Maquetador::muevete_al_lado_izdo_de_la_ventana(int n)
{
    auto margen_x = n*espacio_horizontal_;

    pa_esquina_SD = Posicion{pa_esquina_SD.x - pa_esquina_II.x + margen_x, 
			     pa_esquina_SD.y};

    pa_esquina_II = Posicion{margen_x, pa_esquina_II.y};
}



inline void Maquetador::muevete_a_la_dcha(Coordenada d)
{
    Posicion incr {d, 0_pix};

    pa_esquina_II += incr;
    pa_esquina_SD += incr;
}

//inline void Maquetador::muevete_a_la_dcha_margen_x(int num_margenes_x)
//{
//    pa_esquina_II += {num_margenes_x*espacio_horizontal_, 0_pix};
//    pa_esquina_SD += {num_margenes_x*espacio_horizontal_, 0_pix};
//}

inline void Maquetador::muevete_abajo(Coordenada d)
{
    pa_esquina_II += {0_pix, d};
    pa_esquina_SD += {0_pix, d};
}


inline void Maquetador::alinea_a_la_izda_de(const Widget& w1) 
{
    pa_esquina_II.x = w1.x0();

    alinea_a_la_izda();
}



inline Ancho Maquetador::ancho_ventana(const Widget& mas_a_la_izda)
{
    return (mas_a_la_izda.x1() + margen_horizontal_);
}


inline Alto Maquetador::alto_ventana(const Widget& mas_abajo)
{
    return (mas_abajo.y1() + margen_vertical_);
}


// Cuando colocamos los widgets debajo los alineamos a la derecha
inline void Maquetador::alinea_a_la_dcha()
{alinea_ = Tipo_alineamiento::dcha;}

// Cuando colocamos los widgets debajo los alineamos a la izquierda
inline void Maquetador::alinea_a_la_izda()
{alinea_ = Tipo_alineamiento::izda;}

// Cuando colocamos los widgets debajo los alineamos al centro
inline void Maquetador::alinea_al_centro()
{alinea_ = Tipo_alineamiento::centro;}





/*!
 *  \brief  Sirve para maquetar grupos de widgets horizontalmente.
 *
 *  No es mas que un wrapper de la función a_la_dcha() del Maquetador.
 *  Es syntactic sugar.
 *
 *  Ejemplo:
 *  \code
 *	// colocamos 3 etiquetas una detrás de otra. Por defecto dejamos
 *	// un espacio horizontal entre cada widget.
 *	grupo_horizontal(m) << et01 << et02 << et03;
 *
 *	// colocamos 3 etiquetas una detrás de otra, sin dejar espacio
 *	// horizontal entre ellas.
 *	grupo_horizontal(m, 0_pix) << et01 << et02 << et03;
 *  \endcode
 *  
 *  Cuidado: et01 se coloca a la derecha del último widget que el maquetador
 *  m hubiera colocado.
 *
 *  Esta clase es de implementación. NO DEJARLA DOCUMENTADA EN EL INTERFAZ!!!
 *  ¿prohibir su uso por parte del cliente? Sí. ¿cómo? (???)
 */
class Maquetador_horizontal{
public:
    // Crea un maquetador de grupos horizontales, dejando entre los widgets
    // el espacio horizontal 'd'.
    Maquetador_horizontal(Maquetador& m, Distancia d);

    friend const Maquetador_horizontal& operator<<
	    (const Maquetador_horizontal& m, Widget& w);
private:
    Maquetador& m_;
    Distancia d_;	// distancia que dejamos entre los widgets al colocarlos
};



inline Maquetador_horizontal::Maquetador_horizontal
    (Maquetador& m, Distancia d)
    :m_{m}, d_{d}
{}


inline const Maquetador_horizontal& operator<<
	    (const Maquetador_horizontal& mh, Widget& w)
{
    mh.m_.a_la_dcha(w, mh.d_);
    return mh;
}

/// Crea un grupo_horizontal para maquetar la ventana, usando el maquetador
/// m, y dejando entre los widgets la distancia por defecto que hubiera.
inline Maquetador_horizontal 
grupo_horizontal(Maquetador& m)
{
    return Maquetador_horizontal{m, m.espacio_horizontal()};
}

/// Crea un grupo_horizontal para maquetar la ventana, usando el maquetador
/// m, y dejando una distancia entre los widgets 'd'.
inline Maquetador_horizontal 
grupo_horizontal(Maquetador& m, Distancia d)
{
    return Maquetador_horizontal{m, d};
}



/*!
 *  \brief  Sirve para maquetar grupos de widgets verticalmente.
 *
 *  No es mas que un wrapper de la función debajo() del Maquetador.
 *  Es syntactic sugar.
 *
 *  Ejemplo:
 *  \code
 *	// colocamos 3 etiquetas una detrás de otra. Por defecto dejamos
 *	// un espacio vertical entre cada widget.
 *	grupo_vertical(m)   << et01 
 *			    << et02 
 *			    << et03;
 *
 *	// colocamos 3 etiquetas una detrás de otra, sin dejar espacio
 *	// verticual entre ellas.
 *	grupo_vertical(m, 0_pix)    << et01 
 *				    << et02 
 *				    << et03;
 *  \endcode
 *  
 *  Cuidado: et01 se coloca debajo del último widget que el maquetador
 *  m hubiera colocado.
 *
 *  Esta clase es de implementación. NO DEJARLA DOCUMENTADA EN EL INTERFAZ!!!
 *  ¿prohibir su uso por parte del cliente? Sí. ¿cómo? (???)
 */
class Maquetador_vertical{
public:
    // Crea un maquetador de grupos verticales, dejando entre los widgets
    // el espacio vertical 'd'.
    Maquetador_vertical(Maquetador& m, Distancia d);

    friend const Maquetador_vertical& operator<<
	    (const Maquetador_vertical& m, Widget& w);
private:
    Maquetador& m_;
    Distancia d_;	// distancia que dejamos entre los widgets al colocarlos
};


inline Maquetador_vertical::Maquetador_vertical
    (Maquetador& m, Distancia d)
    :m_{m}, d_{d}
{}


inline const Maquetador_vertical& operator<<
	    (const Maquetador_vertical& mh, Widget& w)
{
    mh.m_.debajo(w, mh.d_);
    return mh;
}

/// Crea un grupo_vertical para maquetar la ventana, usando el maquetador
/// m, y dejando entre los widgets la distancia por defecto que hubiera.
inline Maquetador_vertical 
grupo_vertical(Maquetador& m)
{
    return Maquetador_vertical{m, m.espacio_vertical()};
}

/// Crea un grupo_vertical para maquetar la ventana, usando el maquetador
/// m, y dejando una distancia entre los widgets 'd'.
inline Maquetador_vertical 
grupo_vertical(Maquetador& m, Distancia d)
{
    return Maquetador_vertical{m, d};
}

/*!
 *  \class Maquetador_grupo
 *
 *  \brief  Concebimos el maquetador como si fuera un flujo donde vamos
 *	colocando los widgets.
 *
 *  Ejemplo:
 *  \code
 *	grupo(m) << incr << gui::endl <--- DE MOMENTO NO ME COMPILA!!!
 *	auto g = grupo(m);
 *	g	 << incr << gui::endl
 *		 << x_min << et_x << x_max << endl
 *		 << y_min << et_y << y_max << endl
 *		 << color;
 *  \endcode
 *  
 *  La ventaja de esto es que el código muestra la disposición de los
 *  widgets en la ventana. La desventaja es que no podemos elegir de forma
 *  aleatoria donde colocarlos. Aquí siempre los colocamos a la derecha, o
 *  debajo.
 *
 *  DUDA: Lo llamo Maquetador_grupo por consistencia con los otros grupos, 
 *  pero ¿no sería mejor Maquetador_como_flujo?
 *
 *  \todo grupo(m) << r1 << g1 << b1 << espacio_horizontal(10_car) << ...
 */


class Maquetador_grupo{
public:
    Maquetador_grupo(Maquetador& m):m_{&m}{}

    friend Maquetador_grupo& operator<<(Maquetador_grupo& mg, Widget& w);

    /// Manipuladores: endl, ...
    Maquetador_grupo& operator<<(Maquetador_grupo& (*pf)(Maquetador_grupo&))
    {
	(*pf)(*this);
	return *this;
    }

    void new_line() {new_line_ = true;}

private:

    Maquetador* m_ = nullptr;

    // primer widget de la última línea que hemos colocado:
    // grupo(m) << uno << endl
    //		<< dos << tres <<   <--- aqui: primer_widget_ = dos;
    // los widgets al dar un retorno de carro)
    const Widget* primer_widget_ = nullptr;   

    // indica si hay que escribir a la dcha o debajo
    bool new_line_ = false;


    // Implementación de la función grupo:
    // En principio quería hacer lo mismo que he hecho con
    // Maquetador_horizontal, donde grupo(m) devuelva Maquetador_grupo{m};
    // El problema es que en esta ocasión el operator<< modifica 
    // Maquetador_grupo, con lo que no se le puede pasar un const &. Al 
    // llamar a grupo(m) el compilador da un error (a fin de cuentas, se 
    // esta modificando un rvalue con <<, seguramente fuese un error, aunque
    // en este caso no lo es). Para evitar este error creo esta variable
    // estatica y grupo devuelve grupo_. Si se usa el idioma que indico en el
    // ejemplo no habrá ningún problema, pero si se quieren construir dos
    // grupos diferentes a la vez, resulta imposible. ¿Cómo evitar este 
    // rodeo y hacerlo como Maquetador_horizontal?
    Maquetador_grupo(){}
    static Maquetador_grupo grupo_;
    friend Maquetador_grupo& grupo(Maquetador& m);
};


inline 
Maquetador_grupo& operator<< (Maquetador_grupo& mg, Widget& w)
{
    if(mg.new_line_){
	if(mg.primer_widget_ != nullptr)
	    mg.m_->selecciona(*mg.primer_widget_);

	mg.m_->debajo(w);

	mg.primer_widget_ = &w;
	mg.new_line_ = false;

    }
    else	 
	mg.m_->a_la_dcha(w);

    // si es el primer widget, lo anotamos
    if(mg.primer_widget_ == nullptr)
	mg.primer_widget_ = &w;

    return mg;
}


/// Crea un grupo, conviertiendo al maquetador m en un flujo.
inline Maquetador_grupo& grupo(Maquetador& m)
{
    Maquetador_grupo::grupo_.m_ = &m;
    return Maquetador_grupo::grupo_;
    // return Maquetador_grupo{m};
}


/// Manejador endl
inline Maquetador_grupo& endl(Maquetador_grupo& m)
{
    m.new_line();
    return m;
}


}// namespace gui

#endif
