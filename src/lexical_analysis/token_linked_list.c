/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:14:50 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/01 16:59:32 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_token_list *init_token_list(t_mini *mini, char *input)
{
	t_token_list *list;
	
	list = gc_malloc(sizeof(t_token_list), GC_PARSE);
	if (!list)
		return NULL;
	list->head = NULL;
	list->tail = NULL;
	list->input = ft_strdup(input); // Store copy of original input
	gc_track(list->input, GC_PARSE);
	if (!list->input)
	{
		free(list);
		return NULL;
	}
	list->size = 0;
	list->exit_code = mini->exit_code;
	list->env = mini->env_list;
	list->error_code = mini->error_code;
	return (list);
}

t_token_node	*new_token(void)
{
	t_token_node	*new_token;

	new_token = (t_token_node *)ft_calloc(1, sizeof(t_token_node));
	if (new_token == NULL)
		return (perror("New token failed to malloc\n"), NULL);
	gc_track(new_token, GC_PARSE);
	return (new_token);
}

void	token_add_back(t_token_list *token_list, t_token_node *new_token)
{
	if (token_list->head == NULL)
	{
		token_list->head = new_token;
		token_list->tail = new_token;
		token_list->size = 1;
	}
	else
	{
		token_list->tail->next = new_token;
		token_list->tail = new_token;
		token_list->size++;
	}
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
		gc_free(current->content);
		gc_free(current);
		current = next;
	}
	
	gc_free(list->input);
	gc_free(list);
}
