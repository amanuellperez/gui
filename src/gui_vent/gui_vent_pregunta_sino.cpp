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


#include "gui_vent_pregunta_sino.h"

#include "gui_maquetador.h"

namespace gui{

/***************************************************************************
 *			VENTANA_PREGUNTA_SINO
 ***************************************************************************/
Ventana_pregunta_sino::Ventana_pregunta_sino
	 ( const std::string& titulo
	, const std::string& pregunta
	, const std::string& et_si
	, const std::string& et_no)
	:Ventana_modal{Size{10_pix, 10_pix}, titulo}
	, pregunta_{pregunta}
	, bt_si_{et_si, cb_si}
	, bt_no_{et_no, cb_no}
{
    // redimensiono para que quede mejor
    // redimensiona(bt_si_, 8);
    bt_si_.ancho(std::max(Ancho::en_car(8), bt_si_.ancho()));

    // redimensiona(bt_no_, 8);
    bt_no_.ancho(std::max(Ancho::en_car(8), bt_no_.ancho()));

    // maqueta();
    Maquetador m{*this};

    m.primer_widget(pregunta_);

    // Si la etiqueta es pequeña, los botones son más grandes que ella!!!
    if(bt_si_.ancho() + bt_no_.ancho() > pregunta_.ancho()){
	m.debajo(bt_si_);
	m.a_la_dcha(bt_no_);
    }else{
    // maqueta();
	m.alinea_a_la_dcha();
	m.debajo(bt_no_);
	m.a_la_izda(bt_si_);
    }

    // redimensionamos la ventana al tamaño de los widgets
    size(m.ancho_ventana(bt_no_), m.alto_ventana(bt_no_));
}

}// namespace 
