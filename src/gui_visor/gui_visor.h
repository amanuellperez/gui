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

#ifndef __GUI_VISOR_H__
#define __GUI_VISOR_H__
/****************************************************************************
 *
 *   - DESCRIPCION: Widget del paquete gui_visor.
 *
 *   - COMENTARIOS: Definimos los controles necesarios para manejar visores.
 *	    Un visor es un control usado para mostrar imágenes. Las clases que
 *	    defino aquí encapsulan las de FLTK.
 *
 *	    Este paquete depende de img y gui.
 *
 *	    Un visor es un control que muestra una región de una imagen.
 *
 *   - HISTORIA:
 *     A. Manuel Lopez - 24/01/2017 Escrito
 *			 12/02/2017 Elimino la clase IRaton.
 *			 11/04/2017 Construyo los widgets en el constructor
 *			 02/03/2019 Reescrito. Uso subimagen.
 *
 ****************************************************************************/
#include "gui_base.h"
#include "gui_widget.h"
#include "gui_fl_visor.h"

#include "img.h"

namespace gui{

/*!
 *  \brief  Visor de imágenes.
 *
 *  Muestra una parte de una imagen img0.
 *
 *  Es una subimagen sobre la que colocamos un cristal.
 *
 *  Para el programador un visor es una Subimagen_view de la imagen que
 *  mostramos img0, a la que le hemos colocado un cristal encima donde podemos
 *  dibujar. De esta forma, podemos mostrar en pantalla (lo que ve el
 *  usuario):
 *	1.- Solo la subimagen original.
 *	2.- Solo lo que hemos dibujado en el cristal.
 *	3.- Tanto la subimagen original como lo dibujado sobre el cristal.
 *
 *  De esta forma podemos dibujar encima de una imagen sin modificarla.
 *  Realmente, donde dibujamos es encima del cristal.
 *
 *
 *  Para el usuario de la aplicación es una ventana que muestra la subimagen y
 *  sobre la que puede pinchar con el ratón.
 *
 *  Al ser una view, no es propietaria de la imagen.
 *
 *  El visor tiene 3 imágenes:
 *	    1.- subimg0 = es la subimagen que vamos a mostrar. No podemos
 *			  escribir sobre ella. Es de solo lectura.
 *
 *	    2.- cristal = es el cristal que colocamos sobre la subimg0. Es
 *			  aquí donde dibujamos.
 *
 *	    3.- pantalla = es la imagen que se muestra al usuario. Es la
 *			subimg0 vista a través del cristal. La pantalla
 *			escalada es la que se muestra al usuario.
 *
 *  
 *  Detalles: (lo que sigue está obsoleto, lo dejo de momento)
 *
 *  Un visor muestra una región de una imagen img0. Necesitamos distinguir
 *  las siguientes imágenes:
 *	1.- img0 =  imagen original. De esta imagen mostramos en el visor la
 *		    región 'region()'. Coordenadas globales de imagen (I, J).
 *		    (I, J) = Posicion_global
 *		    Esta imagen es invisible para el usuario.
 *
 *	2.- imgv0 =  imagen original  que mostramos en el visor. Es una
 *		    subimagen de img0. Es const, no podemos modificarla.
 *		    Coordenadas locales de imagen (i, j).
 *		    (i, j) = Posicion_local
 *
 *	3.- cristal = cristal que colocamos sobre la imagen imgv0.
 *		    Es aquí donde dibujamos.
 *		    Coordenadas locales de imagen (i, j)
 *
 *	3.- pantalla =  imagen (sin escalar) que mostramos en el visor.
 *		    Es el cristal encima de imgv0.
 *		    Coordenadas locales de imagen (i, j).
 *		    (i, j) = Posicion_local
 *
 *	4.- imgve = imagen (escalada) que mostramos en el visor. Esta imagen
 *		    es de implementación y no se debe de acceder desde el
 *		    interfaz de usuario. (TODO: esta explicación a la
 *		    documentación de la implementación).
 *		    Coordenadas de visor (iv, jv). Estas son las que devuelve
 *		    el ratón cuando el usuario pulsa sobre la imagen.
 *		    (iv, jv) = Posicion_de_visor
 *		    Esta imagen es invisble para el usuario.
 *
 *  Hay 3 tipos de coordenadas:
 *	- globales de imagen: (I, J)	Tipo: img::Position
 *	- locales de imagen : (i, j)	Tipo: img::Position
 *	- de visor: (iv, jv). Estas coordenadas son locales escaladas.
 *			      Tipo: gui::Posicion, ya que son coordenadas
 *			      de un widget.
 */
class Visor:public Widget{
public:
    // --------------------
    // Funciones de Widgets
    // --------------------
    /// El visor lo construimos de un tamaño sz determinado.
    /// La imagen se la pasamos más adelante.
    explicit Visor(Size sz);

