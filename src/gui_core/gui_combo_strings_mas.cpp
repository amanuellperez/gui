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


#include "gui_combo_strings_mas.h"



namespace gui{

/***************************************************************************
 *			COMBO_STRINGS_MAS
 ***************************************************************************/
Combo_strings_mas::Combo_strings_mas(const std::string& titulo
		, Ancho num_caracteres_ancho_combo)
    :Grupo_horizontal{""}
    , combo_{titulo, num_caracteres_ancho_combo}
{
    // hacemos el botón del mismo alto que el combo
    bt_.alto(combo_.alto());

    // Dos formas de definirlo, a elegir:
    // 1.- Con <<
    *this << combo_ << bt_;

    // 2.- Con push_back.
//	push_back(combo);
//	push_back(bt);
}



}// namespace gui
