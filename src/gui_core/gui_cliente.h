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
#ifndef __GUI_CLIENTE_H__
#define __GUI_CLIENTE_H__

#include <string>

namespace gui{
/*!
 *  \brief  La interacción con el cliente (usuario final con el que interactúa
 *	la GUI), la definimos dentro de este namespace.
 *
 *  DUDA: ¿Qué es mejor: un namespace o una clase?
 *
 */
namespace Cliente{
/*!
 *  \brief  Abre una ventana de diálogo y pregunta al usuario por
 *	el nombre de un fichero.
 *
 *  \param [in] 'titulo' de la ventana.
 *  \param [in] 'filtro' que aplicamos para buscar ("*", "*.jpg",...)
 *  \param [in] 'path' inicial. Nombre del directorio o fichero donde
 *  empezamos la búsqueda.
 *
 *  \return Devuelve la cadena vacía si el usuario no selecciona nada,
 *	o el nombre del fichero seleccionado (tal como está hecho se 
 *	puede escribir el nombre de un fichero que no exista y lo devuelve).
 *
 *  \todo Revisar y hacer más flexible.
 *
 *  DUDA: gui::ask(File_name)???
 *
 */
std::string ask_nombre_fichero
    (const std::string& titulo,		// titulo ventana
     const std::string& filtro,
     const std::string& path ="");	// "*.jpg" 

}// namespace Cliente
}// namespace gui

#endif
