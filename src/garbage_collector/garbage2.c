/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:53:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/23 19:55:51 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Free a garbage node and update pointers
 * @param prev Previous node in the list or NULL if at head
 * @param node Node to free
 * @return Next node to process
 */
t_garbage_node	*free_gc_node(t_garbage_node *prev, t_garbage_node *node)
{
	t_garbage_node	*next;
	t_garbage_list	*llist;

	llist = get_gc_data();
	next = node->next;
	if (prev)
		prev->next = next;
	else
		llist->head = next;
	if (node == llist->tail)
		llist->tail = prev;
	free(node->ptr);
	free(node);
	llist->size--;
	return (next);
}

// /**
//  * Skip to the next node in the list
//  * @param prev Pointer to update with current node
//  * @param current Current node to advance from
//  * @return Next node to process
//  */
// static t_garbage_node	*skip_gc_node(t_garbage_node **prev,
// 									t_garbage_node *current)
// {
// 	*prev = current;
// 	return (current->next);
// }

/**
 * Free all garbage collection nodes of specified type
 * @param type Type of memory to free
 */
void	gc_free_by_type(t_gc_type type)
{
	t_garbage_node	*current;
	t_garbage_node	*prev;
	t_garbage_list	*llist;

	llist = get_gc_data();
	current = llist->head;
	prev = NULL;
	while (current)
	{
		if (current->type == type)
			current = free_gc_node(prev, current);
		else
		{
			prev = current;
			current = current->next;
		}
	}
}
