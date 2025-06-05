/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 06:04:46 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/05 06:49:01 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	**create_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	if (pipe_count <= 0)
		return (NULL);
	pipes = malloc(sizeof(int *) * pipe_count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			return (free(pipes), NULL);
		}
		i++;
	}
	return (pipes);
}

void	close_all_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes || pipe_count <= 0)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	cleanup_pipeline(int **pipes, pid_t *pids, int pipe_count, int ret_val)
{
	if (pids)
		free(pids);
	if (pipes)
		close_all_pipes(pipes, pipe_count);
	return (ret_val);
}

int	finalize_pipeline(int **pipes, pid_t *pids, t_mini *mini, int pipe_count)
{
	int	exit_code;

	(void)pipe_count;
	if (pipes)
		free(pipes);
	exit_code = wait_for_children(pids, mini->cmd_list->size);
	return (exit_code);
}