    // coloca el Visor en la ventana v, en la posición p0
    void coloca(Ventana& v, Posicion p0) override;

    // Enlazamos con la subimagen que queremos mostrar
    // -----------------------------------------------
    /// Indicamos que el visor es un visor "de" la subimagne 
    /// (img0, p0, sz).
    /// Ejemplo: visor.de(img0, p0, sz);
    void de(const img::Image& img0,
                const img::Position& p0, const img::Size2D& sz)
    {visor()->de(img0, p0, sz);}

    /// Indicamos que el visor es un visor "de" la subimagne 
    /// (img0, p0, sz)
    void de(const img::Image& img0,
                const img::Position& p0, const img::Position& p1)
    {visor()->de(img0, p0, p1);}

    /// Asociamos el visor con la imagen img0, mostrando en pantalla
    /// la región 'r'.
    void de(const img::Image& img0, const img::Range2D& r)
    {visor()->de(img0, r);}

    /// Asociamos el visor a la imagen img0, mostrando en pantalla toda
    /// la imagen.
    void de(const img::Image& img0) {visor()->de(img0);}


    // ---------------------------
    // Control de lo que mostramos
    // ---------------------------
    /// \brief Recarga la imagen original al visor.
    ///
    /// Dos formas de comportamiento:
    /// 1) redibuja = true: borra todo lo que se hubiese dibujado encima.
    /// 2) redibuja = false: no borra lo dibujado encima.
    /// Observar que recargar no es redibujar el visor. Si se quiere redibujar
    /// el visor, habrá que llamar a redraw();
    void refresh(bool redibuja = true){visor()->refresh(redibuja);}

    /// Muestra la imagen original en pantalla, no borrando el cristal.
    void original() {visor()->original();}

    /// Indica al visor si tiene que mostrar la imagen y lo dibujado en el
    /// cristal o solo lo dibujado en el cristal.
    void muestra_img(bool mostrar) {visor()->muestra_img(mostrar);}


    // Redimensionamos la región que mostramos de la imagen
    // ----------------------------------------------------
    /// Muestra la región 'r' de la imagen img0 en el visor.
    /// La imagen img0 no cambia.
    ///
    /// Si se intenta mostrar una región fuera de la imagen, esta función 
    /// no hace nada.
    ///
    /// Observar que el rectángulo que le pasamos es un rectángulo de una
    /// imagen, y no un rectángulo de una ventana (de GUI). 
    /// \param[in] 'r': región que queremos visualizar, en coordenadas
    /// globales.
    /// \return	true : el visor muestra la región 'r'.
    ///		false: la función no se ejecuta. En el visor se muestra
    //			lo que se mostraba antes de llamar a esta función.
    void extension(const img::Range2D& rg, bool redibujar = true)
    {visor()->extension(rg, redibujar);}

    void extension(const img::Position& p0, const img::Size2D& sz, bool redibujar = true)
    {visor()->extension(p0, sz, redibujar);}

    void extension(const img::Position& p0, const img::Position& p1, bool redibujar = true)
    {visor()->extension(p0, p1, redibujar);}


    // Acceso a las imágenes del visor
    // -------------------------------
    /// Image original que mostramos en el visor.
    const img::const_Subimage& imgv0() const {return visor()->imgv0();}
    
    /// Devuelve el cristal sobre el que dibujamos. 
    img::Image& cristal() {return visor()->cristal();}
    const img::Image& cristal() const {return visor()->cristal();}

    // de momento la pantalla es igual al cristal
    img::Image& pantalla() {return visor()->cristal();}
    const img::Image& pantalla() const {return visor()->cristal();}

    // Syntax sugar
    // ------------
    /// Color que vemos en el cristal. Sirve para dibujar un punto en el 
    /// cristal. 
    /// En lugar de escrigir: visor.cristal()(p) = color;
    /// escribimos: visor.cristal(p) = color;
    img::ColorRGB& cristal(const img::Position& p)
    {
        return visor()->cristal(p);
    }

    const img::ColorRGB& cristal(const img::Position& p) const
    {
        return visor()->cristal(p);
    }

