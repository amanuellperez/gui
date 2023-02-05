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


#include "gui_vent_pregunta.h"

#include "gui_maquetador.h"

using alp::maximo;

namespace gui{
/***************************************************************************
 *			VENTANA_PREGUNTA
 ***************************************************************************/
Ventana_pregunta::Ventana_pregunta
		( const std::string& titulo
		, const std::string& pregunta)
    :Ventana_modal{Size{10_pix, 10_pix} 
	    , titulo}
	    , input{pregunta, 20_car}
{
    // redimensiono para que quede mejor
    // redimensiona(bt_aceptar_, 8);
    // Poner: bt_aceptar.ancho(maximo(Ancho::en_car(8)));????
    bt_aceptar.ancho(bt_aceptar.ancho(), maximo(Ancho::en_car(8)));

    // redimensiona(bt_cancelar_, 8);
    bt_cancelar.ancho(bt_cancelar.ancho(), maximo(Ancho::en_car(8)));

    // maqueta();
    Maquetador m{*this};

    m.primer_widget(input);

    // Si la etiqueta es pequeña, los botones son más grandes que ella!!!
    if(bt_aceptar.ancho() + bt_cancelar.ancho() > input.ancho()){
	m.debajo(bt_aceptar);
	m.a_la_dcha(bt_cancelar);
    }else{
    // maqueta();
	m.alinea_a_la_dcha();
	m.debajo(bt_cancelar);
	m.a_la_izda(bt_aceptar);
    }

    // redimensionamos la ventana al tamaño de los widgets
    size(m.ancho_ventana(bt_cancelar), m.alto_ventana(bt_cancelar));
}
}// namespace
