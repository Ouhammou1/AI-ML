CC =c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g 
CFILES = main.cpp  Zombie.cpp  newZombie.cpp   randomChump.cpp

OBJS = $(CFILES:.cpp=.o)
NAME = BraiiiiiiinnnzzzZ

all : $(NAME) Zombie.hpp
$(NAME):$(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
fclean: clean
	@rm -rf $(NAME)

re: fclean all