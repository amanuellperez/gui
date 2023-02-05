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

#ifndef __ALP_GUI_BASE_H__
#define __ALP_GUI_BASE_H__
/****************************************************************************
 *
 *   - DESCRIPCION: Capa para aislar mis aplicaciones del sistema de ventanas
 *	    que uso.
 *
 *   - COMENTARIOS: 
 *	    Los nombres de los widgets que sean los mismos que en html.
 *
 *   - EJEMPLO MÍNIMO: test_ventana01.cpp
 *
 *   - HISTORIA:
 *           alp  - 28/07/2016 Escrito
 *		    11/04/2017 Elimino errores iniciales (construye y demás)
 *
 ****************************************************************************/

// TODO: Meter todas las dependencias de Fl en un .cpp
// que los .h no dependan de la implementación. Para lo que hay que 
// reescribir todas las clases!!! (¿Puedo hacer algo parecido a lo que propone
// Stroustrup?)


namespace gui{

/// Bucle principal. Esta función hay que llamarla para ejecutar el
/// sistema de ventanas.
// Truco: para terminar la aplicación lanzo la excepción Fin_programa. 
//	  La capturo aquí de forma que este truco sea trasparente al usuario
int gui_main();


}
#endif 

