/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:39:48 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/23 20:36:15 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Get the global garbage collector list
 */
t_garbage_list	*get_gc_data(void)
{
	static t_garbage_list	llist = {NULL, NULL, 0};

	return (&llist);
}

/**
 * Create a new garbage collection node
 * @param ptr Pointer to track
 * @param type Type of memory
 * @return New garbage node or NULL on failure
 */
static t_garbage_node	*create_gc_node(void *ptr, t_gc_type type)
{
	t_garbage_node	*new_node;

	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
		destroy_minishell(999);
	new_node->ptr = ptr;
	new_node->next = NULL;
	new_node->type = type;
	return (new_node);
}

/**
 * Add a node to the garbage collection list
 * @param node Node to add to the list
 */
static void	add_gc_node(t_garbage_node *node)
{
	t_garbage_list	*llist;

	llist = get_gc_data();
	if (!llist->head)
	{
		llist->head = node;
		llist->tail = node;
	}
	else
	{
		llist->tail->next = node;
		llist->tail = node;
	}
	llist->size++;
}

/**
 * Allocate memory and track it for automatic cleanup
 * @param size Size of memory to allocate
 * @param type Type of memory for selective cleanup
 * @return Pointer to allocated memory or NULL on failure
 */
void	*gc_malloc(size_t size, t_gc_type type)
{
	void			*ptr;
	t_garbage_node	*new_node;

	ptr = malloc(size);
	if (!ptr)
		destroy_minishell(999);
	new_node = create_gc_node(ptr, type);
	add_gc_node(new_node);
	return (ptr);
}

/**
 * Track an existing pointer in the garbage collector
 * @param ptr Pointer to track
 * @param type Memory type for selective cleanup
 * @return 1 on success, 0 on failure
 */
int	gc_track(void *ptr, t_gc_type type)
{
	t_garbage_node	*new_node;

	if (!ptr)
		return (0);
	new_node = create_gc_node(ptr, type);
	add_gc_node(new_node);
	return (1);
}
