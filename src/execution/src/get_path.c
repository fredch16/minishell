/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:58:06 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/30 17:45:25 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(t_cmd_node *cmd_node, t_mini mini)
{
	int		i;
	char	**bin_paths;
	char	*final_path;
	char	*temp;

	if (access(cmd_node->cmd[0], F_OK) == 0)
		return (ft_strdup(cmd_node->cmd[0]));
	i = 0;
	temp = get_env_value(mini.env_list, "PATH");
	bin_paths = ft_split(temp, ':');
	i = -1;
	while (bin_paths[++i])
	{
		temp = ft_strjoin(bin_paths[i], "/");
		final_path = ft_strjoin(temp, cmd_node->cmd);
		free(temp);
		if (access(final_path, F_OK) == 0)
			return (final_path);
		free(final_path);
	}
	free_2d_array(bin_paths);
	exit(127);
}

