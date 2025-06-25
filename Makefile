# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 13:42:12 by apregitz          #+#    #+#              #
#    Updated: 2025/06/25 11:32:38 by apregitz         ###   ########.fr        #
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
			$(SRCD)/expansion/tilde.c \
			$(SRCD)/parser/_parser.c \
			$(SRCD)/parser/commands.c \
			$(SRCD)/parser/redirections.c \
			$(SRCD)/parser/cmd_linked_list.c \
			$(SRCD)/parser/file_linked_list.c \
			$(SRCD)/utilities/error.c \
			$(SRCD)/env_list/init_env.c \
			$(SRCD)/env_list/env_to_array.c \
			$(SRCD)/env_list/env_ops.c \
			$(SRCD)/env_list/env_ops2.c \
			$(SRCD)/garbage_collector/garbage.c \
			$(SRCD)/garbage_collector/garbage2.c \
			$(SRCD)/garbage_collector/garbage3.c \
			$(SRCD)/builtins/echo.c \
			$(SRCD)/builtins/pwd.c \
			$(SRCD)/builtins/env.c \
			$(SRCD)/builtins/unset.c \
			$(SRCD)/builtins/export.c \
			$(SRCD)/builtins/export2.c \
			$(SRCD)/builtins/cd.c \
			$(SRCD)/builtins/exit_minishell.c \
			$(SRCD)/execution/_execution.c \
			$(SRCD)/execution/pipes.c \
			$(SRCD)/execution/heredoc_utils.c \
			$(SRCD)/execution/heredoc_struct_utils.c \
			$(SRCD)/execution/exec_pipes.c \
			$(SRCD)/execution/pipes_utils.c \
			$(SRCD)/execution/execute_commands.c \
			$(SRCD)/execution/get_path.c \
			$(SRCD)/execution/init.c \
			$(SRCD)/redirect/redirections.c \
			$(SRCD)/redirect/redirections_utils.c \
			$(SRCD)/redirect/reverting_stds.c \
			$(SRCD)/redirect/redirection_cases.c \
			$(SRCD)/redirect/expand_heredoc.c \
			$(SRCD)/execution/setup_child.c \
			$(SRCD)/execution/here_doc.c \
			$(SRCD)/execution/error.c \
			$(SRCD)/signals.c \
			$(SRCD)/t_settings.c

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
			$(OBJD)/execution \
			$(OBJD)/redirect

all: $(NAME)

$(NAME): $(OBJ_DIRS) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C include/libft

$(OBJ_DIRS):
	@mkdir -p $(OBJ_DIRS)
	@echo "Compiling minishell"

$(OBJD)/%.o: $(SRCD)/%.c
	@$(eval TOTAL := $(words $(SRCS)))
	@$(eval PROGRESS := $(shell echo $$(($(PROGRESS)+1))))
	@$(eval PERCENT := $(shell echo $$(($(PROGRESS)*100/$(TOTAL)))))
	@$(call progress_bar,$(PERCENT))
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(MAKE) -C include/libft clean
	@rm -rf $(OBJD)

fclean: clean
	@$(MAKE) -C include/libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

RED     := $(shell tput setaf 1)
GREEN   := $(shell tput setaf 2)
YELLOW  := $(shell tput setaf 3)
BLUE    := $(shell tput setaf 4)
MAGENTA := $(shell tput setaf 5)
CYAN    := $(shell tput setaf 6)
WHITE   := $(shell tput setaf 7)
RESET   := $(shell tput sgr0)

define progress_bar
	@printf "$(CYAN)["; \
	for i in $(shell seq 1 50); do \
		if [ $$i -le $$(($(1)*50/100)) ]; then \
			printf "$(GREEN)█$(RESET)"; \
		else \
			printf "$(WHITE)░$(RESET)"; \
		fi; \
	done; \
	printf "$(CYAN)] %3d%%$(RESET)\r" $(1);
endef
