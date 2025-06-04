# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 13:42:12 by apregitz          #+#    #+#              #
#    Updated: 2025/06/04 05:08:23 by apregitz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=		minishell

CC :=		cc
CFLAGS :=	-Wall -Wextra -Werror -g
LDFLAGS :=	-fsanitize=address,undefined
LIBFT :=		include/libft/libft.a

INC :=		-Iinclude
SRCD :=		src
OBJD := 		obj

SRCS :=		$(SRCD)/main.c \
			$(SRCD)/lexical_analysis/_lexical_analysis.c \
			$(SRCD)/lexical_analysis/token_linked_list.c \
			$(SRCD)/lexical_analysis/parsing_utils1.c \
			$(SRCD)/lexical_analysis/token_types.c \
			$(SRCD)/lexical_analysis/token_length.c \
			$(SRCD)/expansion/_expansion.c \
			$(SRCD)/expansion/quote_state.c \
			$(SRCD)/expansion/env_variable.c \
			$(SRCD)/expansion/dollar_vars.c \
			$(SRCD)/expansion/dollar_question.c \
			$(SRCD)/expansion/remove_quotes.c \
			$(SRCD)/parser/_parser.c \
			$(SRCD)/parser/commands.c \
			$(SRCD)/parser/redirections.c \
			$(SRCD)/parser/cmd_linked_list.c \
			$(SRCD)/parser/file_linked_list.c \
			$(SRCD)/utilities/error.c \
			$(SRCD)/env_list/init_env.c \
			$(SRCD)/env_list/env_to_array.c \
			$(SRCD)/env_list/env_ops.c \
			$(SRCD)/garbage_collector/garbage.c \
			$(SRCD)/builtins/echo.c \
			$(SRCD)/builtins/pwd.c \
			$(SRCD)/debug.c \

OBJS :=		$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: mkdir_obj $(NAME)

mkdir_obj:
	@mkdir -p $(OBJ_DIRS)

$(LIBFT):
	$(MAKE) -C src/libft

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	make -C src/libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C src/libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mkdir_obj