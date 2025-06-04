# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 13:42:12 by apregitz          #+#    #+#              #
#    Updated: 2025/06/04 09:38:26 by apregitz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=		minishell

CC :=		cc
CFLAGS :=	-Wall -Wextra -Werror -g
LDFLAGS :=	-lreadline
LIBFT :=	include/libft/libft.a

INC :=		-Iinclude -Iinclude/libft
SRCD :=		src
OBJD :=		obj

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
			$(SRCD)/execution/execution.c \
			$(SRCD)/execution/exec_cmd.c \
			$(SRCD)/execution/pipes.c \
			$(SRCD)/execution/exec_pipes.c \
			$(SRCD)/execution/pipes_utils.c \
			$(SRCD)/execution/execute_commands.c \
			$(SRCD)/execution/get_path.c \
			$(SRCD)/execution/init.c \
			$(SRCD)/execution/redirections.c \
			$(SRCD)/execution/redirection_cases.c \
			$(SRCD)/execution/setup_child.c \
			$(SRCD)/execution/fd_collector.c \
			$(SRCD)/execution/here_doc.c \
			$(SRCD)/execution/error.c \
			$(SRCD)/debug.c

OBJS :=		$(SRCS:$(SRCD)/%.c=$(OBJD)/%.o)

# Create object subdirectories
OBJ_DIRS :=	$(OBJD) \
			$(OBJD)/lexical_analysis \
			$(OBJD)/expansion \
			$(OBJD)/parser \
			$(OBJD)/utilities \
			$(OBJD)/env_list \
			$(OBJD)/garbage_collector \
			$(OBJD)/builtins \
			$(OBJD)/execution

all: $(NAME)

$(NAME): $(OBJ_DIRS) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C include/libft

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(OBJD)/%.o: $(SRCD)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

debug:
	@$(MAKE) fclean all CFLAGS="$(CFLAGS) -D DEBUG=1"

clean:
	$(MAKE) -C include/libft clean
	rm -rf $(OBJD)

fclean: clean
	$(MAKE) -C include/libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re