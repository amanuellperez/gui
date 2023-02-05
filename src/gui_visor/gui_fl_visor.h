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

#ifndef __GUI_FL_VISOR_H__
#define __GUI_FL_VISOR_H__
/****************************************************************************
 *
 *   - DESCRIPCION: Clases que dependen completamente de FLTK. De hecho, son
 *	    clases hijas de clases de FLTK.
 *
 *	    Un visor es un view de una imagen. No es propietario de la imagen.
 *	De hecho, para el programador, un visor no es más que una subimagen 
 *	de una imagen sobre la que hemos colocado un cristal sobre el que
 *	dibujamos. La pantalla es lo que vemos: la subimagen vista a través
 *	del cristal.
 *
 *
 *   - COMENTARIOS: 
 *
 *   - HISTORIA:
 *           Manuel Perez - 19/07/2016 Escrito
 *			      02/03/2019 Lo convierto en subimagen.
 *
 ****************************************************************************/
#include <FL/Fl_Box.H>


#include <img.h>
#include <img_escala.h>
#include <img_view.h>
#include <img_draw.h>

namespace gui{
/*!
 *  \brief  Es el visor real que voy a usar. 
 *	    Necesito heredarlo de Fl_Box para que se llame a la función 
 *	    resize, ya que este control sabe cómo redimensionar la imagen.
 *
 *	Tiene todas las funciones para manejar los visores.
 *
 *	Inicialmente el visor puede estar sin mostrar ninguna imagen,
 *	en cuyo caso mostrará una imagen en negro. Luego se le puede
 *	enlazar con una imagen, via el método 'de' (no olvidar llamar
 *	a refresh para que lo redibuje), y se puede enlazar a diferentes
 *	imágenes tantas veces como se quiera. El visor NO modifica la
 *	imagen, pinta encima del cristal.
 *
 *	Comentarios:
 *	    Este Visor tiene que ser un visor eficiente tanto en tiempo como
 *	    en uso de memoria. Luego, no debe de tener capas. La idea es que
 *	    pueda poner 3 visores distintos en una misma ventana (por ejemplo,
 *	    para seleccionar de distinta forma) y no pese nada crear 3
 *	    visores. De esa forma, cada visor será responsable de manejar el
 *	    ratón de forma distinta (seleccionar en linea, en rectángulo, en
 *	    polígono...).
 *
 *	    Si se necesitan visores con capas, heredar de este o crear otro,
 *	    pero dejar este visor lo más sencillo y eficiente posible.
 *	    TODO: a día de hoy no es eficiente, hay que revisar toda la
 *	    gestión de memoria y demás.
 *
 *	El visor tiene 3 imágenes:
 *	    1.- imgv0  = es la imagen que vamos a mostrar. No podemos
 *			  escribir sobre ella. Es de solo lectura.
 *
 *	    2.- cristal = es el cristal que colocamos sobre la subimg0. Es
 *			  aquí donde dibujamos. 
 *
 *	    3.- pantalla = es la imagen que se muestra al usuario. Es la
 *			subimg0 vista a través del cristal. La pantalla
 *			escalada es la que se muestra al usuario.
 *
 *	\see Visor.
 *
 */
class Visor;

class Fl_Visor:public Fl_Box{
public:
    // La construcción del visor la hago en dos pasos:
    // 1. Constructor
    // 2. enlaza();
    //
    // Lo hago así ya que la clase Visor hereda de Widget y llama a la
    // template construye (OBSOLETO!!!).  
    // REVISAR ESTO para que en el constructor sea 
    // obligatorio pasarle un Visor* ya que si no, lo dejamos a medias
    // construido!!! <--- ERROR DE DISEÑO!!!
    // TODO: cambiar a Fl_Visor(Posicion p0, Size sz)
    Fl_Visor(int x, int y, int a, int h);

    void enlaza(Visor* v) {visor_ = v;}

    ~Fl_Visor();

    void resize(int x, int y, int a, int h);


