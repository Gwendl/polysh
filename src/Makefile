NAME = polysh

all: $(NAME)

$(NAME): $(OBJ)
		   gcc -o polysh -I../include -L. main.c editline.c libpolysh.a

re: fclean all

clean:
	rm -f *.o

fclean: clean
	rm $(NAME)
