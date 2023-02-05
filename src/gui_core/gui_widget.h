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
#ifndef __GUI_WIDGET_H__
#define __GUI_WIDGET_H__

#include "gui_fl.h"
#include "gui_tipos.h"

namespace gui{
/*!
 * \class Widget
 *
 * \brief  Clase genérica de todo widget. 
 *
 *	Una ventana es un contenedor de widgets. Una ventana NO es un widget.
 *
 *	    Un widget es algo que colocamos en una ventana. No tiene que 
 *	tener etiquetas ni nada parecido (fltk le asigna un label a todo
 *	widget, lo cual no tiene por qué ser necesario). Los widget solo 
 *	tienen que saber de:
 *		p0   = su posición dentro de la ventana.
 *		size = su tamaño
 *		borde= cómo dibujar su borde
 *
 *
 *	    Los widgets pueden ser:
 *	    + Grupo_de_controles: contienen controles.
 *	    + Control: es un control que sirve para algo.
 *		       Los controles a su vez están formados por controles 
 *		       básicos (por ejemplo, Control_etcon está formado 
 *		       por una etiqueta + un control (input, combo...)).
 *
 *	    (todavía no tengo claro si esta es la estructura adecuada)
 *
 *
 *	    Un Widget queda totalmente construido en el constructor, 
 *	sin embargo, no queda colocado en ninguna ventana. Hay que colocarlos
 *	explícitamente:
 *
 *	    class Ventana_prueba{
 *		Boton bt{"&Pulsame", cb_pulsame};
 *		...
 *		};
 *
 *	    Ventana_prueba::Ventana_prueba()
 *	    {
 *		bt.coloca(*this, Posicion{30, 50});
 *		...
 *	    }
 *
 *
 *	    En la práctica usaremos el maquetador para evitar tener que 
 *	calcular todas las coordenadas.
 *
 */
class Ventana;
class Grupo_de_controles;



// No es necesario destruir los widgets w_, ya que al destruir la ventana
// FLTK hace el delete de todo lo demás
// FLTK funciona de la siguiente manera:
//	1.- Creamos una ventana Fl_Window, que es un Fl_Group, definiendo
//	    en el constructor que ella es el grupo actual.
//
//	2.- Creamos un nuevo Fl_Widget (new Fl_Button{...})
//	    El constructor llama a parent->add, que se encarga de añadir
//	    el Widget al grupo actual.
//
//	3.- La ventana (el grupo) se destruye. Su destructor hace un delete
//	    de todos los widgets que contiene.
//
//  Observar que:
//	1.- La ventana hay que destruirla explícitamente (salvo que pertenezca
//	    a algún Fl_Group).
//	2.- En la práctica (de momento) no estoy destruyendo ninguna ventana.
//	    hide() se limita a esconderla, pero no libera la memoria. Esto
//	    para pequeñas aplicaciones es válido, pero para grandes no parece
//	    buena idea, pero ¿una aplicación cuantas ventanas reales tiene?
//	    Parecen muy pocas, así que esto no parece que sea un problema (o
//	    si?).
class Widget{
public:
    // prohibimos copiar Widgets
    Widget(const Widget&)	     = delete;
    Widget& operator=(const Widget&) = delete;

    Widget(Widget&&)		     = delete;
    Widget& operator=(Widget&&)	     = delete;

    virtual ~Widget(){}

    /// Coloca el widget en la ventana v, en la posición p0.
    virtual void coloca(Ventana& v, Posicion p0);

    /// Le indicamos al widget que lo hemos colocado en el grupo de controles g
    virtual void coloca(Grupo_de_controles& g) {}

    // -----------
    // de consulta
    // -----------
    /// Coordenada 'x' de la esquina superior izquierda
    // Tengo que definir x0 como virtual, ya que FLTK, en los Input usa
    // x0 como la posición del Input, no la del Widget, siendo incorrecto el 
    // x0 que devuelve w_.
    virtual Coordenada x0() const {return Coordenada::en_pix(w_->x());}

    /// Coordenada 'y' de la esquina superior izquierda
    Coordenada y0() const {return Coordenada::en_pix(w_->y());}

    /// Posicion de la esquina superior izquierda
    Posicion p0() const {return Posicion{x0(), y0()};}

    /// Coordenada 'x' de la esquina inferior derecha
    Coordenada x1() const {return x0()+ancho();}

    /// Coordenada 'y' de la esquina inferior derecha
    Coordenada y1() const {return y0()+alto();}

    /// Posición de la esquina inferior derecha
    Posicion p1() const {return Posicion{x1(), y1()};}

    /// Coordenadas del rectángulo que ocupa el widget en la ventana
    Rectangulo rectangulo() const {return Rectangulo{p0(), p1()};}


    /// \brief Devuelve el ancho, en pixeles, del widget.
    ///
    /// Tiene que ser virtual ya que para FLTK el tamaño de un Input_int
    /// no incluye el ancho de la etiqueta, pero para mi el tamaño del 
    /// widget es el tamaño completo: etiqueta + input.
    virtual Ancho ancho() const	{return Ancho::en_pix(w_->w());}

    /// Devuelve el alto, en pixeles, del widget.
    Alto alto()  const		{return Alto::en_pix(w_->h());}

    /// Devuelve el tamaño, en pixeles, del widget.
    Size size() const {return Size{ancho(), alto()};}

    // Modificación del tamaño y la posición
    //
    // FUNDAMENTAL: llamar al redraw de la ventana que contiene este
    // widget despues de llamar a esta función. Si no, no se ve el cambio!!!
    // Esta función es virtual, ya que para mi p0 es la posición donde empieza
    // el widget, mientras que para fltk en el caso del Input position es
    // donde empieza el Input, no la etiqueta del Input

