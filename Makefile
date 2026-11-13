CC = gcc

CFLAGS = -Wall -Wextra -std=c99 -Isrc

LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRC = \
	src/main.c \
	src/board.c \
	src/game.c \
	src/draw.c \
	src/input.c

OBJ = $(SRC:.c=.o)

EXEC = jogo

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)