# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 13:42:12 by apregitz          #+#    #+#              #
#    Updated: 2025/06/02 12:44:46 by apregitz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=			minishell

CC :=			cc
CFLAGS :=		-Wall -Wextra -Werror -g
LDFLAGS :=		-fsanitize=address,undefined
LIBFT :=		src/libft/libft.a

SRC_DIR :=		src
OBJ_DIR :=		obj

VPATH :=		$(SRC_DIR):\
				$(SRC_DIR)/execution

INCLUDES :=		-Iinc

MAIN_SRCS :=	main.c

EXEC_SRCS :=	error.c \
				exec_cmd.c \
				execution.c \
				fd_collector.c \
				get_path.c \
				here_doc.c \
				init.c \
				redirection_cases.c \
				redirctions.c \
				setup_child.c

SRCS :=			$(MAIN_SRCS) \
				$(EXEC_SRCS)

OBJS :=			$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	$(MAKE) -C src/libft

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	make -C src/libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C src/libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re