    /// Coloca el widget en la posición indicada. Realmente lo recoloca
    /// ya que se da por supuesto que está colocado en alguna ventana o grupo.
    virtual void coloca(Coordenada x, Coordenada y)// {p0(x, y);}
				{w_->position(x.pix(), y.pix());}
    void coloca(Posicion p) //{p0(p);}
		{coloca(p.x, p.y);}


    /// Cambiamos el ancho a 'a' pixeles
    void ancho(Ancho a)  {size(a, alto());}

    /// Cambiamos el ancho a 'a' pixeles, máximo M pixeles.
    ///
    /// Ejemplo de uso: ancho(a, maximo(100));
    void ancho(Ancho a, alp::Maximo<Ancho> M)
    { size(std::min(a, M.valor), alto()); }

    /// Cambiamos el alto a 'h' pixeles
    void alto(Alto h)		{size(ancho(), h);}

    /// Cambiamos el alto a 'h' pixeles, máximo M pixeles.
    ///
    /// Ejemplo de uso: alto(h, maximo(30));
    void alto(Alto h, alp::Maximo<Alto> M)
    {size(ancho(), std::min(h, M.valor));}

    /// Cambiamos el tamaño a 'a x h'
    void size(Ancho a, Alto h)	
    {w_->size(fltk_to_int(a),fltk_to_int(h));}

    /// Cambiamos el tamaño a sz.
    void size(Size sz)	{size(sz.ancho, sz.alto);}

//    /// Cambiamos el tamaño a 'w x h' caracteres x líneas
//    /// \todo Al definir Longitud esta función sobra.
//    void size_en_caracteres(Ancho a, Alto h)	
//    {w_->size(fltk_to_int(a), fltk_to_int(h));}

    // de dibujo
    /// Redibuja el widget. Por defecto, fuerza que se redibuje el widget
    /// en el momento. Pasarle 'false' para que no lo haga en el momento.
    void redraw(bool redraw_ya = true)   
    {
	w_->redraw();
	if (redraw_ya) flush();
    }

    void flush()    {Fl::check();}

    /// Activa el widget.
    void enable()   {w_->activate();}

    /// Desactiva el widget, pintándolo en gris.
    void disable()  {w_->deactivate();}

    /// Mostramos el widget.
    void show()	    {w_->show();}

    /// Ocultamos el widget.
    void hide()	    {w_->hide();}

    /// Devuelve si el widget lo estamos mostrando o no.
    bool es_visible() const {return w_->visible();}

    /// Cuando el ratón se posa sobre un widget durante un tiempo,
    /// muestra el mensaje msg.
    void tooltip(const std::string msg) {w_->copy_tooltip(msg.c_str());}

    /// Marca el widget como redimensionable
    void resizable();



    /// Tipo de widgets
    enum class Tipo_borde{ 
	    ninguno = FL_NO_BOX,
	    elevado = FL_THIN_UP_FRAME,
	    solido = FL_BORDER_BOX,
	    plano  = FL_FLAT_BOX};

    void borde(Tipo_borde t)
	{w_->box(static_cast<Fl_Boxtype>(t));}

protected:
    Widget(Fl_Widget* w):w_{w}, v_{nullptr}
    { }

    // ------------------------
    // Funciones de etiqueta!!!
    // ------------------------
    // TODO: Estas dos funciones no deberían de estar en el widget!!!
    // Un widget no tiene por qué tener etiquetas!!! No hacerlas bajo 
    // ningún concepto public!
    std::string etiqueta() const;
    void etiqueta(const std::string& et);

    // devuelve la longitud de la etiqueta. Nombre feo para evitar usarla.
    Size fltk_measure_label() const;

    // devuelve el número de pixeles que ocupa la etiqueta
    unsigned fltk_ancho_label() const;  

    friend class Maquetador;
    friend class Grupo_de_controles;


    // Doy acceso a las clases hijas al control de fltk
    Fl_Widget* fl_widget() {return w_;}
    const Fl_Widget* fl_widget() const {return w_;}

    // TODO: solo hay un sitio donde uso esta función. ¿Cómo eliminarla?
    Ventana* ventana_no_usar() {return v_;}


private:
    Fl_Widget* w_ = nullptr;	// el widget pertenece a un Fl_Group, no a mi Widget
    Ventana* v_   = nullptr;	// ventana a la que pertenece

    
    // TODO: eliminarlo al eliminar la etiqueta del Widget.
    bool tiene_etiqueta = false;
};



inline std::string Widget::etiqueta() const
{
    if(tiene_etiqueta)	
	return std::string{w_->label()};

    return std::string{""};
}

inline void Widget::etiqueta(const std::string& et)
{
    w_->copy_label(et.c_str());

    tiene_etiqueta = true;
}


inline unsigned Widget::fltk_ancho_label() const
{
    auto sz = fltk_measure_label();
    return sz.ancho.pix();
}


/***************************************************************************
 *			    FUNCIONES AUXILIARES
 ***************************************************************************/
/// Redimensiona el ancho de los dos widgets al de mayor ancho.
void mismo_ancho_mayor(Widget& w1, Widget& w2);

/// Redimensiona el alto de los dos widgets al de mayor alto.
void mismo_alto_mayor(Widget& w1, Widget& w2);


/// Redimensiona los dos widgets de tal manera que sus dimensiones sean
/// las mayores (mayor ancho de los dos y mayor alto de los dos).
inline void  mismo_size_mayor(Widget& w1, Widget& w2)
{
    mismo_ancho_mayor(w1, w2);
    mismo_alto_mayor (w1, w2);
}

/// Redimensionamos w haciendo que tenga el mismo tamaño que w0.
inline void mismo_size_que(const Widget& w0, Widget& w)
{ w.size(w0.size()); }


}// namespace

#endif