    // Enlazamos con la subimagen que queremos mostrar
    // -----------------------------------------------
    /// Indicamos que el visor es un visor "de" la subimagne 
    /// (img0, p0, sz).
    /// Ejemplo: visor.de(img0, p0, sz);
    void de(const img::Image& img0,
                const img::Position& p0, const img::Size2D& sz)
    {de(img0, img::Range2D{p0, sz});}

    /// Indicamos que el visor es un visor "de" la subimagne 
    /// (img0, p0, sz)
    void de(const img::Image& img0,
                const img::Position& p0, const img::Position& p1)
    {de(img0, img::Range2D{p0, p1});}

    /// Asociamos el visor con la imagen img0, mostrando en pantalla
    /// la región 'r'.
    void de(const img::Image& img0, const img::Range2D& r);

    /// Asociamos el visor a la imagen img0, mostrando en pantalla toda
    /// la imagen.
    void de(const img::Image& img0)
    {de(img0, img0.extension());}


    // Redimensionamos la región que mostramos de la imagen
    // ----------------------------------------------------
    void extension(const img::Range2D& rg, bool redibujar = true);

    void extension(const img::Position& p0, const img::Size2D& sz, bool redibujar = true)
    {extension(img::Range2D{p0, sz}, redibujar);}

    void extension(const img::Position& p0, const img::Position& p1, bool redibujar = true)
    {extension(img::Range2D(p0, p1), redibujar);}


    void muestra_img(bool mostrar);


    // Acceso a las imágenes del visor
    // -------------------------------
    /// Image original que mostramos en el visor
    const img::const_Subimage& imgv0() const {return subimg0_;}
    
    /// Cristal sobre el que dibujamos. 
    img::Image& cristal() {return cristal_;}
    const img::Image& cristal() const {return cristal_;}

    /// Es lo que mostramos en pantalla (sin escalar)
    /// Será: pantalla = superposición de cristal sobre imgv0
    // De momento la pantalla es igual al cristal
    img::Image& pantalla() {return cristal_;}
    const img::Image& pantalla() const {return cristal_;}


    // Syntax sugar
    // ------------
    /// Color que vemos en el cristal. Sirve para dibujar un punto en el 
    /// cristal. 
    /// En lugar de escrigir: visor.cristal()(p) = color;
    /// escribimos: visor.cristal(p) = color;
    img::ColorRGB& cristal(const img::Position& p) { return cristal_(p); }
    const img::ColorRGB& cristal(const img::Position& p) const
    {
        return cristal_(p);
    }

    // ----------------------
    // img0 - Image original
    // ----------------------
//    /// Color original de la imagen en el punto p(i,j) (coordenadas locales)
//    // img::ColorRGB img0(int i, int j) const;
    img::ColorRGB img0_local(img::Position p) const;

    // -------------------------------------------------------------
    // imgv0 - Image original (sin las capas) que se ve en el visor
    // -------------------------------------------------------------
    /// Color original de la imagen en el pixel del visor p (coordenadas 
    /// de visor).
    img::ColorRGB imgv0(gui::Posicion p) const;

    // ---------------------------------------------------
    // imgv - Image (con las capas) que se ve en el visor
    //	    TODO: esto es la pantalla. Llamarlo pantalla!!!
    // ---------------------------------------------------
    /// ColorRGB de la imagen que se muestra en el visor.
    /// Coordenadas de visor.
    img::ColorRGB imgv(gui::Posicion p) const
    {
	return pantalla()(visor_to_local(p));
    }

    /// Indica si el punto p pertenece a la imagen que muestra al visor (puede
    /// pertenecer a la imagen o al fondo)
    /// p = coordenadas de visor. Precondición: p pertenece al visor.
    bool pertenece_a_la_imagen(const gui::Posicion& p)
    {
	return (imgve_rango_.j0 <= p.x.pix() and p.x.pix() < imgve_rango_.je)
	    and (imgve_rango_.i0 <= p.y.pix() and p.y.pix() < imgve_rango_.ie);
    }
    

    // funciones para operar con las imágenes
    void refresh(bool redibuja = true);
    void original();	// recarga, sin modificar el visor, la imagen original

    // funciones de conversión

