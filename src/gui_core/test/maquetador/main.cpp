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


// Pruebo las funciones de colocar del maquetador
#include <iostream>

#include "../../gui_maquetador.h"
#include "../../gui_core.h"


using namespace gui;

class Ventana2:public Ventana{
public:
    Ventana2();

private:
    Etiqueta et01{"etiqueta 01"};
    Etiqueta et02{"etiqueta 02"};
    Etiqueta et03{"etiqueta 03"};
    Etiqueta et04{"etiqueta 04"};
    Etiqueta et05{"etiqueta 05"};
    Etiqueta et06{"etiqueta 06"};
    Etiqueta et07{"etiqueta 07"};
    Etiqueta et08{"etiqueta 08"};
    Etiqueta et09{"etiqueta 09"};
    
};


Ventana2::Ventana2()
    :Ventana{Size{800_pix, 500_pix}, "Prueba 02"}
{
    Maquetador m{*this};

    m.primer_widget(et01);
    grupo_horizontal(m) << et02 << et03;
    grupo_vertical(m) << et04 << et05;
    grupo(m) << et06 << et07 << endl
	    << et08 << et09;

    et01.borde(Widget::Tipo_borde::solido);
    et02.borde(Widget::Tipo_borde::solido);
    et03.borde(Widget::Tipo_borde::solido);
    et04.borde(Widget::Tipo_borde::solido);
    et05.borde(Widget::Tipo_borde::solido);
    et06.borde(Widget::Tipo_borde::solido);
    et07.borde(Widget::Tipo_borde::solido);
    et08.borde(Widget::Tipo_borde::solido);
    et09.borde(Widget::Tipo_borde::solido);
}




class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();

private:
    Etiqueta et01{"Esto es una etiqueta."};
    Etiqueta et02{"Esta es la segunda."};
    Etiqueta et03{"Y una tercera."};
    Etiqueta et04{"Debajo están alineadas a la izquierda"};
    Etiqueta et05{"Este es el quinto"};
    Etiqueta et06{"Sexto"};
    Etiqueta et07{"Debajo de esta etiqueta, alineadas a la dcha."};
    Etiqueta et08{"Octava"};
    Etiqueta et09{"Y una novena"};

    Etiqueta et10{"Debajo estan alineadas centradas"};
    Etiqueta et11{"Esta centrada."};
    Etiqueta et12{"Y esta también está centrada"};

    Etiqueta et13{"Usando"};
    Etiqueta et14{"grupo"};
    Etiqueta et15{"horizontal."};

    Etiqueta et16{"Otro"};
    Etiqueta et17{"grupo"};
    Etiqueta et18{"horizontal (sin espacios)"};

    Etiqueta et19{"Un"};
    Etiqueta et20{"grupo"};
    Etiqueta et21{"vertical"};

    Etiqueta et22{"Y otro"};
    Etiqueta et23{"grupo"};
    Etiqueta et24{"vertical 2"};

    Etiqueta et25{"1.1.- Una etiqueta, y debajo"};
    Etiqueta et26{"2.1.- va esta, y al lado"};
    Etiqueta et27{"2.2.- esta, y debajo"};
    Etiqueta et28{"3.1.- esta otra."};

    Etiqueta et29{"Encima de esta colocare..."};
    Etiqueta et30{"Encima a la derecha"};
    Etiqueta et31{"a la izda"};
    Etiqueta et32{"Una grande para poder colocar en medio"};
    Etiqueta et33{"encima en medio"};

    Etiqueta et34{"etiqueta 34"};
    Etiqueta et35{"Esta, está debajo de et34 pero alineada con Encima..."};
};


