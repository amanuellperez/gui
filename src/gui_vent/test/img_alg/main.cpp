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


// Probamos la función img::muestrea

#include <iostream>

#include <alp.h>
#include <img.h>
#include "../../gui.h"


using namespace std;
using namespace gui;

using img::Imagen;
using img::read;
using img::write;



class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();

private:
    Imagen img0; // original
    Imagen img1; // la que muestro en el visor

    Visor visor;

    Boton bt_muestrea{"img::muestrea", cb_muestrea};
    Input_int ancho_muestreo{"ancho muestreo", 3_car, 10};

    Boton bt_simetrica_y{"img::simetrica_y", cb_simetrica_y};
    Boton bt_simetrica_x{"img::simetrica_x", cb_simetrica_x};


    static void cb_muestrea(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->muestrea();}

    void muestrea()
    {
	img1 = img::muestrea(img0, ancho_muestreo, ancho_muestreo);
	visor.imagen(img1);

    }



    static void cb_simetrica_y(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->simetrica_y();}

    void simetrica_y()
    {
	img1 = img::simetrica_y(img1);
	visor.imagen(img1);

    }



    static void cb_simetrica_x(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->simetrica_x();}

    void simetrica_x()
    {
	img1 = img::simetrica_x(img1);
	visor.imagen(img1);

    }

};



Ventana_prueba::Ventana_prueba()
    :Ventana{Size{650_pix, 500_pix},  "Muestrea"}
    , img0{read("../../../../../d/03.jpg")}
    , img1{img0.clone()}
    , visor{Size{400_pix, 400_pix}}
{
    es_principal();
    visor.imagen(img1);

    Maquetador m{*this};
    m.primer_widget(visor);

    m.a_la_dcha(bt_muestrea);
    m.debajo(ancho_muestreo);
    m.linea_en_blanco();
    m.debajo(bt_simetrica_y);
    m.debajo(bt_simetrica_x);
}


int main( int argc, char** argv )
{
try
{	
    const Posicion p0{100_pix, 100_pix};

    Ventana_prueba v0;
    v0.show(p0);

    return gui_main();
}
catch(alp::Excepcion e)
{ 
    cerr << '\n' << e.what()<< '\n'; 
}
catch(...)
{
    cerr << "Otra excepcion\n";
}

    return -2;
}


