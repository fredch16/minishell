/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:04:20 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/23 18:15:23 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_delimiter(char *line, char *delimiter)
{
	int	len;

	if (!line || !delimiter)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strcmp(line, delimiter) == 0)
		return (free(line), 1);
	return (0);
}

int	check_exit_status(pid_t child_pid, t_mini *mini)
{
	int	status;

	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		mini->exit_code = 130;
		return (-1);
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		return (-1);
	return (0);
}

int	create_heredoc_fd(t_hd_node *hd_node)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	write_heredoc_to_pipe(hd_node, pipe_fd[1]);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	write_heredoc_to_pipe(t_hd_node *hd_node, int write_fd)
{
	t_hd_line	*current;

	current = hd_node->lines;
	while (current)
	{
		if (current->line)
		{
			write(write_fd, current->line, ft_strlen(current->line));
			write(write_fd, "\n", 1);
		}
		current = current->next;
	}
	return (0);
}
