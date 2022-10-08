
SRC = main.c init.c input.c
PROG = agario 
LDFLAGS  = `sdl2-config --libs` -lSDL2_image -lm  
INCLUDE_FLAGS = -I.

all:
	gcc -Wall -Wextra $(SRC) -o $(PROG) $(LDFLAGS) $(INCLUDE_FLAGS)