    /// Convierte la posición de visor p, en posición local en imgv.
    // Pasamos de coordenadas locales escaladas a coordenadas locales
    img::Position visor_to_local(gui::Posicion p) const
    { return escalador.local_escalado_to_local(visor_to_local_escalada(p)); }

    /// Convierte la posición de visor p, en posición global en img0.
    // Pasamos de coordenadas locales escaladas a coordenadas locales
    img::Position visor_to_global(const gui::Posicion& p) const
    { return local_to_global(visor_to_local(p));}

    // Convierte: de local escalada (ie, je) --> a global (I, J)
    img::Range2D local_escalada_to_global(const img::Range2D& r) const;

    // Convierte de local a global
    img::Range2D local_to_global(img::Range2D r) const;

    // Grabamos lo que se muestra en pantalla al usuario!!! (sin el escalado)
    void write(const std::string& nombre) const
    { img::write(cristal_, nombre); }

    friend std::ostream& operator<<(std::ostream& out, const Fl_Visor& v);



private:
    // En principio la idea es que un visor es una subimagen sobre la que
    // colocamos un cristal. Nosotros dibujamos solo sobre el cristal. 
    // Podemos implementar esto:
    //	1.- cristal_  = contiene lo dibujado por el usuario. Cada vez que
    //			se dibuje el visor, hay que crear una imagen aparte
    //			que sea la mezcla de la subimagen y el cristal.
    //
    //
    //	2.- cristal_  = inicialmente sobre el cristal dibujamos toda la sub-
    //			imagen, de tal manera que cada vez que dibujamos sobre 
    //			el cristal ya marcamos la imagen.
    //
    //	(1) tiene la ventaja de que podemos recuperar una imagen con lo
    //	marcado, pero la desventaja de que cada vez que se dibuja hay que
    //	crear una nueva imagen con la mezcla de la subimagen y el cristal. 
    //	Elijo (2) para implementarlo.
    //
    //	Tanto (1) como (2) las imagenes son sin escalar.
    //
    // Contiene una copia (o no, si la dejamos en negro) de la imagen que vamos 
    // a marcar. Por defecto, la función draw_local escribe en esta imagen. 
    img::const_Subimage subimg0_;
    img::Image	   cristal_; 


    bool resize_ = true;    // indica si la imagen hay que redimensionarla  
			    // FLTK cuando aumenta una ventana la aumenta
			    // en dos pasos (ancho y alto), luego si se hace
			    // el resize de la imagen cada vez que FLTK llama
			    // a resize, la imagen la escalamos 2 veces
			    // (muy ineficiente, de hecho se ve lento).
			    // Este flag es para evitar esto.


    // Cotilleando el código de Fl_RGB_Image, veo que Fl_RGB_Image no es
    // propietario del puntero, sino que soy yo. Luego yo me encargo de
    // gestionar la memoria de cristal_!!!
    unsigned char* pimge_ = nullptr;  // puntero a la imagen escalada que mostramos 
			    // en el visor
			    
    img::Escalador escalador;    // responsable de escalar las imágenes
			    // ¿sería mejor Image_escalada????
			    // De momento lo uso sobre todo para poder
			    // convertir (ie, je) --> (i,j).


    Fl_RGB_Image* rgb = nullptr;
    static const int num_canales;

    // imagen por defecto que se muestra en el visor en caso de no
    // asociarlo a ninguna imagen
    static const img::Image img_por_defecto;

    // dimensiones del visor
    int ancho, alto;	

    // Range que ocupa la imagen escalada dentro del visor
    // (en coordenadas de visor = locales escaladas)
    img::Range2D imgve_rango_;

    // ¿Qué mostramos en el visor?
    // 1.- La imagen original sin el cristal
    // 2.- Solo el cristal (lo dibujado en él)
    // 3.- La imagen original y encima el cristal.
    bool mostrar_img_ = true;	// indica si mostramos la imagen y lo dibujado
				// en pantalla o solo lo dibujado en pantalla
				
    bool mostrar_original_ = false; // indica si queremos mostrar en pantalla
				// todas las capas, o recargar momentaneamente
				// la imagen original


