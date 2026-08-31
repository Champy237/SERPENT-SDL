CC = gcc
CFLAGS = -Wall -g
LIBS = -lSDL2

SRCS = main_champy.c fonction_champy.c
OBJS = $(SRCS:.c=.o)

EXEC = serpent

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LIBS)

%.o: %.c fonction_champy.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

fclean: clean

.PHONY: all clean fclean
