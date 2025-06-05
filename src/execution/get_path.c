/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:58:06 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/05 07:10:07 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*check_absolute_path(char *command)
{
	if (access(command, F_OK | X_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}

static char	*try_path(char *dir, char *command)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, command);
	free(temp);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK | X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_in_paths(char *command, char **bin_paths)
{
	int		i;
	char	*result;

	i = 0;
	while (bin_paths[i])
	{
		result = try_path(bin_paths[i], command);
		if (result)
			return (result);
		i++;
	}
	return (ft_error(127, NULL), NULL);
}

char	*get_command_path(t_cmd_node *cmd_node, t_mini *mini)
{
	char	*path_env;
	char	**bin_paths;
	char	*result;

	if (ft_strchr(cmd_node->cmd[0], '/'))
		return (check_absolute_path(cmd_node->cmd[0]));
	path_env = get_env_value(mini->env_list, "PATH");
	if (!path_env)
		return (NULL);
	bin_paths = ft_split(path_env, ':');
	if (!bin_paths)
		return (NULL);
	result = search_in_paths(cmd_node->cmd[0], bin_paths);
	return (result);
}
