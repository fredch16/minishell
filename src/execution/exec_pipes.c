/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 06:24:21 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/09 15:08:57 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_pipeline(t_mini *mini)
{
	t_cmd_node	*cmd;
	int			**pipes;
	pid_t		*pids;
	int			i;
	int			pipe_count;

	// save_terminal_settings();
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
	i = 0;
	while (cmd)
	{
		pids[i] = fork_and_exec(cmd, mini, pipes, i);
		if (pids[i] == -1)
			return (cleanup_pipeline(pipes, pids, pipe_count, 1));
		if (i > 0 && pipes)
		{
			close(pipes[i - 1][0]);
			close(pipes[i - 1][1]);
		}
		cmd = cmd->next;
		i++;
	}
	if (pipes && pipe_count > 0)
	{
		close(pipes[pipe_count - 1][0]);
		close(pipes[pipe_count - 1][1]);
	}
	if (pipe_count == 0)
	{
		wait_for_children(pids, 1);
		// restore_terminal();
		return (mini->exit_code);
	}
	return (finalize_pipeline(pipes, pids, mini, pipe_count));
}	
