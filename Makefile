SOURCES := $(wildcard Sources/*.c)
OBJECTS := $(SOURCES:.c=.o)

EXEC := Mazer
CC := gcc

CFLAGS := -std=c11 -Wall -IHeaders/
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	AFLAGS := -lallegro -lallegro_main
endif

ifeq ($(UNAME), Linux)
	AFLAGS := `pkg-config --cflags --libs allegro-5.0`
endif

all : $(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS) $(CFLAGS) $(AFLAGS)

%.o : %.c
	$(CC) -c $(CFLAGS) $(AFLAGS) -o $@ $<

clean:
	rm $(OBJECTS)
