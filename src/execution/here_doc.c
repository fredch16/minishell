/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:13:39 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/11 18:06:24 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t g_signal_recieved;

static void	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static int	is_delimiter(char *line, char *delimiter)
{
	if (!line || !delimiter)
		return (0);
	return (ft_strcmp(line, delimiter) == 0);
}

static void	read_heredoc_lines(t_mini *mini, char *delimiter, int write_fd, t_cmd_node *cmd_node, int builtin)
{
	char	*line;

	if (builtin)
		setup_heredoc_signals();
	else
		setup_heredoc_signals_child();
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_delimiter(line, delimiter))
			return (free(line));
		if (g_signal_recieved == 3)
		{
			if (line)
				free(line);
			break ;
		}
		line = expand_heredoc(mini, line);
		if (!line)
			break ;
		if (cmd_node && cmd_node->cmd && cmd_node->cmd[0])
			write_heredoc_line(write_fd, line);
		free(line);
	}
}

int	create_heredoc(char *delimiter, t_mini *mini, t_cmd_node *cmd_node, int builtin)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), perror("fork"), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		read_heredoc_lines(mini, delimiter, pipefd[1], cmd_node, builtin);
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (close(pipefd[0]), -1);
	return (pipefd[0]);
}
