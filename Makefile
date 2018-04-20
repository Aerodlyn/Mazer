SOURCES := $(wildcard Sources/*.c)
FORTRAN := Sources/Mazer_Module.f95 Sources/Generate_Rooms.f95 Sources/Generate_Paths.f95
MODULES := $(wildcard *.mod Sources/*.mod)
OBJECTS := $(SOURCES:.c=.o) $(FORTRAN:.f95=.o)

EXEC := Mazer
CC   := gcc-7

CFLAGS    := -std=c11 -fms-extensions -Wall -g -IHeaders/
SDL_FLAGS := `sdl2-config --cflags --libs`

# The APACKS variable represents the name of the required Allegro packages (without the version id), 
# with a '|' separating each as to be used with grep -E.
APACKS := 'allegro-|allegro_primitives'

# The ALIBS variable finds the Allegro packages that match the names given in the APACKS variable. 
# The reason for this is because on two of my development systems the files have slightly different 
# endings (5.pc vs 5.0.pc) so instead of renaming each I attempted to come up with a "portable"
# solution.
#
# The first command assumes that PKG_CONFIG_PATH is set to only one path. If your PKG_CONFIG_PATH
# contains more than one path and the one where Allegro's .pc files are located isn't the first
# one in the list, you can comment out the below command and uncomment the one below it. Set
# the path to where Allegro's .pc files are located.
ALIBS := $(shell path=`echo $$PKG_CONFIG_PATH | awk -F ':' '{print $$2}'`; test "$$path" == '' && path=$$PKG_CONFIG_PATH; ls $$path | grep -E $(APACKS) | awk -F '.pc' '{print $$1}')
# ALIBS := $(shell ls /usr/lib/pkgconfig/ | grep -E $(APACKS) | awk -F '.pc' '{print $$1}')

all : $(OBJECTS)
	$(CC) -lgfortran $(CFLAGS) $(SDL_FLAGS) -o $(EXEC) $(OBJECTS)

%.o : %.c
	$(CC) -c $(CFLAGS) $(SDL_FLAGS) -o $@ $<
	
%.o : %.f95
	gfortran -ffree-form -c $< -o $@

clean:
	rm $(OBJECTS)
	rm $(MODULES)
	rm Mazer
