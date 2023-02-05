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


#include "../gui_visor.h"
#include <gui_core.h>
#include <img.h>

#include <alp_test.h>

using namespace alp;
using namespace test;
using namespace gui;

class Ventana_prueba: public Ventana{
public:
    Ventana_prueba()
	:Ventana{Size{600_pix, 500_pix}, "probando visor"}
	, visor{Size{450_pix, 450_pix}}
    {
	es_principal();

	Maquetador m{*this};
	m.primer_widget(visor);
	m.a_la_dcha(bt_carga_img);

    }

    ~Ventana_prueba(){}

private:
    Visor visor;

    Boton bt_carga_img{"&carga img", cb_carga};

    static void cb_carga(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->carga_img();}

    void carga_img()
    {
	img0 = img::read("prueba.jpg");
	visor.de(img0); 
	visor.refresh();
    }

    img::Image img0{0,0};
};


int main()
{
try{
    Ventana_prueba v;

    v.show();

    return gui_main();

}catch(std::exception& e){
    std::cerr << e.what() << '\n';
    return 1;
}
}

