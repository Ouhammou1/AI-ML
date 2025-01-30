CC =c++
CFLAGS= -Wall -Wextra -Werror -std=c++98 
CFILES= megaphone.cpp
 
OBJS= $(CFILES:.cpp=.o)
NAME = megaphone


all: $(NAME)
$(NAME):$(OBJS) 
	$(CC) $(FLAGS)   $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re: fclean all 