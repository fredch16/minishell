/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:13:39 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/02 11:52:47 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}

static int	is_delimiter(char *line, char *delimiter)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (ft_strcmp(line, delimiter) == 0);
}
static void	read_heredoc_lines(char *delimiter, int write_fd)
{
	char	*line;

	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write_heredoc_line(write_fd, line);
		free(line);
	}
}

int	create_heredoc(char *delimiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	read_heredoc_lines(delimiter, pipefd[1]);
	close(pipefd[1]);
	return (pipefd[0]);
}
