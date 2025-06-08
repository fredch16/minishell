/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:11:05 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/08 06:48:30 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Updated redirection_cases.c */
#include "../../include/minishell.h"

int	handle_heredoc_redir(char *delimiter, t_mini *mini)
{
	int	fd;

	fd = create_heredoc(delimiter, mini);
	if (fd == -1)
		ft_error(1, "open", 0);
	return (fd);
}

int	handle_input_redir(t_file_node *file_node, t_mini *mini)
{
	int	fd;

	(void)mini;
	fd = open(file_node->filename, O_RDONLY);
	if (fd == -1)
		ft_error(1, "open", 0);
	return (fd);
}

int	handle_output_redir(t_file_node *file_node, t_mini *mini)
{
	int	fd;

	(void)mini;
	fd = open(file_node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error(1, "open", 0);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_error(1, "dup2", 0);
	close(fd);
	return (0);
}

int	handle_append_redir(t_file_node *file_node, t_mini *mini)
{
	int	fd;

	(void)mini;
	fd = open(file_node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_error(1, "open", 0);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_error(1, "dup2", 0);
	close(fd);
	return (0);
}