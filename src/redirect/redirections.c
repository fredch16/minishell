/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:20:04 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/17 10:30:19 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t g_signal_recieved;

// Find the heredoc node for this specific file_node
static t_hd_node	*get_heredoc_for_file(t_cmd_node *cmd_node, t_file_node *file_node)
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

static int	process_input_redirection(t_file_node *file_node, t_mini *mini, t_cmd_node *cmd_node, int builtins)
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
			{
				if (!builtins)
					ft_error(1, "Redirection failed", 0);
				return (-1);
			}
			last_input_fd = temp_fd;
		}
		else
		{
			if (process_output_redirection(file_node, mini) == -1)
			{
				if (last_input_fd != -1)
					close(last_input_fd);
				if (!builtins)
					ft_error(1, "Redirection failed", 0);
				return (-1);
			}
		}
		file_node = file_node->next;
	}
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