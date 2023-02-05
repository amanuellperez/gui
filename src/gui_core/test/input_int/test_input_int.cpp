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

#include <alp_test.h>


using namespace gui;

using std::cout;
using alp::Excepcion;

using namespace test;

int main()
{
try{
    Input_int a{"x", 20_pix, 10};
    CHECK_TRUE(a == 10, "Input_int{}");

    a = 35;
    CHECK_TRUE(a == 35, "operator=(int)");

    Input_int b{"b", 10_pix, 10};
 
    b = a;
    CHECK_TRUE(b == 35, "operator=(Input_int)");

    b= 10;
    a+= b;
    CHECK_TRUE(a == 45, "operator+=(Input_int)");

    a-= b;
    CHECK_TRUE(a == 35, "operator-=(Input_int)");

    a+= 5;
    CHECK_TRUE(a == 40, "operator+=(int)");

    a-= 10;
    CHECK_TRUE(a == 30, "operator-=(int)");

    a*=2;
    CHECK_TRUE(a == 60, "operator*=(int)");

    a/=2;
    CHECK_TRUE(a == 30, "operator/=(int)");


    CHECK_FALSE(a == b, "operator==(Input_int)");
    CHECK_TRUE(a != b, "operator==(Input_int)");


}catch(const std::exception& e){
    std::cerr << e.what() << '\n';
    return 1;
}
    return 0;
}
