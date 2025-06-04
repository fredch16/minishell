/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 06:24:21 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/04 07:14:18 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_pipeline(t_mini *mini)
{
	t_cmd_node	*cmd;
	int			**pipes;
	pid_t		*pids;
	int			params[2];

	params[1] = mini->cmd_list->size - 1;
	pipes = NULL;
	if (params[1] > 0)
	{
		pipes = create_pipes(params[1]);
		if (!pipes)
			return (1);
	}
	pids = malloc(sizeof(pid_t) * mini->cmd_list->size);
	if (!pids)
		return (cleanup_pipeline(pipes, NULL, params[1], 1));
	cmd = mini->cmd_list->head;
	params[0] = 0;
	while (cmd)
	{
		pids[params[0]] = fork_and_exec(cmd, mini, pipes, params);
		if (pids[params[0]] == -1)
			return (cleanup_pipeline(pipes, pids, params[1], 1));
		cmd = cmd->next;
		params[0]++;
	}
	return (finalize_pipeline(pipes, pids, mini, params[1]));
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
