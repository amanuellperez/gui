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


#include "gui_vent_mensaje_aviso.h"

#include "gui_maquetador.h"


using namespace alp;

namespace gui{


/***************************************************************************
 *			VENTANA_MENSAJE_AVISO
 ***************************************************************************/
Ventana_mensaje_aviso::Ventana_mensaje_aviso
	 ( const std::string& titulo
	 , const std::string& msg
	 , const std::string& et_boton)
	:Ventana_modal{Size{10_pix, 10_pix}, titulo}
	, aviso_{msg}
	, bt_ok_{et_boton, cb_ok}
{
    // redimensiono el botón
    bt_ok_.size(Ancho::en_car(8), Alto::en_lin(1));

    // maqueta()
    Maquetador m{*this};

    m.primer_widget(aviso_);
    m.alinea_a_la_dcha();
    m.debajo(bt_ok_);

    // redimensiono la ventana correctamente
    size(m.ancho_ventana(aviso_), m.alto_ventana(bt_ok_));
}




}// namespace gui

