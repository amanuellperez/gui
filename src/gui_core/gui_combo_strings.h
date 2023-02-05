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

#ifndef __GUI_COMBO_STRINGS_H__
#define __GUI_COMBO_STRINGS_H__

#include "gui_widget_etcon.h"

#include <alp_vector.h>

namespace gui{


/*!
 *  \brief  Para el programador es un vector, para el usuario un
 *	    combobox de strings.
 *
 *   - EJEMPLO:
 *	    Combo_strings lista{"Colores"};
 *
 *	    // en el constructor
 *	    Maquetador m{*this};
 *
 *	    m.primer_widget(lista);
 *	    // ...
 *
 *	    lista.push_back("amarillo");
 *	    lista.push_back("azul");
 *	    lista.push_back("verde");
 *	    lista.sort();   
 *
 *	    ...
 *	    // añadimos el elemento que se ha escrito en la lista,
 *	    // ordenadamente
 *	    lista.add_sort(lista());
 *
 */
class Combo_strings:public Widget_etcon{
public:
    /// \param[in] titulo: título del combo.
    /// \param[in] combo_ancho: ancho del widget.
    Combo_strings(const std::string& titulo, Ancho combo_ancho);

    /// \brief Añadimos un item, siempre y cuando no exista en el combo.
    ///
    /// Si la cadena está ya en la lista, no la añade. 
    /// No añade cadenas vacías, y elimina todos los espacios del principio 
    /// y del final.
    /// Lo añade al final de la lista, ya que es una lista desordenada.
    ///
    /// \return true: añade un nuevo elemento a la lista
    ///         false: no lo añade, porque ya estaba en la lista o es vacía
    bool push_back(const std::string& item);

    /// \brief Añade el elemento "item" ordenándolo alfabéticamente
    ///
    /// Internamente llama a push_back, así que cumple las mismas condiciones.
    ///
    /// \return Indica si añade (true) o no (false) el item al combo.
    bool add_sort(const std::string& item);

    /// Ordena el combo
    void sort();

    /// Leemos el valor seleccionado por el usuario
    std::string operator()() const {return seleccion();}

    /// Leemos el valor seleccionado por el usuario
    std::string seleccion() const {return w()->value();}

    /// Escribimos el valor seleccionado
    void operator()(const std::string& v) {w()->value(v.c_str());}


    /// Devuelve si el usuario ha seleccionado un elemento o no.
    bool hay_seleccion() // const <-- tendría que ser const!!! 
			// pero para FLTK no lo es
    {return (indice_seleccion() != lista.size());}

    /// Indice, en esta lista, del elemento seleccionado.
    ///
    /// En caso de no encontrar el elemento seleccionado devuelve el
    /// size() del combo (número de elementos que hay almacenados en él).
    size_t indice_seleccion() const
    {return alp::find_indice(lista, seleccion());}

protected:
//    /// Cuando el usuario pulsa una tecla en el combo se llama a pulsa_tecla.
//    /// \return Devuelve true, si gestiona la tecla, false en caso contrario.
//    // TODO: esto no funciona!!!!
//    virtual bool pulsa_tecla(const std::string& s, int key) 
//    {return false;} 

    friend Fl_Combo_strings;

private:
    // lista que mostramos en pantalla
    // Aunque esta lista ya la tiene almacenada FLTK, prefiero duplicarla
    // para poder ordenarla, iterar sobre ella... y hacer lo que yo quiera.
    // Quiero que este control sea la interacción de un contenedor con el
    // usuario.
    std::vector<std::string> lista;

    // recarga la lista
    void refresh();

    // conversión a fltk
    Fl_Combo_strings* w(){ return dynamic_cast<Fl_Combo_strings*>(fl_widget());}
    const Fl_Combo_strings* w() const{ return dynamic_cast<const Fl_Combo_strings*>(fl_widget());}
};


inline Combo_strings::Combo_strings(const std::string& titulo
				    , Ancho combo_ancho) // en caracteres
    :Widget_etcon{new Fl_Combo_strings{this
		    , 0,0   , fltk_to_int(Ancho{combo_ancho})
			    , fltk_to_int(Letra::alto())}
		  , titulo
		  , Ancho{combo_ancho}}
{
}


// añade elementos que ya hay en la lista!!!
// Si la cadena está ya en la lista, no la añade.
// Lo añade al final de la lista, ya que es una lista desordenada
// OJO:: Añadimos sin espacios al principio ni final de la cadena!!!
//
// Devuelve:
//	true  - añade un nuevo elemento a la lista
//	false - no lo añade, porque ya estaba en la lista o es vacía
inline bool Combo_strings::push_back(const std::string& item)
{ 
    auto new_item = alp::trim(item);

    if(new_item.empty())
	return false;

    if(!alp::pertenece(new_item, lista)){
	lista.push_back(new_item);
	w()->add(item.c_str());
	return true;
    }

    return false;
}


// añade el elemento "item" ordenándolo alfabéticamente
// Devuelve:
//	true  - añade un nuevo elemento a la lista
//	false - no lo añade, porque ya estaba en la lista
inline bool Combo_strings::add_sort(const std::string& item)
{
    if(push_back(item)){
	sort();
	return true;
    }

    return false;
}

// ordena la lista
inline void Combo_strings::sort()
{
    alp::sort(lista);
    refresh();
}

// recarga la lista
inline void Combo_strings::refresh()
{
    w()->clear();
    for(auto x: lista)
	w()->add(x.c_str());
}


}// namespace

#endif
