NAME = cub3d
SOURS = 						./map_parsing/map_parse.c								\
								./map_parsing/ft_split.c								\
								./map_parsing/ft_strtrim.c								\
								./map_parsing/ft_sub.c									\
								./map_parsing/get_next_line_bonus.c						\
								./map_parsing/get_next_line_utils_bonus.c				\
								./map_parsing/map_input_map.c							\
								./map_parsing/map_input_rgb.c							\
								./map_parsing/map_input_texture.c						\
								./map_parsing/map_make_map.c							\
								./map_parsing/map_vaild_check.c							\
								./ray_casting/ray_cast.c								\
								./ray_casting/ray_init.c								\
								./ray_casting/ray_input_win.c							\
								./ray_casting/math_utils.c							\
								./main.c
	
MAN_OBJS = ${SOURS:.c=.o}
HEADER_FILES =	./map_parsing/map_parse.h ./ray_casting/ray_cast.h ./main.h
CC = cc
CFLAG = -Wall -Wextra -Werror
MLX_DIR = ./mlx
MLX_SRC = ${MLX_DIR}/libmlx.a

all : ${NAME}

${NAME} : ${MAN_OBJS} ${MLX_SRC}
	${CC} ${CFLAG} -Lmlx -lmlx -lm -framework OpenGL -framework AppKit -o $(NAME) $(MAN_OBJS)

%.o : %.c ${HEADER_FILES}
	${CC} ${CFLAG} -Imlx -c $< -o $@

${MLX_SRC} :
	${MAKE} -C ${MLX_DIR} -s

bonus :
	make all FLAG=1

clean :
	rm -f ${MAN_OBJS}
	${MAKE} -C ${MLX_DIR} clean

fclean :
	make clean
	rm -f ${NAME}

re : 
	make fclean
	make all

.PHONY : all clean fclean re bonus