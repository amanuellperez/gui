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


#include "../../gui_ventana.h"
#include "../../gui_base.h"
#include "../../gui_etiqueta.h"
#include "../../gui_boton.h"
#include "../../gui_maquetador.h"

using namespace gui;


class Ventana_basica:public Ventana{
public:
    Ventana_basica();
    ~Ventana_basica(){}

private:
    Etiqueta et{"Hola, mundo!"};
};


Ventana_basica::Ventana_basica()
    :Ventana{Size{150_pix,50_pix}, "basica"}
{ 
    et.coloca(*this, Posicion{10_pix,10_pix});

    et.borde(Widget::Tipo_borde::solido);
}   


class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();
    ~Ventana_prueba(){}

private:
    Boton bt_aumenta{"+", cb_aumenta};
    Boton bt_disminuye{"-", cb_disminuye};


    static void cb_aumenta(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->aumenta();}

    static void cb_disminuye(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->disminuye();}

    void aumenta()
    {
	size(ancho() + 100_pix, alto() + 100_pix);
    }

    void disminuye()
    {
	size(ancho() - 100_pix, alto() - 100_pix);
    }
};


Ventana_prueba::Ventana_prueba()
    :Ventana{Size{150_pix,150_pix}, "prueba"}
{ 
    Maquetador m{*this};

    m.primer_widget(bt_disminuye);
    m.a_la_dcha(bt_aumenta);

    bt_disminuye.tooltip("Disminuye el tamaño de la ventana");
    bt_aumenta.tooltip("Aumenta el tamaño de la ventana");
}   



int main(int argc, char* argv[])
{
    Posicion p0{400_pix,100_pix};
    Posicion p1{500_pix,600_pix};

    Ventana_basica v;
    Ventana_prueba pru;

    v.show(p0);
    pru.show(p1);

    return gui_main();
}



