/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:24:12 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/25 11:32:04 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_hd_node	*get_heredoc_for_file(t_cmd_node *cmd_node,
	t_file_node *file_node)
{
	t_hd_node	*current;

	current = cmd_node->hd_list.head;
	while (current)
	{
		if (current->file_node == file_node)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	process_input_redirection(t_file_node *file_node, t_mini *mini,
	t_cmd_node *cmd_node, int builtins)
{
	t_hd_node	*hd_node;

	(void)builtins;
	if (file_node->redir_type == REDIR_IN)
		return (handle_input_redir(file_node, mini));
	if (file_node->redir_type == REDIR_HEREDOC)
	{
		hd_node = get_heredoc_for_file(cmd_node, file_node);
		if (!hd_node)
			return (-1);
		return (create_heredoc_fd(hd_node));
	}
	return (-1);
}

int	process_output_redirection(t_file_node *file_node, t_mini *mini)
{
	if (file_node->redir_type == REDIR_OUT)
		return (handle_output_redir(file_node, mini));
	if (file_node->redir_type == REDIR_APPEND)
		return (handle_append_redir(file_node, mini));
	return (0);
}

int	dup_fd(int last_input_fd)
{
	if (last_input_fd != -1)
	{
		if (dup2(last_input_fd, STDIN_FILENO) == -1)
		{
			perror("minishell");
			close(last_input_fd);
			return (-1);
		}
		close(last_input_fd);
	}
	return (0);
}
