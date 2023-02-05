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
#ifndef __GUI_GRUPO_DE_CONTROLES_H__
#define __GUI_GRUPO_DE_CONTROLES_H__
/****************************************************************************
 *
 *   - DESCRIPCION: Widgets particulares.
 *	    ¡¡¡Todos estos widgets dependen de FLTK directamente!!!
 *
 *   - HISTORIA:
 *           alp  - 11/04/2017 Escrito
 *
 ****************************************************************************/
#include "gui_widget.h"
#include "gui_etiqueta.h"


namespace gui{

/*!
 *  \brief  Contenedor de controles básico.
 *
 *  Al ser un contenedor, tiene que tener las mismas funciones que los 
 *  contenedores estandar (por ejemplo, que std::vector).
 *
 *  Se trata de una clase abstracta. Es responsable de:
 *	1.- Llevar un listado de los widgets que pertenecen al grupo.
 *	2.- Colocar el título, si lo tiene, de forma adecuada.
 *
 *  Los hijos tienen que definir coloca_childs, función que dice cómo
 *  colocar los widgets (horizontal, vertical, en el mismo sitio (?)).
 *
 *  \todo No tiene todas las funciones de los contenedores. ¿las necesita?
 *
 */

class Grupo_de_controles:public Widget{
public:
    /// Añade el widget w a este grupo.
    void push_back(Widget& w);

    /// Añade el widget w a este grupo. Llama internamente a push_back.
    Grupo_de_controles& operator<<(Widget& w);

    /// Colocamos el grupo en la ventana v, en la posición p.
    void coloca(Ventana& v, Posicion p) final;

    // DUDA: sería mejor devolver titulo_ y que el usuario pueda cambiarle
    // el formato como quiera? (Problema: podría mal usarse!!!)
    /// Si tiene título le podemos poner un borde.
    void borde_titulo(Widget::Tipo_borde b) {titulo_.borde(b);}

    // Si no tenía título, y lo añadimos hay que recolocar todos los widgets
    // del grupo.
//    /// Ponemos un nuevo título al grupo.
//    void titulo(const std::string& t){titulo_(t);}

//    /// Consultamos el título (¿esto es útil?)
//    std::string titulo() const {return titulo_();}

protected: // DUDA: hacer este interfaz público?
    /// Iterador al primer widget del grupo.
    auto begin() {return child_.begin();}
    auto begin() const {return child_.begin();}

    /// Iterador al último más uno widget del grupo.
    auto end() {return child_.end();}
    auto end() const {return child_.end();}

    /// Devuelve el número de widgets que tiene este contenedor.
    /// ¡¡¡Este size es del contenedor!!!
    auto size() const {return child_.size();}

    /// Definimos el tamaño del grupo. ¡¡¡Este size, es del Widget!!!
    void size(Ancho a, Alto h) { Widget::size(a,h);} 
    
protected:
    // No permito crear Grupo_de_controles directamente. Crear grupos
    // horizontales, o verticales.
    /// Crea un grupo de controles.
    Grupo_de_controles(const std::string& titulo);

    // Cada grupo hijo sabrá cómo colocar los hijos.
    virtual Size coloca_childs(Posicion p) = 0;

private:
    Etiqueta titulo_;		    // título del grupo (opcional)
    std::vector<Widget*> child_;    // widgets que forman el grupo

    // Los grupos tienen título, no etiqueta. 
    // Prohibo el uso de estas funciones.
    std::string etiqueta() const;// {return Widget::etiqueta();}
    void etiqueta(const std::string& et);// {Widget::etiqueta(et);}

    // Nos dice si el grupo tiene título o no.
    bool tiene_titulo(){return !titulo_().empty();}

    // Colocamos el grupo, añadiéndole el título
    void coloca_con_el_titulo(Posicion p);

    // Colocamos el grupo, sin ningún título
    void coloca_sin_el_titulo(Posicion p);

    // Añadimos el widget al grupo de fltk
    void fltk_add(Widget& w);
};

inline Grupo_de_controles& Grupo_de_controles::operator<<(Widget& w)
{
    push_back(w);
    return *this;
}


/*!
 *  \brief  Es un grupo horizontal de widgets.
 *
 *  Se colocan todos los widgets uno al lado del otro.
 *
 */
class Grupo_horizontal:public Grupo_de_controles{
public:
    Grupo_horizontal(const std::string& titulo);   

private:
    // devuelve el ancho//alto de todo el widget en pixeles
    Ancho ancho_grupo() const;
    Alto alto_grupo() const;

    // Colocamos los hijos en la posición p
    Size coloca_childs(Posicion p) override;

};



/*!
 *  \brief  Grupo vertical de widgets.
 *
 *  Se colocan todos los widgets uno encima de otro.
 *
 */
class Grupo_vertical:public Grupo_de_controles{
public:
    Grupo_vertical(const std::string& titulo);   

private:
    // devuelve el ancho//alto de todo el widget en pixeles
    Ancho ancho_grupo() const;
    Alto alto_grupo() const;

    // Colocamos los hijos en la posición p
    Size coloca_childs(Posicion p) override;

    static Distancia margen_entre_lineas() {return 0_pix;}//Cfg::widgets_margen_y;}
};






}//namespace gui

#endif