Ventana_prueba::Ventana_prueba()
    :Ventana{Size{800_pix, 500_pix}, "Prueba"}
{
    es_principal();

    Maquetador m{*this};

    m.primer_widget(et01);
    m.a_la_dcha(et02);
    m.justo_a_la_dcha(et03);

    m.selecciona(et01);
    m.linea_en_blanco();
    m.alinea_a_la_izda();
    m.debajo(et04);
    m.debajo(et05);
    m.debajo(et06);

    m.linea_en_blanco();
    m.muevete_al_lado_izdo_de_la_ventana(0);
    m.debajo(et07);

    m.alinea_a_la_dcha();
    m.debajo(et08);
    m.debajo(et09);

    m.linea_en_blanco();
    m.debajo(et10);
    m.alinea_al_centro();
    m.debajo(et11);
    m.debajo(et12);

    m.alinea_a_la_izda();
    m.debajo(et13);
    grupo_horizontal(m) << et14 << et15;
    m.debajo_de(et13, et16);
    grupo_horizontal(m,0_pix) << et17 << et18;
	
    m.debajo_de(et03, et19);
    grupo_vertical(m)   << et20 
			<< et21;

    m.selecciona(et19);
    m.muevete_a_la_dcha(5_car);
    m.a_la_dcha(et22);
    grupo_vertical(m, 0_pix) << et23
			     << et24;
    grupo(m) << endl
	     << et25 << endl
	     << et26 << et27 << endl
	     << et28;

    m.a_la_dcha_de(et18, et29);
    m.alinea_a_la_dcha();
    m.encima(et30);
    m.alinea_a_la_izda();
    m.encima(et31);
    m.encima(et32);
    m.alinea_al_centro();
    m.encima(et33);

    m.alinea_a_la_dcha();
    m.debajo_de(et29, et34);
    m.alinea_a_la_izda_de(et29);
    m.debajo(et35);

    m.resize_window();


    et01.borde(Widget::Tipo_borde::solido);
    et02.borde(Widget::Tipo_borde::solido);
    et03.borde(Widget::Tipo_borde::solido);
    et04.borde(Widget::Tipo_borde::solido);
    et05.borde(Widget::Tipo_borde::solido);
    et06.borde(Widget::Tipo_borde::solido);
    et07.borde(Widget::Tipo_borde::elevado);
    et08.borde(Widget::Tipo_borde::solido);
    et09.borde(Widget::Tipo_borde::solido);
    et10.borde(Widget::Tipo_borde::solido);
    et11.borde(Widget::Tipo_borde::solido);
    et12.borde(Widget::Tipo_borde::solido);
    et13.borde(Widget::Tipo_borde::solido);
    et14.borde(Widget::Tipo_borde::solido);
    et15.borde(Widget::Tipo_borde::solido);
    et16.borde(Widget::Tipo_borde::solido);
    et17.borde(Widget::Tipo_borde::solido);
    et18.borde(Widget::Tipo_borde::solido);
    et19.borde(Widget::Tipo_borde::solido);
    et20.borde(Widget::Tipo_borde::solido);
    et21.borde(Widget::Tipo_borde::solido);
    et22.borde(Widget::Tipo_borde::solido);
    et23.borde(Widget::Tipo_borde::solido);
    et24.borde(Widget::Tipo_borde::solido);
    et25.borde(Widget::Tipo_borde::solido);
    et26.borde(Widget::Tipo_borde::solido);
    et27.borde(Widget::Tipo_borde::solido);
    et29.borde(Widget::Tipo_borde::solido);
    et30.borde(Widget::Tipo_borde::solido);
    et31.borde(Widget::Tipo_borde::solido);
    et32.borde(Widget::Tipo_borde::solido);
    et33.borde(Widget::Tipo_borde::solido);
    et34.borde(Widget::Tipo_borde::solido);
    et35.borde(Widget::Tipo_borde::solido);
}


int main()
{
try
{	
    const Posicion p0{100_pix, 100_pix};
    Ventana_prueba v;
    Ventana2 v2;

    v.show(p0);
    v2.show({200_pix, 200_pix});

    return gui_main();
}
catch(const std::exception& e)
{ std::cerr << '\n' << e.what()<< '\n'; }

    return -2;
}


