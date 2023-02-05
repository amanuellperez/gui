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


#include "../../gui_core.h"


using namespace std;
using namespace gui;


class Ventana_ayuda:public Ventana{
public:
    Ventana_ayuda();
    ~Ventana_ayuda(){}

private:
    Menu_bar menu;

    static void cb_open(void*, void* ventana)
    {static_cast<Ventana_ayuda*>(ventana)->open();}

    void open()
    {	
	cout << "\nPulsaste: ESTE ES EL MENU\n"; 
    }
};

Ventana_ayuda::Ventana_ayuda()
    :Ventana{Size{200_pix,200_pix}, "Ayuda"}
{
    Maquetador m{*this};
    m.primer_widget(menu);

    menu.add("ESTE ES EL MENU", "a", cb_open);

}

class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();
    ~Ventana_prueba(){}

private:
    // controles
    Menu_bar menu;
    Etiqueta et{"Esto es una etiqueta"};

    // otras ventanas
    Ventana_ayuda vt_ayuda;

    // callbacks
    static void cb_open(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->open();}

    void open()
    {	
	cout << "\nAbriendo otra ventana\n"; 
	vt_ayuda.show();
    }
};


Ventana_prueba::Ventana_prueba()
    :Ventana{Size{300_pix,300_pix}, "Ventana con controles"}
{ 
    // maqueta()
    Maquetador m{*this};
    m.primer_widget(menu);
    m.debajo(et);

    // configuramos los controles dinámicamente
    menu.add("&Menu/&Abre", "a", cb_open);
}


int main(int argc, char* argv[])
{
    Posicion p0{100_pix,100_pix};

    Ventana_prueba v;
    v.show(p0);

    return gui_main();
}



