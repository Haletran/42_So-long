# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bapasqui <bapasqui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 11:04:36 by codespace         #+#    #+#              #
#    Updated: 2024/01/29 16:07:32 by bapasqui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile vars                                                                  
NAME    := so_long
CFLAGS  := -Wextra -Wall -Werror -g
SRCS    := so_long.c \
           src/utils.c \
           src/parse.c \
		   src/validity.c \
		   src/render.c \
		   src/mov.c \
           src/checker.c
OBJS_DIR := obj
OBJS    := $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
LIBS    := MacroLibX/libmlx.so -lSDL2

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@make -C MacroLibX
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) libft/libft.a -o $(NAME)

gdb: $(NAME)
	gdb --tui ./so_long

norm:
	@norminette -R CheckForbiddenSourceHeader ft_printf/ get_next_line/ include/ libft so_long.c src/

gt:	
	@if [ ! -d "MacroLibX" ]; then git clone https://github.com/seekrs/MacroLibX.git && make -C MacroLibX; fi

valgrind: $(NAME)
	valgrind --leak-check=full --suppressions=MacroLibX/valgrind.supp ./so_long maps/valid_maps/map_4x5.ber
clean:
	@make -C libft clean
	@make -C MacroLibX clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make -C libft fclean
	@make -C MacroLibX fclean
	@rm -rf $(NAME)

re: clean all

.PHONY: all clean fclean re folder gt valgrind norm



