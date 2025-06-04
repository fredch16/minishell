/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:34:17 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/04 06:52:04 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_unused_pipes(int **pipes, int cmd_index, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (i != cmd_index - 1)
			close(pipes[i][0]);
		if (i != cmd_index)
			close(pipes[i][1]);
		i++;
	}
}

static void	setup_child_pipes(int **pipes, int cmd_index, int pipe_count, t_mini *mini)
{
	if (cmd_index > 0)
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
		close(pipes[cmd_index - 1][0]);
	}
	if (cmd_index < pipe_count)
	{
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
		close(pipes[cmd_index][1]);
	}
	close_unused_pipes(pipes, cmd_index, pipe_count);
	setup_child_input(mini);
	setup_child_output(mini);
}

int	fork_and_exec(t_cmd_node *cmd, t_mini *mini, int **pipes, int *params)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_child_pipes(pipes, params[0], params[1], mini);
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
