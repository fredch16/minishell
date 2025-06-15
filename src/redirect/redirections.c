/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:20:04 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/15 13:37:44 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t g_signal_recieved;

static int	process_input_redirection(t_file_node *file_node, t_mini *mini, t_cmd_node *cmd_node, int builtins)
{
	if (file_node->redir_type == REDIR_IN)
		return (handle_input_redir(file_node, mini));
	if (file_node->redir_type == REDIR_HEREDOC)
		return (handle_heredoc_redir(file_node->filename, mini, cmd_node, builtins));
	return (-1);
}

static int	process_output_redirection(t_file_node *file_node, t_mini *mini)
{
	if (file_node->redir_type == REDIR_OUT)
		return (handle_output_redir(file_node, mini));
	if (file_node->redir_type == REDIR_APPEND)
		return (handle_append_redir(file_node, mini));
	return (0);
}

int	handle_redirections(t_cmd_node *cmd_node, t_mini *mini, int builtins)
{
	t_file_node	*file_node;
	int			last_input_fd;
	int			temp_fd;

	if (!cmd_node->files || !cmd_node->files->head)
		return (0);
	last_input_fd = -1;
	file_node = cmd_node->files->head;
	while (file_node)
	{
		if (file_node->redir_type == REDIR_IN || file_node->redir_type == REDIR_HEREDOC)
		{
			if (last_input_fd != -1)
				close(last_input_fd);
			temp_fd = process_input_redirection(file_node, mini, cmd_node, builtins);
			if (temp_fd == -1)
				last_input_fd = -1;
			else
				last_input_fd = temp_fd;
		}
		else
		{
			if (process_output_redirection(file_node, mini) == -1)
				return (-1);
		}
		file_node = file_node->next;
	}
	if (last_input_fd != -1)
	{
		if (dup2(last_input_fd, STDIN_FILENO) == -1)
			return (perror("minishell"), close(last_input_fd), -1);
		close(last_input_fd);
	}
	return (0);
}