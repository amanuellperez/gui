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


#include "gui_input_string.h"

namespace gui{

Input_string::Input_string( const std::string& etiqueta0
	      , Ancho input_ancho   // ancho del input
	      , const std::string& v0)
    :Widget_etcon{new Fl_Input{0, 0 
			, fltk_to_int(input_ancho)
			, fltk_to_int(Letra::alto())}
	 , etiqueta0, input_ancho}
{
    w()->value(v0.c_str());
}


}// namespace
