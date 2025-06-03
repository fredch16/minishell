# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 16:31:00 by fredchar          #+#    #+#              #
#    Updated: 2025/06/03 22:50:39 by fredchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CC := gcc
CFLAGS := -Wall -Wextra -Werror -g
INCD := include
SRCD := src
OBJD := obj
LIBFT_DIR := $(INCD)/libft
LIBFT := $(LIBFT_DIR)/libft.a

# Colors
GREEN := \033[0;32m
YELLOW := \033[0;33m
RED := \033[0;31m
NC := \033[0m # No Color

SRCS := $(SRCD)/main.c \
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
		$(SRCD)/debug.c \

# Convert src paths to obj paths correctly
OBJS := $(patsubst $(SRCD)/%.c,$(OBJD)/%.o,$(SRCS))

# Get all directories where object files will be stored
OBJ_DIRS := $(sort $(dir $(OBJS)))

all: mkdir_obj $(NAME)

mkdir_obj:
	@mkdir -p $(OBJ_DIRS)

$(LIBFT):
	@printf "$(YELLOW)Building libft library...$(NC)\n"
	@$(MAKE) -C $(LIBFT_DIR)

# Create object file directories before compiling
$(OBJD)/%.o: $(SRCD)/%.c
	@printf "$(YELLOW)Compiling $<...$(NC)\n"
	@$(CC) $(CFLAGS) -I $(INCD) -c $< -o $@
	@printf "$(GREEN)Compiled $< successfully!$(NC)\n"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@printf "$(GREEN)Executable $(NAME) built successfully!$(NC)\n"

clean:
	@printf "$(RED)Cleaning object files...$(NC)\n"
	@rm -rf $(OBJD)
	@printf "$(GREEN)Object files cleaned!$(NC)\n"
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@printf "$(RED)Cleaning library and executable...$(NC)\n"
	@rm -f $(NAME)
	@printf "$(GREEN)Executable cleaned!$(NC)\n"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re mkdir_obj