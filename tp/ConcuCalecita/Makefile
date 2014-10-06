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
fuentes_admin = $(wildcard administrador/*.$(extension))
fuentes_vendedor = $(wildcard vendedor/*.$(extension))
fuentes_caja = $(wildcard caja/*.$(extension))
fuentes_calecita = $(wildcard calecita/*.$(extension))
fuentes_common = $(wildcard common/*.$(extension))
fuentes_common += $(wildcard common/fifos/*.$(extension))
fuentes_common += $(wildcard common/memeCompartida/*.$(extension))
fuentes_common += $(wildcard common/signals/*.$(extension))
fuentes_common += $(wildcard common/logger/*.$(extension))


# REGLAS
#########

.PHONY: all clean

all: client admin vendedor caja calecita

o_common_files = $(patsubst %.$(extension),%.o,$(fuentes_common))
o_client_files = $(o_common_files) $(patsubst %.$(extension),%.o,$(fuentes_client)) 
o_admin_files = $(o_common_files) $(patsubst %.$(extension),%.o,$(fuentes_admin))
o_vendedor_files = $(o_common_files) $(patsubst %.$(extension),%.o,$(fuentes_vendedor))
o_caja_files = $(o_common_files) $(patsubst %.$(extension),%.o,$(fuentes_caja)) 
o_calecita_files =  $(o_common_files) $(patsubst %.$(extension),%.o,$(fuentes_calecita))

test: 
	./vendedor.exe&
	./caja.exe 0 &
	./calecita.exe&
	./client.exe 999 0 &	
	./client.exe 999 0 & 	
	./client.exe 999 0 & 	
	./client.exe 999 1 & 	
	./client.exe 9 0 &  
	./client.exe 9 1 & 	

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

admin: $(o_admin_files)
	@if [ -z "$(o_admin_files)" ]; \
	then \
		echo "No hay archivos de entrada para el administrador de la calecita (archivos admin*.$(extension))."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(o_admin_files) $(LOADLIBES) $(LDLIBS) -o admin.exe $(LDADD)

vendedor: $(o_vendedor_files)
	@if [ -z "$(o_vendedor_files)" ]; \
	then \
		echo "No hay archivos de entrada para el vendedor de boletos (archivos vendedor*.$(extension))."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(o_vendedor_files) $(LOADLIBES) $(LDLIBS) -o vendedor.exe $(LDADD)

caja: $(o_caja_files)
	@if [ -z "$(o_caja_files)" ]; \
	then \
		echo "No hay archivos de entrada para el vendedor de boletos (archivos vendedor*.$(extension))."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(o_caja_files) $(LOADLIBES) $(LDLIBS) -o caja.exe $(LDADD)

calecita: $(o_calecita_files)
	@if [ -z "$(o_calecita_files)" ]; \
	then \
		echo "No hay archivos de entrada para la calecita (archivos calecita*.$(extension))."; \
		false; \
	fi >&2
	$(LD) $(LDFLAGS) $(o_calecita_files) $(LOADLIBES) $(LDLIBS) -o calecita.exe $(LDADD)


clean:
	@$(RM) -fv *.o *~ caja/*.o common/fifos/*.o common/memCompartida/*.o common/signals/*.o calecita/*.o administrador/*.o cliente/*.o vendedor/*.o logs/* client.exe admin.exe vendedor.exe calecita.exe caja.exe















