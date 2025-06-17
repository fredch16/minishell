/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:11:05 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/10 17:19:49 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Updated redirection_cases.c */
#include "../../include/minishell.h"

int	handle_heredoc_redir(char *delimiter, t_mini *mini, t_cmd_node *cmd_node, int builtins)
{
	int	fd;

	fd = create_heredoc(delimiter, mini, cmd_node, builtins);
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