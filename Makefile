NAME = polysh

SRC_DIR = src

CC = gcc

SRC =	$(SRC_DIR)/editline.c \
		$(SRC_DIR)/main.c

OBJ = $(SRC=:.c=.o)

LDFLAGS = -Iinclude -Lsrc

all: $(NAME)

$(NAME): $(OBJ)
		   $(CC) $(OBJ) -lpolysh $(LDFLAGS) -o $(NAME)

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm $(NAME)