    // Para gestionar el drag, necesito recordar el último botón del ratón que
    // se pulsó
    enum class Boton_raton{ ninguno, dcho, izdo, medio };
    Boton_raton boton_pulsado_ = Boton_raton::ninguno;


    // --------------------
    // Funciones auxiliares
    // --------------------
    void draw();	// vuelca img1_ en la pantalla



//    double razon_semejanza() const 
//    {
//        return 
//	    alp::narrow_cast<double>(alto_region()) /
//					alp::narrow_cast<double>(alto);
//    }

    // --------------------------------
    // Cambio de sistemas de referencia
    // --------------------------------
    // 1.- De coordenadas de visor gui::Posicion a coordenadas 
    // locales escaladas img::Position
    // La imagen local escalada tiene el mismo tamaño que el visor.
    // Las posiciones del visor coinciden con las posiciones en esta
    // imagen. Esta función me permite convertir de unas coordenadas
    // a otras.
    img::Position visor_to_local_escalada(gui::Posicion p) const
    {
        return img::Position{p.y.pix() - imgve_rango_.i0,
                             p.x.pix() - imgve_rango_.j0};
    }

    // 2.- De coordenadas locales escaladas (ie, je) a coordenadas locales
    img::Ind ie_to_local(img::Ind ie) const
    {return escalador.i(ie);}

    img::Ind je_to_local(img::Ind je) const
    {return escalador.j(je);}


    // de coordenadas local escalada (ie, je) a coordenadas locales (i,j).
    // De coordenadas de pantalla a coordenadas de subimagen.
    img::Position local_escalada_to_local(img::Position p) const
	{return img::Position{ie_to_local(p.i), je_to_local(p.j)};}


    img::Range2D local_escalada_to_local(const img::Range2D& r) const
    {
//	return img::Range2D{local_escalada_to_local(r.p0())
//					, local_escalada_to_local(r.p1())};
	return img::Range2D{local_escalada_to_local(r.upper_left_corner())
			  , local_escalada_to_local(r.bottom_right_corner())};
    }

    // 3.- De coordenadas locales a coordenadas globales
    img::Position local_to_global(img::Position p) const
    { return {subimg0_.P0().i + p.i, subimg0_.P0().j + p.j};}


    // Funciones para implementar draw():
    void vuelca_al_visor(const img::Image& img0);
    void draw_original();
//    void draw_capas();


    // crea las capas asociada a la imagen. Precondición: se
    // tiene que haber llamado a enlaza_img0. Ahora solo tengo una capa
    // pero en el futuro podría tener más.
    void crea_cristal() {cristal_ = clone(subimg0_);}


    void resize();

    // Manejadores (los implementa las hijas de la clase Visor)
    Visor* visor_;
    int handle(int event);

};


// Devuelve el color de la imagen original
// (i,j) = son coordenadas locales a la región que se muestra en el visor.
inline img::ColorRGB Fl_Visor::img0_local(img::Position p) const 
//{ return (*img0_)(p0_.i+p.i, p0_.j+p.j); }
{ return subimg0_(p); }
//
inline img::ColorRGB Fl_Visor::imgv0(gui::Posicion p) const
{ return img0_local(visor_to_local(p));}


inline void Fl_Visor::refresh(bool redibuja)
{
    if(subimg0_.empty()) return;

    //if(mostrar_img_) cristal_ = img0_->clone(p0_, p1_);
    if(mostrar_img_) cristal_ = clone(subimg0_);
    else	     cristal_ = img::imagen_negra(subimg0_.size2D());

    if(redibuja) redraw();
}


inline void Fl_Visor::original()
{
    mostrar_original_ = true;
    redraw();
}

// Recargamos la imagen original en el visor, para que momentaneamente
// podamos ver la imagen original que estamos marcando. No modificamos
// nada. Si se llamase a redraw() se recargaría lo que estaba dibujado
inline void Fl_Visor::draw_original()
{ vuelca_al_visor(clone(subimg0_)); }

std::ostream& operator<<(std::ostream& out, const Fl_Visor& v);



}


#endif

