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


#include "gui_base.h"
#include "gui_tipos.h"

#include <FL/Fl.H>  // Fl::run

namespace gui{

// Bucle principal. Esta función hay que llamarla para ejecutar el
// sistema de ventanas.
// Truco: para terminar la aplicación lanzo la excepción Fin_programa. 
//	  La capturo aquí de forma que este truco sea trasparente al usuario
int gui_main()
{
try{
    return Fl::run();
}catch(impl::Fin_programa)
{}
return 0;
}

}// namespace
