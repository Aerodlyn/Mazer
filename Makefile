SOURCES := $(wildcard Sources/*.c)
FORTRAN := $(wildcard Sources/*.f)
MODULES := $(wildcard *.mod)
OBJECTS := $(SOURCES:.c=.o) $(FORTRAN:.f=.o)

EXEC := Mazer
CC := gcc

CFLAGS := -std=c11 -fms-extensions -Wall -IHeaders/
UNAME := $(shell uname)

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
# ALIBS := $(shell ls /usr/local/lib/pkgconfig/ | grep -E $(APACKS) | awk -F '.pc' '{print $$1}')

ifeq ($(UNAME), Darwin)
	AFLAGS := -lallegro -lallegro_primitives -lallegro_main
endif

ifeq ($(UNAME), Linux)
	AFLAGS := `pkg-config --cflags --libs $(ALIBS)`
endif

all : $(OBJECTS)
	$(CC) -o $(EXEC) -lgfortran $(OBJECTS) $(CFLAGS) $(AFLAGS)

%.o : %.c
	$(CC) -c $(CFLAGS) $(AFLAGS) -o $@ $<
	
%.o : %.f
	gfortran -ffree-form -c $< -o $@

clean:
	rm $(OBJECTS)
	rm $(MODULES)
	rm Mazer
