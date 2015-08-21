NAME = polysh

CC = gcc

SRC =	editline.c \
		main.c

OBJ = $(SRC=:.c=.o)

CFLAGS = -I../include

LDFLAGS = -L. -lpolysh 

all: $(NAME)

$(NAME): $(OBJ)
		   $(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm $(NAME)
