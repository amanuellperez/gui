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


// Muestra cómo el programador puede dibujar en la pantalla

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
    Menu_bar menu;
    Visor visor;

    Imagen img0;

    static void cb_rojo(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->rojo();}

    void rojo();
};


Ventana_prueba::Ventana_prueba()
    :Ventana{Size{550_pix, 550_pix}, "Prueba"}
    , visor{Size{500_pix, 500_pix}}
    , img0{read("../../../d/03.jpg")}
{
    Traza tr{"Ventana_prueba"};

    es_principal();

    Maquetador m{*this};
    m.primer_widget(menu);
    m.debajo(visor);

    // en visor muestro una imagen, pero en visor02 no muestro nada
    visor.imagen(img0);

    menu.add("&Rojo", "", cb_rojo);
}


void Ventana_prueba::rojo()
{
    auto img0 = visor.imgv();
    img::only_red(img0);
    visor.draw_imgv(img0);

    visor.redraw();
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


