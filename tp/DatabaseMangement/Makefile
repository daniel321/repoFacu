# Makefile de ejemplo para programa cliente-servidor en C/C++
# 
# Creado: vie abr 27 00:37:46 ART 2007
#
# Copyleft 2007 - Leandro Lucarella, Bajo licencia GPL [http://www.gnu.org/]
#

# CONFIGURACION
################

# Extensión de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp

# Si usa funciones de math.h, descomentá (quitale el '#' a) la siguiente línea.
#math = si

# Si usa pthreads, descomentá (quitale el '#' a) la siguiente línea.
pthreads = si

# Si usa gthreads, descomentá (quitale el '#' a) la siguiente línea.
#gthreads = si

# Si es un programa GTK+, descomentá (quitale el '#' a) la siguiente línea.
#gtk = si

# Si es un programa gtkmm, descomentá (quitale el '#' a) la siguiente línea.
#gtkmm = si

# Descomentar si se quiere ver como se invoca al compilador
#verbose = si


# CONFIGURACION "AVANZADA"
###########################

# Opciones para el compilador C/C++ en modo ansi.
CFLAGS = #-Wall -Werror -pedantic -pedantic-errors

# Para que explote lo mas posible
#CFLAGS += -O3 -DNDEBUG

# Para valgrind o debug
CFLAGS += -ggdb -DDEBUG -fno-inline

# Opciones del enlazador.
LDFLAGS =

# Estandar de C a usar
CSTD = c99

# Estandar de C++ a usar
CXXSTD = c++98

# Si se quiere compilar estaticamente, descomentar la siguiente linea
#static = si


# VARIABLES CALCULADAS A PARTIR DE LA CONFIGURACION
####################################################

ifdef static
LDFLAGS += -static
endif

# Pongo flags de C para C++ también
CXXFLAGS += $(CFLAGS)

# Uso enlazador de c++ si es código no C.
ifeq ($(extension), c)
CFLAGS += -std=$(CSTD)
LD = $(CC)
else
CXXFLAGS += -std=$(CXXSTD)
LD = $(CXX)
endif

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
RM := $(RM) -v
else
CC =  @echo "  CC  $@"; $(occ)
CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)
endif

# Si no especifica archivos, tomo todos.
fuentes_client = $(wildcard cliente/*.$(extension))
fuentes_server = $(wildcard servidor/*.$(extension))
fuentes_common = $(wildcard common/*.$(extension))
fuentes_common += $(wildcard common/exception/*.$(extension))
fuentes_common += $(wildcard common/signals/*.$(extension))

# REGLAS
#########

.PHONY: all clean

all: client server

o_common_files = $(patsubst %.$(extension),%.o,$(fuentes_common))
o_client_files = $(o_common_files) $(patsubst %.$(extension),%.o,$(fuentes_client)) 
o_server_files = $(o_common_files) $(patsubst %.$(extension),%.o,$(fuentes_server))

%.deps: %.$(extension)
	@set -e; rm -f $@; \
		$(old) -MM -MG -MP $(CXXFLAGS) $(CFLAGS) $< -MF $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

-include $(o_files:.o=.deps)

client: $(o_client_files)
	@if [ -z "$(o_client_files)" ]; \
	then \
		echo "No hay archivos de entrada para el cliente (archivos client*.$(extension))."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(o_client_files) $(LOADLIBES) $(LDLIBS) -o client.exe $(LDADD)

server: $(o_server_files)
	@if [ -z "$(o_server_files)" ]; \
	then \
		echo "No hay archivos de entrada para el vendedor de boletos (archivos vendedor*.$(extension))."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(o_server_files) $(LOADLIBES) $(LDLIBS) -o server.exe $(LDADD)

clean:
	@$(RM) -fv *.o *~ common/*.o common/*/*.o cliente/*.o servidor/*.o client.exe server.exe















