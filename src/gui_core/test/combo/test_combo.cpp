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


#include "../../gui_combo_strings.h"

#include "../../gui_core.h"

using namespace alp;
using namespace gui;

using std::cout;
using std::cerr;

class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();
    ~Ventana_prueba(){}

private:
    Combo_strings combo{"Un combo", 10_car};
    Boton bt_sort{"&Ordena", cb_sort};
    Boton bt_add{"&Añade", cb_add};
    Boton bt_addsort{"Añade ordenado", cb_addsort};
    Boton bt_escribe{"&Escribe en combo", cb_escribe};
    Boton bt_hay_seleccion{"&Hay selección?", cb_hay_seleccion};

    static void cb_sort(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->sort();}

    void sort() {combo.sort();}

    static void cb_add(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->add();}

    void add() 
    {
	// añadimos el elemento seleccionado
	combo.push_back(combo());
    }

    static void cb_addsort(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->addsort();}

    void addsort() 
    {
	combo.add_sort(combo());
    }

    static void cb_escribe(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->escribe();}

    void escribe() 
    { combo("Escrito automáticamente"); }

    static void cb_hay_seleccion(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->hay_seleccion();}

    void hay_seleccion() 
    {
	cout << std::boolalpha << combo.hay_seleccion() << '\n';
    }

};


Ventana_prueba::Ventana_prueba()
    :Ventana{Size{400_pix, 400_pix}, "Prueba"}
{
    Maquetador m{*this};

    m.primer_widget(combo);
    grupo(m)	<< endl
		<< bt_sort << bt_add << bt_addsort << endl
		<< bt_escribe << bt_hay_seleccion;
    
    // rellenamos el combo
    combo.push_back("uno");
    combo.push_back("dos");
    combo.push_back("tres");
}

int main(int argc, char* argv[])
{
try{
    Ventana_prueba v;

    v.show(20_pix,20_pix);

    gui_main();
}catch(Excepcion e){
    cerr << e.what() << std::endl;
    return 1;
}

    return 0;
}


