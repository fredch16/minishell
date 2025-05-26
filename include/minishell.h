/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:47:25 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/26 23:54:45 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include "libft/libft.h"
# include "garbage_collector.h"

// remember ECHo and echo is the same, same for all builtins

/* Forward declarations with correct syntax */
struct s_cmd_node;
struct s_file_node;
struct s_token_node;

typedef enum e_redir_type
{
	REDIR_IN,         /* < */
	REDIR_OUT,            /* > */
	REDIR_APPEND,         /* >> */
	REDIR_HEREDOC          /* << */
}	t_redir_type;

typedef struct s_token_node
{
	char				*token;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_token_list
{
	t_token_node	*head;
	t_token_node	*tail;
	size_t			size;
}	t_token_list;

typedef struct s_file_node
{
	t_redir_type		redir_type;
	char				*file_name;
	struct s_file_node	*next;
}	t_file_node;

typedef struct s_file_list
{
	t_file_node	*head;
	t_file_node	*tail;
	size_t		size;
}	t_file_list;

typedef struct s_cmd_node
{
	int					cmd_type;
	char				**cmd;
	t_file_list			*file_list;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node	*head;
	t_cmd_node	*tail;
	size_t		size;
}	t_cmd_list;

/* Token functions */
t_token_list	*init_token_list(void);
t_token_node	*create_token_node(char *token);
void			add_token_to_list(t_token_list *list, t_token_node *node);
void			free_token_list(t_token_list *list);
int				tokenise(t_token_list *token_list, char *line);
void			print_tokens(t_token_list *list);

#endif