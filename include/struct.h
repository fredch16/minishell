/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:28:02 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/15 17:58:56 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stddef.h>  /* For size_t */
# include <string.h>  /* For strdup */
# include "libft/libft.h"
# include "garbage_collector.h"

typedef struct s_env_list	t_env_list;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_ERROR
}	t_redir_type;

typedef enum e_cmd_type
{
	BUILTIN,
	STDCMD
}						t_cmd_type;

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
}						t_token_type;

typedef struct s_hd_line
{
	char				*line;
	struct s_hd_line	*next;
}						t_hd_line;

typedef struct s_hd_node
{
	t_hd_node			*next;
	t_hd_line			*lines;
	char				*lim;
}						t_hd_node;

typedef struct s_hd_list
{
	t_hd_node			*head;
	t_hd_node			*tail;
	size_t				size;
}						t_hd_list;

typedef struct s_exec_data
{
	int					input_file;
	int					output_file;
	char				**ep;
}						t_exec_data;

typedef struct s_token_node
{
	char				*content;
	t_token_type		type;
	size_t				length;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_token_list
{
	t_token_node	*head;
	t_token_node	*tail;
	t_env_list		*env;
	char			*input;
	int				exit_code;
	int				error_code;
	size_t			size;

}	t_token_list;

typedef struct s_file_node
{
	t_redir_type		redir_type;
	char				*filename;
	char 				*lim;
	struct s_file_node	*next;
}	t_file_node;

typedef struct s_file_list
{
	t_file_node	*head;
	t_file_node	*tail;
	size_t		size;
}	t_file_list;

typedef struct s_env_node
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
	int					fd[2];
	t_file_list			*files;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node		*head;
	t_cmd_node		*tail;
	size_t			size;
	t_env_list		*env;
	char			*input;
	int				exit_code;
	int				error_code;
}	t_cmd_list;

typedef enum e_quote_state
{
	UNQUOTED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED
}	t_quote_state;

typedef struct termios t_termios;

typedef struct s_t_t_settings
{
	t_termios		termios;
	int				termios_saved;
}					t_t_settings;

typedef struct s_mini
{
	t_cmd_list		*cmd_list;
	t_token_list	*token_list;
	t_env_list		*env_list;
	t_exec_data		exec_data;
	int				exit_code;
	int				error_code;
}	t_mini;

/**
 * Structure for tracking allocated memory
 */
typedef enum e_gc_type
{
	GC_PARSE,
	GC_ENV,
	GC_EXEC,
	GC_OTHER
}	t_gc_type;

typedef struct s_garbage_node
{
	void					*ptr;
	t_gc_type				type;
	struct s_garbage_node	*next;
}	t_garbage_node;

typedef struct s_garbage_list
{
	t_garbage_node	*head;
	t_garbage_node	*tail;
	size_t			size;
}					t_garbage_list;

typedef struct s_fd_node
{
	int					fd;
	struct s_fd_node	*next;
}						t_fd_node;

typedef struct s_fd_list
{
	t_fd_node			*head;
	t_fd_node			*tail;
	size_t				size;
}						t_fd_list;

#endif