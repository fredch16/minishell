/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:11:05 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/04 06:56:29 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_if_not_std(int fd, int std_fd)
{
	if (fd != std_fd && fd != -1)
		close(fd);
}

int	handle_heredoc_redir(char *delimiter, t_mini *mini)
{
	int	fd;

	fd = create_heredoc(delimiter);
	if (fd == -1)
		return (-1);
	close_if_not_std(mini->exec_data.input_file, STDIN_FILENO);
	mini->exec_data.input_file = fd;
	return (0);
}

int	handle_input_redir(t_file_node *file_node, t_mini *mini)
{
	int	fd;

	fd = open(file_node->filename, O_RDONLY);
	if (fd == -1)
		return (perror(file_node->filename), -1);
	close_if_not_std(mini->exec_data.input_file, STDIN_FILENO);
	mini->exec_data.input_file = fd;
	return (0);
}

int	handle_output_redir(t_file_node *file_node, t_mini *mini)
{
	int	fd;

	fd = open(file_node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(file_node->filename), -1);
	close_if_not_std(mini->exec_data.output_file, STDOUT_FILENO);
	mini->exec_data.output_file = fd;
	return (0);
}

int	handle_append_redir(t_file_node *file_node, t_mini *mini)
{
	int	fd;

	fd = open(file_node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(file_node->filename), -1);
	close_if_not_std(mini->exec_data.output_file, STDOUT_FILENO);
	mini->exec_data.output_file = fd;
	return (0);
}
