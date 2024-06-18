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


#include "../../gui_input_int.h"

#include "../../gui_core.h"

#include <alp.h>
#include <alp_test.h>

using namespace gui;

using std::cout;
using alp::Excepcion;


int main()
{
try{
    Input_int_acotado a{"x", 20_pix, 10};
    test::check_true(a == 10, "Input_int_acotado{}");

    a = 35;
    test::check_true(a == 35, "operator=(int)");

    Input_int_acotado b{"b", 10_pix, 10};
 
    b = a;
    test::check_true(b == 35, "operator=(Input_int_acotado)");

    b= 10;
    a+= b;
    test::check_true(a == 45, "operator+=(Input_int_acotado)");

    a-= b;
    test::check_true(a == 35, "operator-=(Input_int_acotado)");

    a+= 5;
    test::check_true(a == 40, "operator+=(int)");

    a-= 10;
    test::check_true(a == 30, "operator-=(int)");

    a*=2;
    test::check_true(a == 60, "operator*=(int)");

    a/=2;
    test::check_true(a == 30, "operator/=(int)");


    test::check_false(a == b, "operator==(Input_int_acotado)");
    test::check_true(a != b, "operator==(Input_int_acotado)");

    // probamos las cotas
    a = -4;
    test::check_true(a == -4, "operator=(int)");

    a.min(0);
    test::check_true(a == 0, "min(0)");
    
    a = 20;
    a.max(10);
    test::check_true(a == 10, "max(10)");


    a+=3;
    test::check_true(a == 10, "a+=3 (pasandose)");

    a-=3;
    test::check_true(a == 7, "a-=3");
    
    a-=10;
    test::check_true(a == 7, "a-=10 (pasandose)");

    a-=7;
    test::check_true(a == 0, "a-=7 (borde)");

    a = 1;
    a *= 2;
    test::check_true(a == 2, "a*=2");

    a *= 20;
    test::check_true(a == 2, "a*=20 (pasandose)");

    a /= 2;
    test::check_true(a == 1, "a/=2");

    a /= -1;
    test::check_true(a == 1, "a/=-1 (pasandose)");

}catch(alp::Excepcion e){
    std::cerr << e.what() << '\n';
    return 1;
}
    return 0;
}
