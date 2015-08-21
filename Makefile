NAME = polysh

SRC_DIR = src

CC = gcc

SRC =	$(SRC_DIR)/editline.c \
		$(SRC_DIR)/libpolysh.a \
		$(SRC_DIR)/main.c

OBJ = $(SRC=:.c=.o)

LDFLAGS = -Iinclude

all: $(NAME)

$(NAME): $(OBJ)
		   $(CC) $(OBJ) $(SRC_DIR)/libpolysh.a $(LDFLAGS) -o $(NAME)

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm $(NAME)