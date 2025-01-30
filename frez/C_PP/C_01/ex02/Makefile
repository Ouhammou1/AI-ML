CC =c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g 
CFILES = main.cpp

OBJS = $(CFILES:.cpp=.o)
NAME = HI_THIS_IS_BRAIN

all : $(NAME) 
$(NAME):$(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
fclean: clean
	@rm -rf $(NAME)

re: fclean all