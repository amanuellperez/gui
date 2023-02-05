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


#include "../../gui_check_bool.h"

#include "../../gui_core.h"



using namespace gui;

using std::cout;
using alp::Excepcion;

void comprueba(const Check_bool& b, bool v)
{
    cout << std::boolalpha << bool(b);
    if(b == v)	cout << " OK\n";
    else{
	cout << " ERROR!!!\n";
	throw Excepcion{""};
    }
}

// La condición 'cond' tiene que ser true. En caso contrario ha habido un
// error.
void comprueba_true(bool cond, const std::string& prueba)
{
    cout << prueba;
    if(cond)	cout << " OK\n";
    else{
	cout << " ERROR!!!\n";
	throw Excepcion{""};
    }
}



class Ventana_main:public Ventana{
public:
    Ventana_main();
private:
    Check_bool red{"red (sin marcar)"};
    Check_bool green{"green (marcado)", true};

    Boton bt_imprimir{"&Imprimir valores", cb_imprime};


    static void cb_imprime(void*, void* ventana)
    {static_cast<Ventana_main*>(ventana)->imprime();}

    void imprime()
    {	
	cout << "red = " << std::boolalpha << bool(red) << '\n';
	cout << "green = " << std::boolalpha << bool(green) << '\n';
    }
};

Ventana_main::Ventana_main()
    :Ventana{Size{300_pix, 300_pix}, "check_bool"}
{
    Maquetador m{*this};

    m.primer_widget(red);
    m.debajo(green);
    m.debajo(bt_imprimir);
}


void f(bool b)
{
    cout << "Se convierte de forma implícita a bool ... OK\n";
}

void g(const Check_bool& b)
{
    throw Excepcion{"La función g no tiene que compilar\n"};
}


int main()
{
try{
    Check_bool b{"prueba", true};
    comprueba(b, true);

    b = false;
    comprueba(b, false);

    f(b);

    comprueba_true(b == false, "b == false");
    comprueba_true(false == b, "false == b");
    comprueba_true(b != true, "b != true");
    comprueba_true(true != b, "true != b");



    // Esto no tiene que compilar. Comentarlo para probarlo.
//    bool a = true;
//    g(a);


    Ventana_main v;
    v.show(100_pix,100_pix);

    return gui_main();
}catch(const std::exception& e){
    std::cerr << e.what() << '\n';
    return 1;
}
    return 0;
}
