/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 06:24:21 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/23 17:47:49 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	fork_and_exec_loop(t_cmd_node *cmd, t_mini *mini, int **pipes,
	pid_t *pids)
{
	int	i;

	i = 0;
	while (cmd)
	{
		pids[i] = fork_and_exec(cmd, mini, pipes, i);
		if (pids[i] == -1)
			return (cleanup_pipeline(pipes, pids, mini->cmd_list->size - 1, 1));
		if (i > 0 && pipes)
		{
			close(pipes[i - 1][0]);
			close(pipes[i - 1][1]);
		}
		cmd = cmd->next;
		i++;
	}
	if (pipes && mini->cmd_list->size - 1 > 0)
	{
		close(pipes[mini->cmd_list->size - 2][0]);
		close(pipes[mini->cmd_list->size - 2][1]);
	}
	return (0);
}

int	execute_pipeline(t_mini *mini)
{
	t_cmd_node	*cmd;
	int			**pipes;
	pid_t		*pids;
	int			pipe_count;

	pipe_count = mini->cmd_list->size - 1;
	pipes = NULL;
	if (pipe_count > 0)
	{
		pipes = create_pipes(pipe_count);
		if (!pipes)
			return (1);
	}
	pids = malloc(sizeof(pid_t) * mini->cmd_list->size);
	if (!pids)
		return (cleanup_pipeline(pipes, NULL, pipe_count, 1));
	gc_track(pids, GC_EXEC);
	cmd = mini->cmd_list->head;
	fork_and_exec_loop(cmd, mini, pipes, pids);
	if (pipe_count == 0)
		return (wait_for_children(pids, 1), mini->exit_code);
	return (finalize_pipeline(pipes, pids, mini, pipe_count));
}
