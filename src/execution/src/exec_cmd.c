/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:31:44 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/01 12:15:38 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cmd(t_cmd_node *cmd_node, t_exec_data *exec_data)
{
	char	*path;
	pid_t	pid;

	path = get_path(cmd_node->cmd[0], exec_data->ep);
	if (!path)
		error();
	pid = fork();
	if (pid == 0)
	{
		if (dup2(exec_data->fd[0], STDIN_FILENO) == -1 \
		|| dup2(exec_data->fd[1], STDOUT_FILENO) == -1)
			error();
		close(exec_data->fd[0]);
		close(exec_data->fd[1]);
		execve(path, cmd_node->cmd, exec_data->ep);
		error();
	}
	return (1);
}
