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


#include "../gui_core/gui_fl.h"

#include <gui_base.h>
#include "gui_visor.h"

#include <iostream>
#include <algorithm>
#include <cstring>  // memset

#include <img.h>


using namespace std;
using namespace img;

namespace gui{
/***************************************************************************
 *				 FL_VISOR
 ***************************************************************************/
const int Fl_Visor::num_canales = 3;

//const img::Image Fl_Visor::img_por_defecto = img::imagen_negra(50,50);
const img::Image Fl_Visor::img_por_defecto = img::imagen_negra(1,1);

namespace impl
{
// Esta función la necesito porque FLTK quiere un puntero a imagen
// DUDA: ¿podría hacer un memcpy? Según Stroustrup hay veces que 
// el compilador añade cosas a las clases, así que no hay garantía de
// que un ColorRGB sean 3 caracteres R, G, B (además, son int!)
// PRECONDICIÓN: p es del mismo tamaño que img!!!
//
// Copia la imagen img0 en al array [p0, ancho * alto * 3].
// (es una función del tipo copia_dentro)
// En general el array p0 será más grande que la imagen img0, por ello
// la centra.
// Precondición: p0 = es un array de ancho * alto * 3 caracteres.
// Devuelve el rango en donde queda dibujada la imagen.
static img::Range2D img_to_char(  const img::Image& img0    
			, unsigned char* p0, Ind ancho, Ind alto)
{
    // borramos la imagen que pudiera haber
    std::memset(p0, 0, ancho * alto * 3);

    // escribimos la nueva imagen
    auto p = p0;

    Range2D rg;

    if (ancho > img0.cols()){
	rg.i0 = 0;
        rg.j0 = (ancho - img0.cols()) / 2;
    }

    if (alto > img0.rows()){
	rg.i0 = (alto - img0.rows()) / 2;
	rg.j0 = 0;
    }

    rg.ie = rg.i0 + std::min(img0.rows(), alto);
    rg.je = rg.j0 + std::min(img0.cols(), ancho);

    // copiamos: ¿no puedo hacer memcpy? Habría que garantizar que
    // Image solo tiene 3 datos: R,G,B y en este orden <-- dificil de
    // garantizar. Cuando la modifique no me acordaré. No hacer memcpy!!!
    // (salvo que sea muy estable Image, y que esta función se defina dentro
    // del interfaz de Image para saber que hay que revisarla)
    for(Ind i = 0; i != std::min(img0.rows(), alto); ++i)
    {
	for(Ind j = 0; j != std::min(img0.cols(), ancho); ++j)
	{
	    *p = img0(i,j).r; ++p;
	    *p = img0(i,j).g; ++p;
	    *p = img0(i,j).b; ++p;
	}

	p = p0 + 3*((i + rg.i0)*ancho + rg.j0);
    }

    return rg;
}

} // namespace impl


// Garantizamos que el visor quede en buen estado: por defecto, 
// lo inicializamos a la imagen por defecto.
// OJO: falta por inicializar visor_!!!
Fl_Visor::Fl_Visor(int x, int y, int a, int h)
    :Fl_Box{x, y, a, h}
    //, cristal_ {img_por_defecto.clone()}
    , cristal_ {img_por_defecto}
    , ancho{a}, alto{h}
    , visor_{nullptr}
{
    Fl::visual(FL_RGB); // prevents dithering on some systems

    // Dejamos bien construido el visor, enlazándolo con la imagen por
    // defecto.
    //enlaza_img0(img_por_defecto, img::extension(img_por_defecto));
    de(img_por_defecto);
}


Fl_Visor::~Fl_Visor()
{
    delete[] pimge_;
    delete rgb;	// es un Fl_Image, no lo destruye FLTK
}



void Fl_Visor::resize(int x, int y, int a, int h)
{
    ancho = a; alto = h;

    resize_ = true;

    Fl_Box::resize(x,y,a,h); // Obligatorio llamar al resize del padre @_@
}


void Fl_Visor::resize()
{
    if (subimg0_.empty()) return;

    // reservamos la memoria necesaria
    // TODO: mejoras:	
    //	1.- Si se va a hacer más pequeña la imagen no es necesario el delete.
    delete[] pimge_; delete rgb;
    pimge_ = new unsigned char[ancho*alto*num_canales];
    rgb  = new Fl_RGB_Image{pimge_, ancho, alto, num_canales};

    // la asociamos al Fl_Box
    image(rgb);

    resize_ = false;
//    redraw();
}



// Volcamos la imagen img0 al visor. Esta función es la que realmente
// hace el dibujo en pantalla de la imagen img0.
void Fl_Visor::vuelca_al_visor(const Image& img0)
{
    img::Image imge = escalador.escala(img0, ancho, alto);
    imgve_rango_ = impl::img_to_char(imge, pimge_, ancho, alto);

    // >>> TODO: no se por qué tengo que hacer un delete del rgb
    // Si no lo hago no redibuja la imagen cuando le pido actualizarla
    // (con el resize funciona, sin el resize no)
    delete rgb;
    rgb  = new Fl_RGB_Image{pimge_, ancho, alto, num_canales};
    image(rgb);
    // <<< FIN

    Fl_Box::draw();
}



// Función que llama FLTK cada vez que hay que redibujar el widget
void Fl_Visor::draw()
{
    if(resize_) resize();

    if(mostrar_original_)   
    {
	draw_original();
	mostrar_original_ = false;
    }
    else
	vuelca_al_visor(cristal_);
}




int Fl_Visor::handle(int event)
{
    auto procesado = false;

    if(event == FL_KEYDOWN)
	procesado = visor_->pulsa_tecla(Fl::event_text(), Fl::event_key());
    else if(event == FL_FOCUS)
	procesado = true;
    else{
	// Solo llamamos al manejador correspondiente con puntos que
	// pertenezcan al visor. Es posible que esta validación sobre, ya que
	// FLTK debería de llamar a handle solo sobre widgets que están sobre
	// el punto indicado. Pero así garantizo que funcione correctamente
	// OJO: recordar que una cosa es el visor y otra la imagen que
	// mostramos. La imagen que mostramos no ocupa todo el visor, luego se
	// va a llamar a push_left también cuando se pinche sobre el visor
	// pero fuera de la imagen!!!
	if (!pertenece(Fl::event_x(), Fl::event_y(), *this))
	    return false;

	// OJO: event_x/y devuelve la posición relativa a la ventana!!!
	// (i,j) = posición local escalada = posición relativa al visor
//	int i = Fl::event_y() - y();
//	int j = Fl::event_x() - x();
	auto p = Posicion::en_pix(Fl::event_x()-x(), Fl::event_y()-y());

	switch(event){
	    case FL_PUSH:
		switch(Fl::event_button()){
		    case FL_LEFT_MOUSE:   
			procesado = visor_->push_left(p);   
			boton_pulsado_ = Boton_raton::izdo;
			break;

		    case FL_MIDDLE_MOUSE: 
			procesado = visor_->push_middle(p); 
			boton_pulsado_ = Boton_raton::medio;
			break;

		    case FL_RIGHT_MOUSE:  
			procesado = visor_->push_right(p);  
			boton_pulsado_ = Boton_raton::dcho;
			break;
		}
		break;

	    case FL_DRAG:
		//switch(Fl::event_state()){
		switch(boton_pulsado_){
		    case Boton_raton::izdo: procesado = visor_->drag_left(p); break;
		    case Boton_raton::medio: procesado = visor_->drag_middle(p); break;
		    case Boton_raton::dcho: procesado = visor_->drag_right(p); break;
		    case Boton_raton::ninguno: break;	// para que no de warning
							// no hago nada aposta
		}
		break;

	    case FL_RELEASE:
		boton_pulsado_ = Boton_raton::ninguno;

		switch(Fl::event_button()){
		    case FL_LEFT_MOUSE:   procesado = visor_->release_left(p);   break;
		    case FL_MIDDLE_MOUSE: procesado = visor_->release_middle(p); break;
		    case FL_RIGHT_MOUSE:  procesado = visor_->release_right(p);  break;
		}
		break;

	    case FL_MOUSEWHEEL:
		// Desconozco para qué sirve el dx. Lo paso por si hay
		// ratones que puedan usarlo.
		procesado = visor_->
		    mouse_wheel(Coordenada::en_pix(Fl::event_dx()), 
				Coordenada::en_pix(Fl::event_dy()));
		break;

	}
    }

    if(!procesado)
	return Fl_Box::handle(event);

    // si llega hasta aquí es que está procesado
    return 1;
}



// asociamos el visor con la subimagen pasada
void Fl_Visor::de(const img::Image& img0
		    , const img::Range2D& rg)
{
    subimg0_.de(img0, rg);
    resize_ = true;
    crea_cristal();
}



// indicamos al visor que queremos mostrar la región asociada a r
void Fl_Visor::extension(const img::Range2D& rg, bool redibujar)
{
    subimg0_.extension(rg);

    if (visible()){ // si está oculto, no lo mostramos
	Fl_Box::show();
	refresh(redibujar);
    }

    // aquí no estamos cambiando el tamaño de la ventana, sino
    // cargando una parte diferente de la imagen!!!
//  resize_ = true;
}


void Fl_Visor::muestra_img(bool mostrar) 
{	
    if(mostrar == mostrar_img_) return;
    mostrar_img_ = mostrar;

    refresh();  // la va a redibujar (mejor no????)
}


// funciones de conversión
// OJO: (i,j) = (ie, je) = es una posición local escalada
// Convierte: (ie, je) --> (I, J)
img::Range2D Fl_Visor::local_escalada_to_global(const img::Range2D& r) const
{
    return local_to_global(local_escalada_to_local(r));
}


// Convierte: (ie, je) --> (I, J)
img::Range2D Fl_Visor::local_to_global(img::Range2D r) const
{
//    r.p0(r.p0() + subimg0_.P0());
//    r.p1(r.p1() + subimg0_.P0());

    r.upper_left_corner(r.upper_left_corner() + subimg0_.P0());
    r.bottom_right_corner(r.bottom_right_corner() + subimg0_.P0());

    return r;
}




//std::ostream& operator<<(std::ostream& out, const Fl_Visor& v)
//{
//    out << "Datos región sin escalar:\n";
//    out << "(p0, p1) = (" << v.subimg0_.P0() << ", " << v.subimg0_.P1() << ")\n";
//    out << "(ancho, alto) = (" << v.ancho_region() << ", " << v.alto_region() << ")\n";
//
//    out << "Datos región escalada:\n";
//    out << "(ancho, alto) = (" << v.ancho << ", " << v.alto << ")\n";
//    out << "razon_semejanza = " << v.razon_semejanza() << '\n';
//
//    return out;
//}




}// namespace gui
