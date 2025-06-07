/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:31:22 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/06 17:35:44 by fredchar         ###   ########.fr       */
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

#endif