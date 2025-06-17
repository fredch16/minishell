/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:12:31 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/17 02:37:08 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	go_to_old_pwd(t_env_list *env_list)
{
	char	*temp1;
	char	*temp2;

	temp1 = get_env_value(env_list, "PWD");
	temp2 = get_env_value(env_list, "OLDPWD");
	set_env_var(env_list, "PWD", temp2);
	set_env_var(env_list, "OLDPWD", temp1);
	chdir(get_env_value(env_list, "PWD"));
	return (0);
}

int	cd_builtin(t_env_list *env_list, char **args)
{
	char	*path;
	char	*oldpwd;
	char	*cwd;

	if (ft_strs_len(args) > 2)
		return (ft_putstr_fd("minishell: cd: too many arguments \n", 2), 1);
	if (ft_strcmp(args[1], "-") == 0)
		return (go_to_old_pwd(env_list));
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (ft_putendl_fd("minishell: cd failed", STDERR_FILENO), 1);
	gc_track(oldpwd, GC_EXEC);
	if (!args[1])
		path = get_env_value(env_list, "HOME");
	else
		path = args[1];
	if (chdir(path))
	{
		ft_putstr_fd("minishell: no such file or directory: ", STDERR_FILENO);
		return (ft_putendl_fd(path, STDERR_FILENO), 1);
	}
	set_env_var(env_list, "OLDPWD", oldpwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_putendl_fd("minishell: cd failed", STDERR_FILENO), 1);
	gc_track(cwd, GC_EXEC);
<<<<<<< HEAD
<<<<<<< HEAD
	return (set_env_var(env_list, "PWD", cwd), 0);
=======
	set_env_var(env_list, "PWD", cwd);
	return (0);
>>>>>>> test-merge-v2
=======
	set_env_var(env_list, "PWD", cwd);
	return (0);
>>>>>>> d942762a441ad445e8a5e5c638b54a301dedbc8f
}
