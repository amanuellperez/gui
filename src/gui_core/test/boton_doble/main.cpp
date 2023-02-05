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


#include "../../gui_boton_doble.h"

#include "../../gui_core.h"

using alp::Excepcion;
using namespace std;
using namespace gui;


class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();
    ~Ventana_prueba(){}

private:
    Boton_doble bt_doble_{this
			, "Encendido", cb_on
			, "Apagado", cb_off};

    // callbacks
    static void cb_on(void*, void* ventana)
    { static_cast<Ventana_prueba*>(ventana)->on(); }
    
    void on() { cout << "Has pulsado encendido\n"; }

    static void cb_off(void*, void* ventana)
    { static_cast<Ventana_prueba*>(ventana)->off(); }

    void off() { cout << "Has pulsado apagado\n"; }

};

Ventana_prueba::Ventana_prueba()
    :Ventana{Size{300_pix, 100_pix}, "Prueba"}
{
    Maquetador m{*this};
    m.primer_widget(bt_doble_);
}



int main(int argc, char* argv[])
{
try{
    Ventana_prueba v;
    v.show(50_pix, 50_pix);

    return gui_main();

}catch(const std::exception& e){
    cerr << e.what();
    return 1;
}

    return 0;
}
