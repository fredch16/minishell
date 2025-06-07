/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:20:04 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/07 16:41:08 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	process_redirection(t_file_node *file_node, t_mini *mini)
{
	if (file_node->redir_type == REDIR_IN)
		return (handle_input_redir(file_node, mini));
	if (file_node->redir_type == REDIR_OUT)
		return (handle_output_redir(file_node, mini));
	if (file_node->redir_type == REDIR_APPEND)
		return (handle_append_redir(file_node, mini));
	if (file_node->redir_type == REDIR_HEREDOC)
		return (handle_heredoc_redir(file_node->filename, mini));
	return (0);
}

int	handle_redirections(t_cmd_node *cmd_node, t_mini *mini)
{
	t_file_node	*file_node;

	if (!cmd_node->files || !cmd_node->files->head)
		return (0);
	file_node = cmd_node->files->head;
	while (file_node)
	{
		if (process_redirection(file_node, mini) == -1)
			return (-1);
		file_node = file_node->next;
	}
	return (0);
}
