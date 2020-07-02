NAME2 = checker

NAME = push_swap

SRCS =	src/push_swap.c \
		src/parsing_1.c \
		src/parsing_2.c \
		src/utils.c \
		src/operations_1.c \
		src/operations_2.c

SRCS2 =	src/checker.c \
		src/parsing_1.c \
		src/parsing_2.c \
		src/utils.c \
		src/operations_1.c \
		src/operations_2.c

OBJS = $(SRCS:.c=.o)

OBJS2 = $(SRCS2:.c=.o)

FLAGS = -Wall -Wextra -Werror

NOFLAGS = 

LIBFT_DIR = lib/libft

COMPILER = clang

CFLAGS = $(FLAGS)

LIBS = -lft
INCLUDES = -I include/ -I $(LIBFT_DIR)/
LIBDIRS = -L./$(LIBFT_DIR)/

all : $(NAME)

%.o : %.c
	gcc $(FLAGS) -c -o $@ $< $(INCLUDES)

$(NAME) : $(OBJS)
	@make -C $(LIBFT_DIR)
	gcc $(FLAGS) -o $(NAME) $(OBJS) $(LIBDIRS) $(LIBS)
	@echo "Compilation finished."

$(NAME2) : $(OBJS2)
	@make -C $(LIBFT_DIR)
	gcc $(FLAGS) -o $(NAME2) $(OBJS2) $(LIBDIRS) $(LIBS)
	@echo "Compilation finished."

clean :
	rm -f $(OBJS) $(OBJS2)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -f $(NAME) $(NAME2)
	make fclean -C $(LIBFT_DIR)

re : fclean all
