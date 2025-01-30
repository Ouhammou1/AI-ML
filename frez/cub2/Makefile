SRCM= ./get_next_line_1/get_next_line.c \
		./get_next_line_1/get_next_line_utils.c \
		ft_main.c \
		ft_error.c \
		ft_free.c \
		ft_validate_content.c \
		ft_validate_utils.c \
		ft_config.c \
		ft_map.c \
		ft_rgb_cnfg.c \
		game.c \
		RayCaster/draw_map.c   RayCaster/start_game.c   RayCaster/ft_func_maths.c RayCaster/move_plyer.c \
		RayCaster/ft_intersection.c\

OBJ= ${SRCM:.c=.o}

CFLAGS = -Wall -Wextra -Werror  -fsanitize=address -g
CC = cc

MLXLIB= ./MLX42/build/libmlx42.a
# INCLUDES= ${MLXLIB} -Iinclude -ldl -lglfw -pthread -lm  

INCLUDES = ./MLX42/build/libmlx42.a -framework Cocoa -framework OpenGL -framework IOKit

LIBFT= ./libft_1/libft.a

DIR_LIB = ./libft_1

NAME= cub3D

all: ${LIBFT} ${NAME}

${LIBFT} : 
	make -C ${DIR_LIB}

${NAME}: ${OBJ} cub.h 
	${CC} ${CFLAGS} ${INCLUDES}  ${OBJ} ${LIBFT} -Iinclude -lglfw -L "/Users/bouhammo/goinfre/homebrew/Cellar/glfw/3.4/lib" -o ${NAME}

%.o: %.c cub.h
	${CC} ${CFLAGS} -c $< -o $@

clean: 
	rm -rf ${OBJ}
	make fclean -C ${DIR_LIB}

fclean: clean
	rm -rf ${NAME}

re: fclean all

PHYNO:
