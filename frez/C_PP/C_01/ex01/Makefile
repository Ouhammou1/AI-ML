CC =c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g 
CFILES = Zombie.cpp zombieHorde.cpp main.cpp

OBJS = $(CFILES:.cpp=.o)
NAME = Moar_brainz

all : $(NAME) 
$(NAME):$(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
fclean: clean
	@rm -rf $(NAME)

re: fclean all