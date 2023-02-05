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

#ifndef __ALP_GUI_CORE_H__
#define __ALP_GUI_CORE_H__

// GUI básico:
// Define:
//  + API sobre FLTK para ocultarla.
//  + clases Ventana y Widget.
//  + Controles básicos: boton, input_int, ...
//  + Maquetador.
//
//  TODO: sacar a otro paquete lo que depende de FLTK para que quede
//  claro qué es lo que hay que reescribir en caso de querer usar 
//  otro sistema de ventanas diferentes.


// ---------------------------------------
//	      DEPENDE DE FLTK
// ---------------------------------------
// paquete gui_core
#include "gui_base.h"		// Widget
#include "gui_widget.h"		// Widget
#include "gui_ventana.h"	// Ventana
#include "gui_cliente.h"

#include "gui_grupo_de_controles.h"  // Grupo_de_controles

// Widgets particulares (basados en los correspondientes de fltk)
#include "gui_menu_bar.h"	// una barra de menús

#include "gui_etiqueta.h"	// string solo de lectura para el usuario
#include "gui_boton.h"		// función

#include "gui_check_bool.h"	// bool
#include "gui_circular_bool.h"	// bool
#include "gui_boton_bool.h"	// bool
#include "gui_boton_doble.h"	// bool

#include "gui_widget_etcon.h"
#include "gui_input_string.h"	// string
#include "gui_input_int.h"	// int
#include "gui_combo_strings.h"	// vector<string>

#include "gui_combo_strings_mas.h"

#include "gui_timer.h"		// Timer


// Aunque el maquetador no depende de FLTK, es tan útil que lo 
// necesito para hacer cualquier cosa con las ventanas. Es básico
// ==> pertenece al core!!!
#include "gui_maquetador.h"


#endif
