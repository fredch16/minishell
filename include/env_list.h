/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:11:01 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/04 05:14:47 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_H
# define ENV_LIST_H
# include "minishell.h"

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