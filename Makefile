SOURCES := $(wildcard Sources/*.c)
FORTRAN := Sources/Mazer_Module.f95 Sources/Determine_Borders.f95 Sources/Generate_Tiles.f95 Sources/Generate_Rooms.f95 \
			Sources/Generate_Paths.f95
MODULES := $(wildcard *.mod Sources/*.mod)
OBJECTS := $(SOURCES:.c=.o) $(FORTRAN:.f95=.o)

EXEC := Mazer
CC := gcc-7

CFLAGS := -std=c11 -fms-extensions -Wall -g -IHeaders/
SDL_FLAGS := `sdl2-config --cflags --libs`

all : $(OBJECTS)
	$(CC) -lgfortran $(CFLAGS) $(SDL_FLAGS) -o $(EXEC) $(OBJECTS)

debug : CC += -DDEBUG
debug : all

%.o : %.c
	$(CC) -c $(CFLAGS) $(SDL_FLAGS) -o $@ $<
	
%.o : %.f95
	gfortran -ffree-form -c $< -o $@

clean:
	rm $(OBJECTS)
	rm $(MODULES)
	rm Mazer
