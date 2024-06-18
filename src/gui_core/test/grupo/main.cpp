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
#include <numeric>

#include "../../gui_core.h"


using namespace std;
using namespace alp;
using namespace gui;


class Input_punto:public Grupo_horizontal{
public:
    Input_punto();

private:
    Input_int x{"Punto: ", 4_car, 0};
    Input_int y{", "	 , 4_car, 0};
};

// Calculamos el tamaño del grupo
Input_punto::Input_punto()
    :Grupo_horizontal{""}
{
    push_back(x);
    push_back(y);
}

/*!
 *  \brief  Es un Combo_strings con un botón + para añadir nuevos elementos.
 *
 *  Es una prueba para probar Grupo_horizontal. Lo ideal es que este 
 *  combo heredara de Combo_strings, pero no funcionaria con Grupo_horizontal.
 *  Así que realmente es un wrapper del combo (lo cual es un incordio para 
 *  mantener; ¿no se podría heredar?).
 *
 */
//class Combo_strings_mas:public Grupo_horizontal{
//public:
//    /// Crea un combo de título y ancho (dado en número de caracteres).
//    Combo_strings_mas(const std::string& titulo
//		    , unsigned num_caracteres_ancho_combo);
//
//    /// \brief Añadimos un item, siempre y cuando no exista en el combo.
//    ///
//    /// Si la cadena está ya en la lista, no la añade. 
//    /// No añade cadenas vacías, y elimina todos los espacios del principio 
//    /// y del final.
//    /// Lo añade al final de la lista, ya que es una lista desordenada.
//    ///
//    /// \return true: añade un nuevo elemento a la lista
//    ///         false: no lo añade, porque ya estaba en la lista o es vacía
//    bool push_back(const std::string& item){return combo_.push_back(item);}
//
//    /// \brief Añade el elemento "item" ordenándolo alfabéticamente
//    ///
//    /// Internamente llama a push_back, así que cumple las mismas condiciones.
//    ///
//    /// \return Indica si añade (true) o no (false) el item al combo.
//    bool add_sort(const std::string& item) {return combo_.add_sort(item);}
//
//    /// Ordena el combo
//    void sort() {combo_.sort();}
//
//    /// Leemos el valor seleccionado por el usuario
//    std::string operator()() const {return combo_();}
//
//    /// Escribimos el valor seleccionado
//    void operator()(const std::string& v) {combo_(v);}
//
//private:
//    Combo_strings combo_;
//    Boton bt_{"+", cb_add};
//
//    static void cb_add(void*, void* grupo)
//    {static_cast<Combo_strings_mas*>(grupo)->add_input();}
//
//    void add_input()
//    { combo_.push_back(combo_()); }
//};
//
//
//Combo_strings_mas::Combo_strings_mas(const std::string& titulo
//		, unsigned num_caracteres_ancho_combo)
//    :Grupo_horizontal{""}
//    , combo_{titulo, num_caracteres_ancho_combo}
//{
//    // hacemos el botón del mismo alto que el combo
//    bt_.alto(combo_.alto());
//
//    // Dos formas de definirlo, a elegir:
//    // 1.- Con <<
//    *this << combo_ << bt_;
//
//    // 2.- Con push_back.
////	push_back(combo);
////	push_back(bt);
//}
//




class Ventana_prueba:public Ventana{
public:
    Ventana_prueba();
    ~Ventana_prueba(){}

private:
    Etiqueta et_horizontal{"Estos son grupos horizontales:"};   
    Input_punto punto;
    Combo_strings_mas combo{"Colores", 10_car};

    Circular_bool op1{"Opción 1", true};
    Circular_bool op2{"Opción 2", false};
    Circular_bool op3{"Opción 3", false};
    Grupo_horizontal grh_opciones{"Grupo horizontal"};

    Etiqueta et_vertical{"Estos son grupos verticales:"};   
    Circular_bool op4{"Opción 4", true};
    Circular_bool op5{"Opción 5", false};
    Circular_bool op6{"Opción 6", false};
    Grupo_vertical grv_opciones{"Grupo vertical"};

    Grupo_horizontal gh{"Horizontal"};
    Grupo_vertical gv{"Vertical"};
    Etiqueta et01{"Etiqueta 01"};
    Etiqueta et02{"Etiqueta 02"};
    Etiqueta et03{"Etiqueta 03"};
    Etiqueta et04{"Etiqueta 04"};

    Boton bt_sort{"&Ordena", cb_sort};

    static void cb_sort(void*, void* ventana)
    {static_cast<Ventana_prueba*>(ventana)->sort();}

    void sort()
    { combo.sort(); }
};


Ventana_prueba::Ventana_prueba()
    :Ventana{Size{500_pix,500_pix}, "Probando grupos de controles"}
{
    Maquetador m{*this};
    m.primer_widget(et_horizontal);
    m.debajo(punto);

    grv_opciones    << op4 
		    << op5
		    << op6;
    m.debajo(grv_opciones);

    // 1.- Componer el grupo
    grh_opciones << op1 << op2 << op3;

    // 2.- Colocarlo en la ventana
    m.debajo(grh_opciones);

    m.debajo(combo);
    m.debajo(bt_sort);




    // TODO: esto pudiera estar bien???
    // Tal como está hecho, no funciona.
//    gh << et02 << et03 << et04;
//    gv	<< et01 
//	<< gh;
//
//    m.debajo(gv);

    // Para comprobar que se crean de los anchos correctos
    et_horizontal.borde(Widget::Tipo_borde::solido);
    et_vertical.borde(Widget::Tipo_borde::solido);


    grh_opciones.borde(Widget::Tipo_borde::solido);
    grh_opciones.borde_titulo(Widget::Tipo_borde::solido);
    grv_opciones.borde(Widget::Tipo_borde::solido);
    grv_opciones.borde_titulo(Widget::Tipo_borde::solido);

    punto.borde(Widget::Tipo_borde::solido);
    punto.borde_titulo(Widget::Tipo_borde::solido);
    combo.borde(Widget::Tipo_borde::solido);
    combo.borde_titulo(Widget::Tipo_borde::solido);


    // relleno el combo
    combo.push_back("uno");
    combo.push_back("dos");

}



int main()
{
try{
    Ventana_prueba v;
    v.show(50_pix, 50_pix);

    return gui_main();

}catch(const std::exception& e){
    cerr << e.what() << '\n';
}
    return 1;
}
