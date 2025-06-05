/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:34:17 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/05 06:36:05 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_child_pipes(int **pipes, int cmd_index, int pipe_count)
{
	int	i;

	if (cmd_index > 0)
	{
		if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
			ft_error(1, "dup2 input failed");
	}
	if (cmd_index < pipe_count)
	{
		if (dup2(pipes[cmd_index][1], STDOUT_FILENO) == -1)
			ft_error(1, "dup2 output failed");
	}
	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	fork_and_exec(t_cmd_node *cmd, t_mini *mini, int **pipes, int index)
{
	pid_t	pid;
	int		pipe_count;

	pipe_count = mini->cmd_list->size - 1;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_child_pipes(pipes, index, pipe_count);
		if (handle_redirections(cmd, mini) == -1)
			ft_error(1, "Redirection failed");
		if (cmd->cmd_type == BUILTIN)
			execute_builtin(cmd, mini);
		else
			execute_external(cmd, mini);
		ft_error(127, "Command execution failed");
	}
	return (pid);
}
