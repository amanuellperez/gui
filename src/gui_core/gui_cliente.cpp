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


#include "gui_cliente.h"

#include <FL/Fl_File_Chooser.H>	// fl_file_chooser

namespace gui{
namespace Cliente{
/***************************************************************************
 *  
 *  Abre una ventana de diálogo para elegir un fichero.
 *
 *  Devuelve la cadena vacía si el usuario no selecciona nada,
 *	o el nombre del fichero seleccionado (tal como está hecho se 
 *	puede escribir el nombre de un fichero que no exista y lo devuelve).
 *
 *  TODO: Revisar y hacer más flexible.
 *
 ***************************************************************************/
std::string ask_nombre_fichero
     ( const std::string& titulo	    
     , const std::string& filtro	// "*.jpg"
     , const std::string& path)	// "path o fichero inicial"
{
    std::string nombre_fichero;

    char* fic = fl_file_chooser(titulo.c_str(), filtro.c_str()
			, path.c_str(), 0);
    if(fic != NULL)
	nombre_fichero = fic;

    return nombre_fichero;
}


}}// namespaces gui::Cliente
