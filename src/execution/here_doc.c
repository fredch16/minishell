/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:13:39 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/07 17:06:26 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

static void	read_heredoc_lines(t_mini *mini, char *delimiter, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		line = expand_heredoc(mini, line);
		if (!line)
		{
			// do error handling
			break ;
		}
		write_heredoc_line(write_fd, line);
		free(line);
	}
}

int	create_heredoc(char *delimiter, t_mini *mini)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	read_heredoc_lines(mini, delimiter, pipefd[1]);
	close(pipefd[1]);
	return (pipefd[0]);
}