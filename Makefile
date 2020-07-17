NAME2 = checker

NAME = push_swap

SRCS = 	src/parsing_1.c \
		src/parsing_2.c \
		src/utils_1.c \
		src/utils_2.c \
		src/utils_3.c \
		src/operations_1.c \
		src/operations_2.c \
		src/operations_3.c \
		src/operations_4.c \
		src/stack_1.c \
		src/stack_2.c \
		src/pre_sort_1.c \
		src/pre_sort_2.c \
		src/pre_sort_3.c \
		src/quicksort_1.c \
		src/quicksort_2.c \
		src/quicksort_3.c

SRCS1 =	src/push_swap.c $(SRCS)

SRCS2 =	src/checker.c $(SRCS)

OBJS1 = $(SRCS1:.c=.o)

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

$(NAME) : $(OBJS1)
	@make -C $(LIBFT_DIR)
	gcc $(FLAGS) -o $(NAME) $(OBJS1) $(LIBDIRS) $(LIBS)
	@echo "Compilation finished."

$(NAME2) : $(OBJS2)
	@make -C $(LIBFT_DIR)
	gcc $(FLAGS) -o $(NAME2) $(OBJS2) $(LIBDIRS) $(LIBS)
	@echo "Compilation finished."

clean :
	rm -f $(OBJS1) $(OBJS2)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -f $(NAME) $(NAME2)
	make fclean -C $(LIBFT_DIR)

re : fclean all
