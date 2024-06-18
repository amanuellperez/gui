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


// Probamos las funciones de movimiento de un visor

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
    Boton bt_zoom_mas{"+", cb_zoom_mas};
    Boton bt_zoom_menos{"-", cb_zoom_menos};
    Input_int incr_zoom{"incr. zoom = ", 4_car, 4};

    Boton bt_dcha {"->", cb_dcha};
    Boton bt_izda {"<-", cb_izda};
    Boton bt_abajo {"!", cb_abajo};
    Boton bt_arriba {"¡", cb_arriba};
    Boton bt_muevete {"Mueve (v_i, v_j)", cb_muevete};

    Input_int v_i{"v_i = ", 3_car, 4};
    Input_int v_j{"v_j = ", 3_car, 4};

    Visor visor01;
    Imagen img0;

    static void cb_zoom_mas(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->zoom_mas();}

    void zoom_mas()
    { visor01.zoom(Coordenada::en_pix(incr_zoom)
		   , Coordenada::en_pix(incr_zoom)); }

    static void cb_zoom_menos(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->zoom_menos();}

    void zoom_menos()
    { visor01.zoom(Coordenada::en_pix((-1)*incr_zoom)
	    , Coordenada::en_pix((-1)*incr_zoom)); }

    static void cb_dcha(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->dcha();}

    void dcha()
    { visor01.muevete_a_la_dcha(v_j);}
    //{ visor01.muevete(img::Vector2D{0, v_j}); }

    static void cb_izda(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->izda();}

    void izda()
    { visor01.muevete_a_la_izda(v_j); }


    static void cb_abajo(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->abajo();}

    void abajo()
    { visor01.muevete_abajo(v_i);}


    static void cb_arriba(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->arriba();}

    void arriba()
    { visor01.muevete_arriba(v_i);}

    static void cb_muevete(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->muevete();}

    void muevete()
    { visor01.muevete(img::Vector{v_i, v_j}); }

};


Ventana_prueba::Ventana_prueba()
    :Ventana{Size{600_pix, 500_pix}, "Prueba"}
    , visor01{Size{400_pix, 400_pix}}
    , img0{img::imagen_negra(100,100)}
{
    es_principal();

    mismo_ancho_mayor(bt_zoom_mas, bt_zoom_menos);
    mismo_ancho_mayor(bt_dcha, bt_izda);
    mismo_ancho_mayor(bt_dcha, bt_arriba);
    mismo_ancho_mayor(bt_dcha, bt_abajo);

    Maquetador m{*this};
    m.primer_widget(visor01);
    m.a_la_dcha(bt_zoom_mas);
    m.a_la_dcha(bt_zoom_menos);
    m.debajo_de(bt_zoom_mas, incr_zoom);
    m.debajo(bt_arriba);
    m.debajo(bt_izda);
    m.a_la_dcha(bt_dcha);
    m.debajo_de(bt_izda, bt_abajo);
    m.debajo(v_i);
    m.a_la_dcha(v_j);
    m.debajo_de(v_i, bt_muevete);


    // en visor01 muestro una imagen, pero en visor02 no muestro nada
    img0 = read("../../../../../z/03.jpg");

    visor01.imagen(img0, img::Rectangulo{{0,0}, {100, 100}});
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


