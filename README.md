# gui

Capa sobre FLTK en C++.

¡¡¡NO PIERDAS TIEMPO CON ESTE PAQUETE: Es inestable y de aprendizaje!!!
Lo mantengo aquí como copia de seguridad, nada más.

Se trata de un proyecto de aprendizaje (y que ya de paso uso si tengo que
hacer algún programa con ventanitas). 

Uno de los problemas que tiene C++ es la falta de bibliotecas estándar de
cosas básicas, como por ejemplo, un paquete para hacer aplicaciones de
windows. Si bien es verdad que hay un montón de opciones (Qt y demás) eso
mismo genera un problema: hay demasiada opción. Si solo estás interesado en
hacer algún programa de vez en cuando muy determinado de ventanas no interesa
perder tiempo teniendo que aprender qué paquete es más práctico, más sencillo,
... 

¿Por qué me quedé con FLTK? Es un paquete pequeño (instalé Qt y ocupó un
montón).

Sin embargo al empezar a usarlo no me gustó el planteamiento que tienen:
una ventana y un widget están dentro de la misma jerarquía pero para mi una
ventana y un widget son cosas totalmente diferentes, no se pueden mezclar. Así
que decidí ir escribiendo, a la vez que aprendía a manejar FLTK, una capa
sobre FLTK.

Claramente esta capa no puede estar bien diseñada por varios motivos:

1. No sabía manejar FLTK, y de hecho ahora sigo sin saberlo manejar. No se
   puede pretender reescribir un sistema de ventanas basándote en un paquete
   que no dominas.

2. Nunca antes había programado aplicaciones de windows. Todos mis programas
   siempre han sido para ser ejecutados en servidor y nunca en cliente.

Con todo algunas de las ideas que tiene el paquete `gui` creo que están
bastante bien:

* Un control que se use para que el usuario de la aplicación escriba, por
  ejemplo, un `int` el programador lo puede usar como si fuera un `int` vulgar
  y corriente sin tener que preocuparse de estar manejando un control.

* El maquetador ha quedado bastante bien (aunque se puede mejorar, hay un
  intento de mejorarlo pero no funcionaba bien siendo necesario depurar el
  código).




