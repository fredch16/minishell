/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expansion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:09:07 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/01 16:09:12 by fredchar         ###   ########.fr       */
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
		expand_token(token_list, current);
		// remove quotes and handle them if needed
		current = current->next;
	}
}