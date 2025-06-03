# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 13:42:12 by apregitz          #+#    #+#              #
#    Updated: 2025/06/03 07:19:19 by apregitz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		minishell

CC =		cc
CFLAGS =	-Wall -Wextra -Werror -g
LDFLAGS =	-fsanitize=address,undefined
LIBFT =		include/libft/libft.a

SRCD =		src
OBJD =		obj

INC =		-Iinclude

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
			$(SRCD)/env_list/env_ops.c \
			$(SRCD)/garbage_collector/garbage.c \
			$(SRCD)/debug.c \
			$(SRCD)/execution/error.c \
			$(SRCD)/execution/exec_cmd.c \
			$(SRCD)/execution/execution.c \
			$(SRCD)/execution/fd_collector.c \
			$(SRCD)/execution/get_path.c \
			$(SRCD)/execution/here_doc.c \
			$(SRCD)/execution/init.c \
			$(SRCD)/execution/redirection_cases.c \
			$(SRCD)/execution/redirections.c \
			$(SRCD)/execution/setup_child.c

OBJS :=		$(addprefix $(OBJD)/, $(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	make -C include/libft

$(NAME): $(OBJD) $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -lreadline -o $(NAME)

$(OBJD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INC) -c $< -o $@

$(OBJD):
	mkdir -p $(OBJD)

clean:
	make -C include/libft clean
	rm -rf $(OBJD)

fclean: clean
	make -C include/libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re