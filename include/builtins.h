/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:31:22 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/25 15:38:08 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		echo_builtin(char **args);
int		pwd_builtin(void);
int		env_builtin(t_env_list *env_list);
int		unset_builtin(t_env_list *env_list, char **args);
int		export_builtin(t_env_list *env_list, char **args);
int		cd_builtin(t_env_list *env_list, char **args);
int		exit_minishell(t_cmd_node *cmd_node);
int		export_no_arg(t_env_list *env_list);
void	assign_empty_var(t_env_list *env_list, char *arg);
int		find_append(char *arg);
int		trust_but_verify(char *arg);
int		has_equals(char *arg);

#endif