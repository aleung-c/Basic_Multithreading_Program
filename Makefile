NAME = thread_test

HEADER = thread_testing.h

SRC = main.c

OBJ = $(SRC:.c=.o)

CC = gcc -g -Wall -Werror -Wextra

all : $(NAME) thread_testing.h 

$(NAME) : $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -pthread -lm

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

main.o: thread_testing.h

.PHONY : all clean fclean re