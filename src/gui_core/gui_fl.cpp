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


#include "gui_fl.h"
#include "gui_base.h"
#include "gui_ventana.h"

#include <FL/Fl.H>



using namespace std;


namespace gui{

/***************************************************************************
 *				FL_VENTANA
 ***************************************************************************/
// La clase Fl_Ventana necesita tener un puntero a Ventana para poder llamar
// a v_->pulsa_tecla. Notar que quien sabe qué hacer cuando se pulsa una tecla
// es la clase hija de Ventana (vg: Ventana_ivi). Luego pulsa_tecla es una
// función virtual que define Ventana_ivi.
//
// Necesito gestionar FL_FOCUS, para que cuando llame ventana.take_focus()
// coja el foco.
int Fl_Ventana::handle(int event)
{
    bool procesado = false;

    if(event == FL_KEYDOWN)
	procesado = v_->pulsa_tecla(Fl::event_text(), Fl::event_key());
    else if(event == FL_FOCUS)
	procesado = true;
    else{
	// event_x/y devuelve la posición relativa a la ventana
//	int i = Fl::event_y();
//	int j = Fl::event_x();
	auto p = Posicion::en_pix(Fl::event_x(), Fl::event_y());

	if(event == FL_PUSH){
	    switch(Fl::event_button()){
		//case FL_LEFT_MOUSE:   procesado = v_->push_left(i,j);   break;
		case FL_LEFT_MOUSE:   procesado = v_->push_left(p);   break;
		case FL_MIDDLE_MOUSE: procesado = v_->push_middle(p); break;
		case FL_RIGHT_MOUSE:  procesado = v_->push_right(p);  break;
	    }
	} else if(event == FL_DRAG){
	    if(Fl::event_state(FL_BUTTON1)) procesado = v_->drag_left(p);
	    else if(Fl::event_state(FL_BUTTON2)) procesado = v_->drag_middle(p);
	    else if(Fl::event_state(FL_BUTTON3)) procesado = v_->drag_right(p);
	}else if(event == FL_RELEASE){
	    switch(Fl::event_button()){
		case FL_LEFT_MOUSE:   procesado = v_->release_left(p);   break;
		case FL_MIDDLE_MOUSE: procesado = v_->release_middle(p); break;
		case FL_RIGHT_MOUSE:  procesado = v_->release_right(p);  break;
	    }
	}
    }

    if(!procesado)
	return Fl_Window::handle(event);

    // si llega hasta aquí es que está procesado
    return 1;
}


// Para poder darle a las ventanas hijas de Ventana la capacidad de dibujar
// lo que quieran al llamar a redraw(), necesito esta ventana. Como 
// Ventana::draw es virtual, se llamará a la función correspondiente
void Fl_Ventana::draw()
{ 
    v_->draw(); 
    Fl_Window::draw();
}


/***************************************************************************
 *				FL_COMBO_STRINGS
 ***************************************************************************/
// De momento solo voy a permitir modificar la entrada de teclado al
// Combo_strings. 
// TODO: esto no funciona bien. ¿por qué?
//int Fl_Combo_strings::handle(int event)
//{
//    bool procesado = false;
//
//    switch(event){
//	case FL_KEYUP:
//	    cerr << "key up\n";
//	    break;
//
//	case FL_KEYDOWN:
//	    cerr << "key down\n";
//	    procesado = w_->pulsa_tecla(Fl::event_text(), Fl::event_key());
//	    break;
//
//	case FL_FOCUS:
//	    procesado = true;
//	    cerr << "fl_focus\n";
//	    break;
//
//	case FL_UNFOCUS: // cuando pierde el foco
//	    cerr << "fl_unfocus\n";
//	    procesado = true;
//	    break;
//
//    }// switch(event)
//
////    else{
////	// event_x/y devuelve la posición relativa a la ventana
////	int i = Fl::event_y();
////	int j = Fl::event_x();
////	if(event == FL_PUSH){
////	    switch(Fl::event_button()){
////		case FL_LEFT_MOUSE:   procesado = v_->push_left(i,j);   break;
////		case FL_MIDDLE_MOUSE: procesado = v_->push_middle(i,j); break;
////		case FL_RIGHT_MOUSE:  procesado = v_->push_right(i,j);  break;
////	    }
////	} else if(event == FL_DRAG){
////	    if(Fl::event_state(FL_BUTTON1)) procesado = v_->drag_left(i,j);
////	    else if(Fl::event_state(FL_BUTTON2)) procesado = v_->drag_middle(i,j);
////	    else if(Fl::event_state(FL_BUTTON3)) procesado = v_->drag_right(i,j);
////	}else if(event == FL_RELEASE){
////	    switch(Fl::event_button()){
////		case FL_LEFT_MOUSE:   procesado = v_->release_left(i,j);   break;
////		case FL_MIDDLE_MOUSE: procesado = v_->release_middle(i,j); break;
////		case FL_RIGHT_MOUSE:  procesado = v_->release_right(i,j);  break;
////	    }
////	}
////    }
//
//    if(procesado) return 1;
//
//    cout << "." << flush;
//    return Fl_Input_Choice::handle(event);
//
//}



}// namespace gui
