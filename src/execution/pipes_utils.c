/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 06:04:46 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/07 19:46:38 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	**create_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	if (pipe_count <= 0)
		return (NULL);
	pipes = gc_malloc(sizeof(int *) * pipe_count, GC_EXEC);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = gc_malloc(sizeof(int) * 2, GC_EXEC);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			while (--i >= 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
			}
			return (NULL);
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
		gc_free(pipes[i]);
		i++;
	}
	gc_free(pipes);
}

int	cleanup_pipeline(int **pipes, pid_t *pids, int pipe_count, int ret_val)
{
	if (pids)
		gc_free(pids);
	if (pipes)
		close_all_pipes(pipes, pipe_count);
	return (ret_val);
}

int	finalize_pipeline(int **pipes, pid_t *pids, t_mini *mini, int pipe_count)
{
	int	exit_code;

	(void)pipe_count;
	if (pipes)
		gc_free(pipes);
	exit_code = wait_for_children(pids, mini->cmd_list->size);
	return (exit_code);
}
