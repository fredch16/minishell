/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:47:25 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/26 18:32:54 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>

// remember ECHo and echo is the same, same for all builtins

typedef struct t_cmd_node;
typedef struct t_file_node;

typedef enum e_redir_type
{
	REDIR_IN = 1,         /* < */
	REDIR_OUT,            /* > */
	REDIR_APPEND,         /* >> */
	REDIR_HEREDOC         /* << */
}	t_redir_type;

typedef struct s_file_node
{
	t_redir_type	redir_type;
	char			*file_name;
	t_file_node		*next;
}	t_file_node;

typedef struct s_file_list
{
	t_file_node *head;
	t_file_node *tail;
	size_t		size;
}	t_file_list;

typedef struct s_cmd_node
{
	int		cmd_type;
	char	**cmd;
	t_file_list	*flist;
	t_cmd_node	*next;
}	t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node *head;
	t_cmd_node *tail;
	size_t		size;
}	t_cmd_list;

#endif