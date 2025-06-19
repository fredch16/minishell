/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:31:22 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/18 10:02:28 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	echo_builtin(char **args);
int	pwd_builtin(void);
int	env_builtin(t_env_list *env_list);
int	unset_builtin(t_env_list *env_list, char **args);
int	export_builtin(t_env_list *env_list, char **args);
int	cd_builtin(t_env_list *env_list, char **args);
int exit_minishell(t_cmd_node *cmd_node);

#endif