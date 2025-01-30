CC =c++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98
CFILES = oop.cpp exercice.cpp  person.cpp  student.cpp 

OBJS = $(CFILES:.cpp=.o)
NAME = a_cpp_go

all : $(NAME)
$(NAME):$(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
fclean: clean
	@rm -rf $(NAME)

re: fclean all