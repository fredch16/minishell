/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:38:49 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/30 17:00:42 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"
# include "garbage_collector.h"
# include "struct.h"
# include "parser.h"
# include "expansion.h"
# include "debug.h"

// remember ECHo and echo is the same, same for all builtins

void			print_tokens(t_token_list *list);

/* Environment variable handling */
// init_env.c
t_env_list	*init_env_list(void);
t_env_node	*create_env_node(char *variable, char *value);
int			parse_env_string(char *env_str, char **variable, char **value);
void		add_env_node(t_env_list *list, t_env_node *node);
t_env_list	*env_array_to_list(char **env);
char		**env_list_to_array(t_env_list *list);

// env_ops.c
t_env_node	*find_env_var(t_env_list *list, char *variable);
char		*get_env_value(t_env_list *list, char *variable);
int			set_env_var(t_env_list *list, char *variable, char *value);
int			unset_env_var(t_env_list *list, char *variable);
void		print_env(t_env_list *list);

#endif