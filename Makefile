
SRC = main.c
PROG = agario 
LDFLAGS  = `sdl2-config --libs` -lSDL2_image -lm  

all:
	gcc -Wall -Wextra $(SRC) -o $(PROG) $(LDFLAGS)
