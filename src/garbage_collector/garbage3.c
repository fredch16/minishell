/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:35:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/23 20:36:23 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Free a head node from the garbage collection list
 * @param llist Garbage collection list
 * @return 1 after successful freeing
 */
static int	free_head_node(t_garbage_list *llist)
{
	t_garbage_node	*current;

	current = llist->head;
	llist->head = llist->head->next;
	if (!llist->head)
		llist->tail = NULL;
	free(current->ptr);
	free(current);
	llist->size--;
	return (1);
}

/**
 * Free a node that is not the head from the garbage collection list
 * @param llist Garbage collection list
 * @param ptr Pointer to find and free
 * @return 1 if freed, 0 if not found
 */
static int	free_other_node(t_garbage_list *llist, void *ptr)
{
	t_garbage_node	*current;
	t_garbage_node	*prev;

	prev = llist->head;
	current = llist->head->next;
	while (current)
	{
		if (current->ptr == ptr)
		{
			prev->next = current->next;
			if (current == llist->tail)
				llist->tail = prev;
			free(current->ptr);
			free(current);
			llist->size--;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

/**
 * Free a specific pointer from the garbage collection list
 * @param ptr Pointer to free
 * @return 1 if freed, 0 if not found
 */
int	gc_free(void *ptr)
{
	t_garbage_list	*llist;

	llist = get_gc_data();
	if (!ptr || !llist->head)
		return (0);
	if (llist->head->ptr == ptr)
		return (free_head_node(llist));
	return (free_other_node(llist, ptr));
}

/**
 * Free all allocated memory in the garbage collection list
 */
void	gc_free_all(void)
{
	t_garbage_node	*tmp;
	t_garbage_node	*curr;
	t_garbage_list	*llist;

	llist = get_gc_data();
	curr = llist->head;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->ptr);
		free(tmp);
	}
	llist->head = NULL;
	llist->tail = NULL;
	llist->size = 0;
}
