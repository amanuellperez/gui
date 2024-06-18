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


#include <iostream>


#include <alp.h>
#include "../gui.h"


using namespace std;
using namespace gui;

class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();
    ~Ventana_prueba(){}

private:
    Boton bt_{"Pregunta", cb_boton};


    static void cb_boton(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->boton();}

    void boton()
    { 
	auto nom_fichero = Cliente::ask_nombre_fichero("Elige imagen", "*.jpg");

	if(!nom_fichero.empty())
	    cout << "Has elegido [" << nom_fichero << "]\n";
	else
	    cout << "Cancelaste\n";

	auto nom_fichero2 
	    = Cliente::ask_nombre_fichero("Este buscamos en /home", "*", "/home");
    }

};

Ventana_prueba::Ventana_prueba()
    :Ventana{Size{300_pix, 300_pix}, "Pregunta"}
{
    bt_.coloca(*this, Posicion{10_pix,10_pix});
}

int main()
{
try{
    Ventana_prueba v;
    v.show(100_pix,100_pix);

    return gui_main();

}catch(alp::Excepcion e){
    cerr << e.what();
    return 1;
}

}
