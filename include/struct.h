/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:28:02 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/31 17:02:13 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stddef.h>  /* For size_t */
# include <string.h>  /* For strdup */
# include "libft/libft.h"
# include "garbage_collector.h"

typedef struct s_env_list t_env_list;

typedef enum e_redir_type
{
	REDIR_IN,         /* < */
	REDIR_OUT,            /* > */
	REDIR_APPEND,         /* >> */
	REDIR_HEREDOC          /* << */
}	t_redir_type;

typedef enum e_cmd_type
{
	BUILTIN,
	STDCMD
}	t_cmd_type;

typedef enum e_token_type
{
	TK_WORD = 1,
	TK_CMD,
	TK_PIPE,
	TK_INFILE,
	TK_OUTFILE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_REDIR_APPEND,
	TK_REDIR_HEREDOC,
	TK_D_QUOTES,
	TK_BUILTIN,
	TK_S_QUOTES
}	t_token_type;

typedef struct s_token_node
{
	char			*content;
	t_token_type	type;
	size_t			length;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_token_list
{
	t_token_node	*head;
	t_token_node	*tail;
	t_env_list		*env;
	char			*input;
	int				exit_code;
	size_t			size;

}	t_token_list;

typedef struct s_file_node
{
	t_redir_type		redir_type;
	char				*filename;
	struct s_file_node	*next;
}	t_file_node;

typedef struct s_file_list
{
	t_file_node	*head;
	t_file_node	*tail;
	size_t		size;
}	t_file_list;

typedef	struct s_env_node
{
	struct s_env_node	*next;
	char				*variable;
	char				*value;
}	t_env_node;

typedef struct s_env_list
{
	t_env_node	*head;
	t_env_node	*tail;
	size_t		size;
}	t_env_list;

typedef struct s_cmd_node
{
	t_cmd_type			cmd_type;
	char				**cmd;
	t_file_list			*files;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node	*head;
	t_cmd_node	*tail;
	size_t		size;
}	t_cmd_list;

typedef enum e_quote_state
{
	UNQUOTED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED
} t_quote_state;

typedef	struct s_mini
{
	t_cmd_list		*cmd_list;
	t_token_list	*token_list;
	t_env_list		*env_list;
	int				exit_code;
}	t_mini;

/**
 * Structure for tracking allocated memory
 */
typedef enum e_gc_type
{
	GC_PARSE,
	GC_ENV,
	GC_OTHER
}	t_gc_type;

typedef struct s_garbage_node
{
	void					*ptr;
	t_gc_type				type;
	struct s_garbage_node	*next;
}	t_garbage_node;

#endif