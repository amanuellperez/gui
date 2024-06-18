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


#include "../gui_vent_mensaje_aviso.h"
#include "../gui_vent_pregunta.h"
#include "../gui_vent_pregunta_sino.h"

#include <iostream>
#include <alp.h>
#include "../gui_maquetador.h"

using namespace std;
using namespace alp;
using namespace gui;

class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();
    ~Ventana_prueba(){}

private:
    Boton bt_{"Pregunta", cb_boton};
    Boton bt2_{"Mensaje de aviso", cb_boton2};
    Boton bt3_{"Pregunta sí/no", cb_boton3};


    static void cb_boton(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->boton();}

    void boton()
    { 
	string respuesta;
	bool ha_respondido;
	tie(ha_respondido, respuesta) 
		= pregunta("¿Qué quieres responder?", "Mi pregunta");

	if(ha_respondido)
	    cout << "Has respondido [" << respuesta << "]\n";
	else
	    cout << "Cancelaste\n";
    }

    static void cb_boton2(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->boton2();}

    void boton2()
    {
	Ventana_mensaje_aviso vt{"Aviso!!!", "Este es el primer aviso"};
	vt.show(100_pix,100_pix);
    }

    static void cb_boton3(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->boton3();}

    void boton3()
    {
	gui::Ventana_pregunta_sino v{"Pregunta sí/no"
		, "¿Funciona? Esta si que es una pregunta larga, andaa que..."
		  , "Responde que si"};
	v.show(100_pix,100_pix);
	if(v.ha_respondido_si())
	    cout << "Has dicho que SÍ funciona\n";
	else
	    cout << "Has dicho que NO funciona\n";

	if(pregunta_sino("Esta es otra\n forma de preguntar\nOtra linea\n"
		    "Y otra\nY otra\n"))
	    cout << "Ahora has dicho que SÍ funciona\n";
	else
	    cout << "Ahora has dicho que NO funciona\n";

    }

};


Ventana_prueba::Ventana_prueba()
    :Ventana{Size{300_pix, 300_pix}, "Pregunta"}
{
    Maquetador m{*this};

    m.primer_widget(bt_);
    m.debajo(bt2_);
    m.debajo(bt3_);
}

int main()
{
try{
    Ventana_prueba v;
    v.show(100_pix,100_pix);

    return gui_main();

}catch(Excepcion e){
    cerr << e.what();
    return 1;
}

}
