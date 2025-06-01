/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_linked_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:14:50 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/01 21:50:59 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_file_list *init_file_list(t_mini *mini, char *input)
{
	t_file_list *list;
	
	(void)input;
	(void)mini;
	list = gc_malloc(sizeof(t_file_list), GC_PARSE);
	if (!list)
		return NULL;
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

t_file_node	*new_file(void)
{
	t_file_node	*new_file;

	new_file = (t_file_node *)ft_calloc(1, sizeof(t_file_node));
	if (new_file == NULL)
		return (perror("New file failed to malloc\n"), NULL);
	gc_track(new_file, GC_PARSE);
	return (new_file);
}

void	file_add_back(t_file_list *file_list, t_file_node *new_file)
{
	if (file_list->head == NULL)
	{
		file_list->head = new_file;
		file_list->tail = new_file;
		file_list->size = 1;
	}
	else
	{
		file_list->tail->next = new_file;
		file_list->tail = new_file;
		file_list->size++;
	}
}
