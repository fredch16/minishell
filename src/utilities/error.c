/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:05:02 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 22:42:43 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tk_err(t_token_list *token_list, int error_code)
{
	token_list->error_code = error_code;
}

int	check_syntax_errors(t_token_list *token_list)
{
	t_token_node	*current;

	current = token_list->head;
	if (!current)
		return (0);
	if (current->type == TK_PIPE)
		return (tk_err(token_list, EC_PIPE_AT_START), EC_PIPE_AT_START);
	while (current)
	{
		if (current->type == TK_PIPE)
		{
			if (!current->next || current->next->type == TK_PIPE)
				return (tk_err(token_list, EC_SYNTAX_PIPE), EC_SYNTAX_PIPE);
		}
		else if (is_redirect(current))
		{
			if (!current->next || current->next->type != TK_CMD)
				return (tk_err(token_list, EC_SYNTAX_REDIR), EC_SYNTAX_REDIR);
		}
		current = current->next;
	}
	current = token_list->tail;
	if (current && current->type == TK_PIPE)
		return (tk_err(token_list, EC_PIPE_AT_END), EC_PIPE_AT_END);
	return (0);
}

int	handle_error(t_mini *mini)
{
	if (!mini->token_list->error_code)
		return (0);
	else if (mini->token_list->error_code == EC_UNCLOSEQ)
		return (printf("Error: %s\n", ERR_UNCLOSED_QUOTE),
		gc_free_by_type(GC_PARSE), -1);
	else if (mini->token_list->error_code == EC_PIPE_AT_START)
		return (printf("Error: %s\n", ERR_PIPE_AT_START),
		gc_free_by_type(GC_PARSE), -1);
	else if (mini->token_list->error_code == EC_SYNTAX_PIPE)
		return (printf("Error: %s\n", ERR_SYNTAX_PIPE),
		gc_free_by_type(GC_PARSE), -1);
	else if (mini->token_list->error_code == EC_SYNTAX_REDIR)
		return (printf("Error: %s\n", ERR_SYNTAX_REDIR),
		gc_free_by_type(GC_PARSE), -1);
	else if (mini->token_list->error_code == EC_PIPE_AT_END)
		return (printf("Error: %s\n", ERR_PIPE_AT_END),
		gc_free_by_type(GC_PARSE), -1);
	else if (mini->token_list->error_code == EC_MALLOC)
		return (printf("Error: %s\n", ERR_MALLOC),
		gc_free_by_type(GC_PARSE), -1);
	return (0);
}

bool	g2g(t_token_list *list)
{
	if (list->error_code)
		return (false);
	return (true);
}
