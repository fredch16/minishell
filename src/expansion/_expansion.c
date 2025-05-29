/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expansion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:09:07 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/30 01:22:25 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expansion.h"
#include "../../include/parser.h"


void	expansion(t_token_list *token_list)
{
	t_token_node *current;

	if (!token_list || !token_list->head)
	{
		printf("Token list is empty or NULL");
		return ;
	}
	current = token_list->head;
	while (current)
	{
		if (current->type == TK_CMD)
			expand_command_token(token_list, current);
		// if (current->type == TK_S_QUOTES)
		// 	expand_squote_token(token_list, current);
		current = current->next;
	}
}