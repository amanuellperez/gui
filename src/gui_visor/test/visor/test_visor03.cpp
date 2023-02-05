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


// Probamos las funciones de dibujo del visor

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <alp.h>
#include <img.h>

#include "../../gui_core.h"

using namespace std;
using namespace gui;
using img::Imagen;
using img::read;
using img::write;
using alp::Traza;



class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();
    ~Ventana_prueba(){cout << "~Ventana_prueba()\n";}

private:
    Visor visor;
    Imagen img0;

    Boton bt_clear{"&clear", cb_clear};
    Boton bt_linea{"&Dibujar linea lentamente", cb_linea};

    Etiqueta et_ayuda{"Pincha con el ratón sobre el visor"};


    bool push_left(Posicion p)  override;
    

    static void cb_clear(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->clear();}

    void clear()
    { visor.refresh();}

    static void cb_linea(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->linea();}

    void linea();
};


Ventana_prueba::Ventana_prueba()
    :Ventana{Size{600_pix, 500_pix}, "Probando funciones draw"}
    , visor{Size{400_pix, 400_pix}}
    , img0{img::imagen_negra(100,100)}
{
    es_principal();

    Maquetador m{*this};
    m.primer_widget(visor);
    m.debajo(et_ayuda);
    m.a_la_dcha_de(visor, bt_clear);
    m.debajo(bt_linea);

    img0 = read("../../../../../z/03.jpg");

    // muestro  un pequeño rectangulo pequeño para ver
    // si las coordenadas marcadas son correctas
    visor.imagen(img0, img::Rectangulo{{60,74}, {80, 94}});
}


bool Ventana_prueba::push_left(Posicion p)
{
    cout << "Pinchaste en: " << p << '\n';

    if(pertenece(p, visor)){
	cout << "pertenece\n";
	auto p_v = p-visor.p0();
	cout << "coordenadas de visor: " << p_v << '\n';
	visor.draw_visor(p_v, img::ColorRGB::rojo());
	visor.redraw();
    }
    else{
	cout << "no pertenece\n";
	return false;
    }


    return true;
}



void Ventana_prueba::linea()
{
    int i = visor.imgv_rows()/2;

    for (int j = 0; j < visor.imgv_cols(); ++j){
	visor.draw_local(img::Posicion{i,j}, img::ColorRGB::rojo());
	visor.redraw();
	cout << "." << flush;
	alp::sleep_for(std::chrono::milliseconds(100));
    }
    cout << "   FIN" << std::endl;

}


int main( int argc, char** argv )
{
try
{	
    const Posicion p0{100_pix, 100_pix};
    Ventana_prueba v;
    v.show(p0);

    return gui_main();
}
catch(alp::Excepcion e)
{ cerr << '\n' << e.what()<< '\n'; }

    return -2;
}


