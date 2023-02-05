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


#include "../../gui_tipos.h"
#include <iostream>


using namespace gui;


void comprueba(const Coordenada& c, int v)
{
    std::cout << c;
    if(c.pix() == v)	std::cout << " OK\n";
    else{
	std::cout << " ERROR!!!\n";
	throw alp::Excepcion{""};
    }
}

void comprueba(Posicion p, int x, int y)
{
    std::cout << p;
    if((p.x.pix() == x) and (p.y.pix() == y))	std::cout << " OK\n";
    else{
	std::cout << " ERROR!!!\n";
	throw alp::Excepcion{""};
    }
}

int main(int argc, char* argv[])
{
try{
    // Coordenadas
    Coordenada c1 = 20_pix;
    comprueba(c1, 20);

    Coordenada c2 = "-20"_pix;
    comprueba(c2, -20);

    c2 = "30"_pix;
    comprueba(c2, 30);

    comprueba(2*c2, 60);
    comprueba(c2*3, 90);


    // Longitudes
    Longitud l1 = 40_pix;
    Coordenada c3 = c2 + l1;
    comprueba(c3, 70);
    
    c3-= 60_pix;
    comprueba(c3, 10);

    // Anchos
    Ancho a1 = 40_pix;
    c3+=a1;
    comprueba(c3, 50);

    // se promocina a1 a coordenada. Se puede restar.
    Coordenada c4 = c3 - c2 - a1;
    comprueba(c4, -20);
    
    Ancho a2 = 300_pix;
    try{
	// esto tiene que lanzar una excepción
	std::cout << "Restando anchos menor - mayor ...";
	Ancho a3 = a1-a2;
	std::cout << a3;
	std::cout << " ERROR!!!\n";
	throw alp::Excepcion{""};
    }catch(const std::exception&){
	std::cout << " OK!!!\n";
    }


    // Altos
    Alto h1 = 30_pix;
    c3-=h1;
    comprueba(c3, 20);


    Posicion p1{10_pix, 20_pix};
    comprueba(p1, 10, 20);

    Posicion p2 = p1;
    comprueba(p2, 10, 20);

    p2 = Posicion{40_pix, 50_pix};
    comprueba(p2, 40, 50);

    p2+= {5_pix, 6_pix};
    comprueba(p2, 45, 56);

    auto p3 = p2-p1;
    comprueba(p3, 35, 36);

    a2 = 100_pix; 
    Alto h2 = 200_pix;
    p3 = Posicion{a2, h2};
    comprueba(p3, 100, 200);

    p3+=Posicion{0_pix, 20_pix};
    comprueba(p3, 100, 220);


}catch(const std::exception& e){
    std::cerr << e.what() << '\n';
    return 1;
}

    return 0;
}


