# -------------------------
# Estructura de directorios
# -------------------------
GUI_ROOT=${MY_HOME}/prj/git/gui	; export GUI_ROOT
GUI_SRC=${GUI_ROOT}/src		; export GUI_SRC
GUI_MK=${GUI_ROOT}/mk		; export GUI_MK

# ---------------------
# Reglas de compilación
# ---------------------
# Reglas de compilación de cada entorno
GUI_CORE_COMPRULES=${GUI_MK}/gui_core.mk	; export GUI_CORE_COMPRULES
GUI_VISOR_COMPRULES=${GUI_MK}/gui_visor.mk	; export GUI_VISOR_COMPRULES
GUI_VENT_COMPRULES=${GUI_MK}/gui_vent.mk	; export GUI_VENT_COMPRULES



# ------------------------------------------------------
# CPATH = es donde busca g++ los archivos .h (opción -I)
# Movido a cpp/entorno.sh
# ------------------------------------------------------
#CPATH=${CPATH}:${MY_HOME}/include
#export CPATH

# --------------------------------------------------------
# LIBRARY_PATH = donde busca g++ las librerias (opción -L)
# Movido a cpp/entorno.sh
# --------------------------------------------------------
#LIBRARY_PATH=${MY_HOME}/lib
#export LIBRARY_PATH 


# Alias
alias gui='cd ${GUI_SRC}'

cd ${GUI_SRC}
