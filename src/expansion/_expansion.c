/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expansion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:09:07 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 21:42:15 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expansion.h"
#include "../../include/parser.h"

void	expand_token(t_token_list *token_list, t_token_node *current)
{
	current->content = expand_dollar_vars(token_list, current->content);
	if (token_list->error_code)
		return ;
	current->content = expand_dollar_qmark(token_list, current->content);
	current->content = remove_quotes(token_list, current->content);
}

void	expansion(t_token_list *token_list)
{
	t_token_node	*current;

	if (!token_list || !token_list->head)
	{
		printf("Token list is empty or NULL");
		return ;
	}
	current = token_list->head;
	while (current && !token_list->error_code)
	{
		expand_token(token_list, current);
		if (current->type == TK_S_QUOTES)
			current->type = TK_CMD;
		current = current->next;
	}
}
