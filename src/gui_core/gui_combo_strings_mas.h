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

#ifndef __GUI_COMBO_STRINGS_MAS_H__
#define __GUI_COMBO_STRINGS_MAS_H__
/****************************************************************************
 *
 *   - DESCRIPCION: Combo_strings_mas
 *
 *   - COMENTARIOS: 
 *
 *   - HISTORIA:
 *           alp  - 13/04/2017 Escrito
 *
 ****************************************************************************/
#include "gui_base.h"
#include "gui_grupo_de_controles.h"
#include "gui_boton.h"
#include "gui_combo_strings.h"

namespace gui{

/*!
 *  \brief  Es un Combo_strings con un botón + para añadir nuevos elementos.
 *
 *  Es una prueba para probar Grupo_horizontal. Lo ideal es que este 
 *  combo heredara de Combo_strings, pero no funcionaria con Grupo_horizontal.
 *  Así que realmente es un wrapper del combo (lo cual es un incordio para 
 *  mantener; ¿no se podría heredar?).
 *
 */
class Combo_strings_mas:public Grupo_horizontal{
public:
    /// Crea un combo de título y ancho (dado en número de caracteres).
    Combo_strings_mas(const std::string& titulo
		    , Ancho num_caracteres_ancho_combo);

    /// \brief Añadimos un item, siempre y cuando no exista en el combo.
    ///
    /// Si la cadena está ya en la lista, no la añade. 
    /// No añade cadenas vacías, y elimina todos los espacios del principio 
    /// y del final.
    /// Lo añade al final de la lista, ya que es una lista desordenada.
    ///
    /// \return true: añade un nuevo elemento a la lista
    ///         false: no lo añade, porque ya estaba en la lista o es vacía
    bool push_back(const std::string& item){return combo_.push_back(item);}

    /// \brief Añade el elemento "item" ordenándolo alfabéticamente
    ///
    /// Internamente llama a push_back, así que cumple las mismas condiciones.
    ///
    /// \return Indica si añade (true) o no (false) el item al combo.
    bool add_sort(const std::string& item) {return combo_.add_sort(item);}

    /// Ordena el combo
    void sort() {combo_.sort();}

    /// Leemos el valor seleccionado por el usuario
    std::string operator()() const {return combo_();}

    /// Escribimos el valor seleccionado
    void operator()(const std::string& v) {combo_(v);}

private:
    Combo_strings combo_;
    Boton bt_{"+", cb_add};

    static void cb_add(void*, void* grupo)
    {static_cast<Combo_strings_mas*>(grupo)->add_input();}

    void add_input()
    { combo_.push_back(combo_()); }
};






}// namespace gui

#endif
