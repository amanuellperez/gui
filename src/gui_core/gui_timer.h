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


#pragma once

#ifndef __GUI_TIMER_H__
#define __GUI_TIMER_H__


#include <alp_time.h>

namespace gui{
/*!
 *  \brief Timer que uso para controlar el tiempo que tarda la
 *  \brief ejecución de un algoritmo. Está vinculado a una Linea
 *  \brief que es donde se muestra al usuario el tiempo que tarda la ejecución.
 *
 *   - EJEMPLO:
 *	    Linea info;
 *
 *	    Opción 1:
 *	    --------
 *	    Timer timer{info};
 *	    timer.start("Marcando bordes"); // msg que se muestra al usuario
 *	    ... ejecutamos el algoritmo
 *	    timer.stop();	// muestra en info el tiempo de ejecución
 *
 *	    Opción 2 (más corta)
 *	    --------------------
 *	    Timer timer{info, "Marcando bordes"};   // llamamos a start
 *	    ... ejecutamos el algoritmo
 *	    timer.stop();	// muestra en info el tiempo de ejecución
 *
 *
 */
class Timer{
public:
    Timer(Linea& info0):info(info0){}
    Timer(Linea& info0, const std::string& s):info(info0)
    {start(s);}

    void start(const std::string& s)
    {
	msg = s;
	flush(msg + " ...");
	crono.start();
    }

    void stop()
    {
	crono.stop();
	flush(msg + " ... OK; t = " 
		+ alp::to<std::string>(crono.milisegundos()) + " ms");
    }

private:
    Linea& info;
    alp::Cronometro crono;
    std::string msg;

    void flush(const std::string& s)
    {
	info.texto(s);
	info.flush();
    }
};


}// namespace

#endif

