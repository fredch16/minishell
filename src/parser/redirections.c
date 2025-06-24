/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 22:39:10 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/23 17:50:30 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_redirect(t_token_node *token)
{
	if (token->type == TK_REDIR_APPEND)
		return (true);
	if (token->type == TK_REDIR_HEREDOC)
		return (true);
	if (token->type == TK_REDIR_IN)
		return (true);
	if (token->type == TK_REDIR_OUT)
		return (true);
	return (false);
}

t_redir_type	get_redir_type(t_token_node *token)
{
	if (token->type == TK_REDIR_APPEND)
		return (REDIR_APPEND);
	if (token->type == TK_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	if (token->type == TK_REDIR_IN)
		return (REDIR_IN);
	if (token->type == TK_REDIR_OUT)
		return (REDIR_OUT);
	return (REDIR_ERROR);
}

void	add_redirection(t_file_list *file_list, t_token_node *redir_token,
	t_token_node *file_token)
{
	t_file_node	*file;

	file = new_file();
	file->redir_type = get_redir_type(redir_token);
	file->filename = ft_strdup(file_token->content);
	gc_track(file->filename, GC_PARSE);
	file->next = NULL;
	file_add_back(file_list, file);
}
