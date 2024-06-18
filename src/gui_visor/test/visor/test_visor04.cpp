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
#include <img.h>
#include "../gui.h"


using namespace std;
using namespace gui;
using img::Imagen;
using img::read;
using img::write;
using alp::Traza;

const char AYUDA[] =	"prueba\n";

const char CAYUDA[]=	"Forma de uso: exp imagen.jpg\n"
"Programa para experimentar con imágenes\n";





class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();
    ~Ventana_prueba(){cout << "~Ventana_prueba()\n";}

private:
    Boton bt_boton{"&cambia img", cb_boton};
    Visor visor01;
    Visor visor02;

    Imagen img0;
    Imagen img1;

    static void cb_boton(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->boton();}

    void boton()
    {
	img1 = read("../../../d/02.jpg");
	visor01.imagen(img1, rectangulo(img1));
	visor02.imagen(img1, rectangulo(img1));
    }

};


Ventana_prueba::Ventana_prueba()
    :Ventana{Size{550_pix, 500_pix}, "Prueba"}
    , visor01{Size{100_pix, 100_pix}}
    , visor02{Size{300_pix, 300_pix}}
    , img0{Imagen::negra(100,100)}
    , img1{Imagen::negra(200,200)}
{
    Traza tr{"Ventana_prueba"};

    es_principal();

    Maquetador m{*this};
    m.primer_widget(bt_boton);
    m.debajo(visor01);
    m.a_la_dcha(visor02);

    // en visor01 muestro una imagen, pero en visor02 no muestro nada
    img0 = read("../../../d/03.jpg");
    visor01.imagen(img0, rectangulo(img0));
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


