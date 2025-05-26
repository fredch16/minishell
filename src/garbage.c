/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:39:48 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/26 23:50:41 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

static	t_garbage_node *gc_list = NULL;

/**
 * Allocate memory and track it for automatic cleanup
 * @param size Size of memory to allocate
 * @return Pointer to allocated memory or NULL on failure
 */
void	*gc_malloc(size_t size)
{
	void			*ptr;
	t_garbage_node	*new_node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	new_node->ptr = ptr;
	new_node->next = gc_list;
	gc_list = new_node;
	return (ptr);
}

/**
 * Free a specific pointer from the garbage collection list
 * @param ptr Pointer to free
 * @return 1 if freed, 0 if not found
 */
int	gc_free(void *ptr)
{
	t_garbage_node	*current;
	t_garbage_node	*prev;

	if (!ptr || !gc_list)
		return (0);
	if (gc_list->ptr == ptr)
	{
		current = gc_list;
		gc_list = gc_list->next;
		free(current->ptr);
		free(current);
		return (1);
	}
	prev = gc_list;
	current = gc_list->next;
	while (current)
	{
		if (current->ptr == ptr)
		{
			prev->next = current->next;
			free(current->ptr);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

/**
 * Free all allocated memory in the garbage collection list
 */
void	gc_free_all(void)
{
	t_garbage_node	*tmp;

	while (gc_list)
	{
		tmp = gc_list;
		gc_list = gc_list->next;
		free(tmp->ptr);
		free(tmp);
	}
	gc_list = NULL;  // Ensure we reset the list to empty
}