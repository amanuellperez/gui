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


#include "gui_boton_doble.h"

#include "gui_widget.h"

namespace gui{

Boton_doble::Boton_doble(  Ventana* v, const std::string& boton1,  Callback f1
		, const std::string& boton2,  Callback f2)
    :Grupo_de_controles{""}
    , bt1_{boton1, cb_click_boton1}
    , bt2_{boton2, cb_click_boton2}
    , v_{v}
    , cb1_{f1}, cb2_{f2}
{
    // Añadimos al grupo los botones.
    push_back(bt1_);
    push_back(bt2_);
}


void Boton_doble::click_boton1() 
{ 
    cb1_(NULL, v_);

    bt1_.hide();
    bt2_.show();
}


void Boton_doble::click_boton2() 
{
    cb2_(NULL, v_);

    bt2_.hide();
    bt1_.show();
}


Size Boton_doble::coloca_childs(Posicion p)
{
    mismo_size_mayor (bt1_, bt2_);

    bt1_.coloca(p); bt1_.show();
    bt2_.coloca(p); bt2_.hide();

    return bt1_.size();
}


}// namespace
