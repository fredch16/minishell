/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 06:24:21 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/04 15:33:14 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_pipeline(t_mini *mini)
{
	t_cmd_node	*cmd;
	int			**pipes;
	pid_t		*pids;
	int			i;

	pipes = NULL;
	if (mini->cmd_list->size > 1)
	{
		pipes = create_pipes(mini->cmd_list->size - 1);
		if (!pipes)
			return (1);
	}
	pids = malloc(sizeof(pid_t) * mini->cmd_list->size);
	if (!pids)
		return (cleanup_pipeline(pipes, NULL, mini->cmd_list->size - 1, 1));
	gc_track(pids, GC_EXEC);
	cmd = mini->cmd_list->head;
	i = 0;
	while (cmd)
	{
		pids[i] = fork_and_exec(cmd, mini, pipes, i);
		if (pids[i] == -1)
			return (cleanup_pipeline(pipes, pids, mini->cmd_list->size - 1, 1));
		cmd = cmd->next;
		i++;
	}
	return (finalize_pipeline(pipes, pids, mini, mini->cmd_list->size - 1));
}

// int	execute_pipeline(t_mini *mini)
// {
// 	t_cmd_node	*cmd;
// 	int			**pipes;
// 	pid_t		*pids;
// 	int			cmd_index;
// 	int			pipe_count;

// 	pipe_count = mini->cmd_list->size - 1;
// 	if (pipe_count < 0)
// 		return (0);
// 	pipes = NULL;
// 	if (pipe_count > 0)
// 	{
// 		pipes = create_pipes(pipe_count);
// 		if (!pipes)
// 			return (1);
// 	}
// 	pids = malloc(sizeof(pid_t) * mini->cmd_list->size);
// 	if (!pids)
// 	{
// 		if (pipes)
// 			close_all_pipes(pipes, pipe_count);
// 		return (1);
// 	}
// 	cmd = mini->cmd_list->head;
// 	cmd_index = 0;
// 	while (cmd)
// 	{
// 		pids[cmd_index] = fork_and_exec(cmd, mini, pipes, &cmd_index);
// 		if (pids[cmd_index] == -1)
// 		{
// 			free(pids);
// 			if (pipes)
// 				close_all_pipes(pipes, pipe_count);
// 			return (1);
// 		}
// 		cmd = cmd->next;
// 		cmd_index++;
// 	}
// 	if (pipes)
// 		close_all_pipes(pipes, pipe_count);
// 	cmd_index = wait_for_children(pids, mini->cmd_list->size);
// 	free(pids);
// 	return (cmd_index);
// }
