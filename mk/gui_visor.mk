include $(CPP_ENVRULES)

# -----------
# DIRECTORIOS
# -----------
# Compilamos enlazando fltk TODO: comentar estos flags!
FLTK_CXXFLAGS=$(shell fltk-config --use-gl --use-images --cxxflags)
FLTK_LDFLAGS=$(shell fltk-config --use-gl --use-images --ldflags)


GUI_CXXFLAGS=-I$(CPP_INCLUDE)/alp \
			 -I$(CPP_INCLUDE)/img \
			 -I$(CPP_INCLUDE)/gui

GUI_LDFLAGS=-L$(INSTALL_LIB) -lgui_core -limg -lalp

# Variables genéricas de compilación del proyecto
PROJ_CXXFLAGS=$(GUI_CXXFLAGS) $(FLTK_CXXFLAGS) $(DEPURAR)
PROJ_LDFLAGS=$(GUI_LDFLAGS) $(FLTK_LDFLAGS)


include $(CPP_GENRULES)