    // -------------------------------------------------------------
    // imgv0 - Image original (sin las capas) que se ve en el visor
    // -------------------------------------------------------------
    /// Color original de la imagen en el punto p(iv, jv) 
    /// p = coordenadas de visor
    img::ColorRGB imgv0(gui::Posicion p) const {return visor()->imgv0(p);}

    // ---------------------------------------------------
    // imgv - Image (con las capas) que se ve en el visor
    // ---------------------------------------------------
    /// Color que se ve en el visor en la posición p (iv, jv).
    /// (iv, jv) = coordenadas de visor.
    /// Todas las gui::Posicion son siempre coordenadas de visor.
    img::ColorRGB imgv(gui::Posicion p) const 
    {return visor()->imgv(p);}


    /// Indica si el punto p pertenece a la imagen o no.
    /// p = coordenadas de visor. Precondición: p pertenece al visor.
    bool pertenece_a_la_imagen(const gui::Posicion& p)
    {return visor()->pertenece_a_la_imagen(p);}

    // Funciones de conversión de coordenadas
    //
    // push_left pasa las coordenadas de visor. ¿cómo saber qué coordenadas
    // locales de imagen tiene? Necesitamos que esta función sea visible!!!
    /// Convierte la posición de visor p, en posición local en imgv.
    // Pasamos de coordenadas locales escaladas a coordenadas locales
    img::Position visor_to_local(gui::Posicion p) const
    { return visor()->visor_to_local(p); }

protected:
    Fl_Visor* visor(){return dynamic_cast<Fl_Visor*>(fl_widget());}
    const Fl_Visor* visor() const {return dynamic_cast<const Fl_Visor*>(fl_widget());}

    // amiga para que acceda a los manejadores de esta clase
    friend class Fl_Visor;

    // ----------------------
    // manejadores de eventos
    // ----------------------
    // 1. - manejador de teclado
    // devuelve 0 si no procesa la tecla, 1 si la procesa
    // Devuelve:
    //	    true    = procesa la tecla
    //	    false   = no la procesa
    // s = texto que ha escrito el usuario
    // key = codigo int de la tecla (por ejemplo, para flechas, ctrl, alt...)
    virtual bool pulsa_tecla(const std::string& t, int key) {return false;} 

    // 2. - manejadores del raton
    // p = (i, j) son las posiciones relativas al visor
    // Se garantiza que p pertenece al visor, no es necesario validar que
    // pertenezca.
    // Ejemplo: (0,0) = es la esquina superior izquierda.
    // Al ser relativas al visor, son las posiciones escaladas en la imagen.
    virtual bool push_left(Posicion p)    {return false;};
    virtual bool push_middle(Posicion p)  {return false;};
    virtual bool push_right(Posicion p)   {return false;};

    // IMPORTANTE: para que funcionen estos métodos, el método push tiene que
    // devolver true para pedir el ratón.
    // TODO: esto es porque así funciona FLTK, pero es raro, mejor cambiar esto (???)
    virtual bool drag_left(Posicion p)    {return false;};
    virtual bool drag_middle(Posicion p)  {return false;};
    virtual bool drag_right(Posicion p)   {return false;};

    virtual bool release_left(Posicion p)    {return false;};
    virtual bool release_middle(Posicion p)  {return false;};
    virtual bool release_right(Posicion p)   {return false;};

    // Cuando se mueve la rueda del ratón se llama a esta función.
    // dx = lo que se mueve en el eje x (horizontal)
    // dy = lo que se mueve en el eje y
    // Con mi ratón solo uso dy. Dejo el dx por si en el futuro sirve.
    virtual bool mouse_wheel(Coordenada dx, Coordenada dy){return false;}


    /// Convierte el rectángulo dado en coordenadas locales a coordenadas
    /// globales.
    img::Range2D local_to_global(const img::Range2D& r) const
    {return visor()->local_to_global(r);}



    /// Convierte la posición de visor p, en posición global en img0.
    // Pasamos de coordenadas locales escaladas a coordenadas locales
    img::Position visor_to_global(const gui::Posicion& p) const
    { return visor()->visor_to_global(p); }



    // La imagen local escalada tiene el mismo tamaño que el visor.
    // Las posiciones del visor coinciden con las posiciones en esta
    // imagen. Esta función me permite convertir de unas coordenadas
    // a otras. 
    // gui::Posicion p = coordenadas de visor.
    static img::Position coordenadas_de_visor_to_local(Posicion p)
    { return img::Position{p.y.pix(), p.x.pix()}; }
};



}//namespace img

#endif
