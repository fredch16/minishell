/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:14:50 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/28 02:07:00 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_token_list *init_token_list(char *input)
{
	t_token_list *list;
	
	list = gc_malloc(sizeof(t_token_list));
	if (!list)
		return NULL;
	list->head = NULL;
	list->tail = NULL;
	list->input = strdup(input); // Store copy of original input
	gc_track(list->input);
	if (!list->input)
	{
		free(list);
		return NULL;
	}
	list->size = 0;
	return (list);
}

bool add_token(t_token_list *list, char *token_str, t_token_type type)
{
	t_token_node *new_node;
	
	if (!list || !token_str)
		return false;
	new_node = gc_malloc(sizeof(t_token_node));
	if (!new_node)
		return false;
	new_node->token = strdup(token_str);
	gc_track(new_node->token);
	if (!new_node->token)
	{
		gc_free(new_node);
		return false;
	}
	new_node->type = type;
	new_node->next = NULL;
	if (list->head == NULL)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		list->tail->next = new_node;
		list->tail = new_node;
	}
	list->size++;
	return true;
}

/* UTILITY: Free token list */
void free_token_list(t_token_list *list)
{
	t_token_node *current, *next;
	
	if (!list)
		return;
	
	current = list->head;
	while (current)
	{
		next = current->next;
		gc_free(current->token);
		gc_free(current);
		current = next;
	}
	
	gc_free(list->input);
	gc_free(list);
}