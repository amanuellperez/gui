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
#include <fstream>
#include <string>
#include <map>

//#include <boost/filesystem.hpp>

#include "../../gui_core.h"



using namespace std;
using namespace gui;



class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();
    ~Ventana_prueba(){cout << "~Ventana_prueba()\n";}

private:
    Menu_bar menu;

    Boton bt_boton{"&Timer", cb_boton};
    Boton bt_boton02{"  ?  ", cb_boton};

    Boton bt_aumenta{"+", cb_aumenta};
    Boton bt_disminuye{"-", cb_disminuye};

    Check_bool rojo{"&rojo", true};
    Check_bool verde{"&verde", false};
    Check_bool azul{"", false};
    

    Input_string input01{"este es 1:", 10_car, ""};
    Input_int	 input02{"un número:", 4_car, 23};
    Input_int	 input03{"y otro:", 5_car, 0};

    Combo_strings combo01{"Colores:", 10_car};

    Etiqueta etiqueta{"Esto es una etiqueta"};
    Etiqueta etiqueta2{"Aumenta"};

    Linea linea{"Esta es una línea de texto"};
    Varias_lineas texto{"Esto es una parrafada\nVeamos a ver si es capaz de escribirla"
	    , Size{10_car, 5_lin}};

    Varias_lineas texto02{"Esto es otro mensaje.\nAunque este lo límito"
	    "a 10 caracteres de ancho y 3 líneas de alto"
		, 10, alp::Maximo<unsigned>{3}};

    static void cb_boton(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->boton();}

    static void cb_aumenta(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->aumenta();}

    static void cb_disminuye(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->disminuye();}

    void boton()
    { 
	Timer timer{linea, "Probando el timer"};
	alp::sleep_for(2s);
	timer.stop();
    }

    void aumenta()
    {
	etiqueta2.size(etiqueta2.ancho() + 10_pix, etiqueta2.alto() + 10_pix);
	redraw(); // que no se olvide!!!
    }

    void disminuye()
    {
	etiqueta2.size(etiqueta2.ancho() - 10_pix, etiqueta2.alto() - 10_pix);
	redraw(); // que no se olvide!!!
    }
};



Ventana_prueba::Ventana_prueba()
    :Ventana{Size{500_pix, 600_pix}, "Prueba"}
{
    cout << "VENTANA_PRUEBA()\n";
    es_principal();

    menu.coloca(*this);

    bt_boton.coloca(*this, {10_pix,60_pix});
    bt_boton02.coloca(*this, {10_pix,110_pix});

    // descomentar para colocarlos todos alineados a la izda
//    input01.coloca(*this, {200, 50});
//    input02.coloca(*this, {200, 80});
//    input03.coloca(*this, {200, 110});

    // los alineamos usando el input
    input01.coloca_input(*this, {300_pix, 50_pix});
    input02.coloca_input(*this, {300_pix, 80_pix});
    input03.coloca_input(*this, {300_pix, 110_pix});

    combo01.coloca_input(*this, {300_pix, 160_pix});

    rojo.coloca(*this, {100_pix, 60_pix});
    verde.coloca(*this, {100_pix, 80_pix});
    azul.coloca(*this, {100_pix, 100_pix});


    texto.coloca(*this, {10_pix, 200_pix});
    texto02.coloca(*this, {200_pix, 200_pix});
    
    etiqueta.coloca(*this, {10_pix, 350_pix});
    linea.coloca(*this, {0_pix, 400_pix});

    etiqueta2.coloca(*this, {10_pix, 500_pix});
    bt_aumenta.coloca(*this, {200_pix, 500_pix});
    bt_disminuye.coloca(*this, {250_pix, 500_pix});

    etiqueta.borde(Widget::Tipo_borde::solido);
    linea.borde(Widget::Tipo_borde::solido);
    texto.borde(Widget::Tipo_borde::plano);

    etiqueta2.borde(Widget::Tipo_borde::solido);
    
    // rellenamos controles
    menu.add("&Prueba/&Timer", "^t", cb_boton);


    input03.ancho();

    combo01.push_back("amarillo");
    combo01.push_back("rojo");
    combo01.push_back("verde");
    combo01.push_back("azul");
    combo01.sort();

    bt_boton02.tooltip("Esta es la ayuda de este boton");

    combo01.borde(Widget::Tipo_borde::solido);

}


int main( int argc, char** argv )
{
try
{	
//    if(argc < 2)
//    {
//	cerr << CAYUDA << endl;
//	return -1;
//    }// if(argc != 2)
//
//    string name = argv[1];
//    
//    Imagen img = read(name);   
//    Ventana_prueba v{img};

    const Posicion p0{100_pix, 100_pix};
    Ventana_prueba v;
    v.show(p0);

    return gui_main();
}
catch(alp::Excepcion e)
{ cerr << '\n' << e.what()<< '\n'; }

    return -2;
}


