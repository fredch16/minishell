/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:39:48 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 22:32:36 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_garbage_node	*g_gc_list = NULL;

/**
 * Allocate memory and track it for automatic cleanup
 * @param size Size of memory to allocate
 * @return Pointer to allocated memory or NULL on failure
 */
void	*gc_malloc(size_t size, t_gc_type type)
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
	new_node->next = g_gc_list;
	new_node->type = type;
	g_gc_list = new_node;
	return (ptr);
}

int	gc_track(void *ptr, t_gc_type type)
{
	t_garbage_node	*new_node;

	if (!ptr)
		return (0);
	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
		return (0);
	new_node->ptr = ptr;
	new_node->next = g_gc_list;
	new_node->type = type;
	g_gc_list = new_node;
	return (1);
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

	if (!ptr || !g_gc_list)
		return (0);
	if (g_gc_list->ptr == ptr)
	{
		current = g_gc_list;
		g_gc_list = g_gc_list->next;
		return (free(current->ptr), free(current), 1);
	}
	prev = g_gc_list;
	current = g_gc_list->next;
	while (current)
	{
		if (current->ptr == ptr)
		{
			prev->next = current->next;
			return (free(current->ptr), free(current), 1);
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

	while (g_gc_list)
	{
		tmp = g_gc_list;
		g_gc_list = g_gc_list->next;
		free(tmp->ptr);
		free(tmp);
	}
	g_gc_list = NULL;
}

/**
 * Free a garbage node and update pointers
 * @param prev Previous node in the list or NULL if at head
 * @param node Node to free
 * @return Next node to process
 */
t_garbage_node	*free_gc_node(t_garbage_node *prev, t_garbage_node *node)
{
	t_garbage_node	*next;

	if (prev)
		prev->next = node->next;
	else
		g_gc_list = node->next;
	if (prev)
		next = prev->next;
	else
		next = g_gc_list;
	free(node->ptr);
	free(node);
	return (next);
}

/**
 * Skip to the next node in the list
 * @param prev Pointer to update with current node
 * @param current Current node to advance from
 * @return Next node to process
 */
static t_garbage_node	*skip_gc_node(t_garbage_node **prev,
									t_garbage_node *current)
{
	*prev = current;
	return (current->next);
}

/**
 * Free all garbage collection nodes of specified type
 * @param type Type of memory to free
 */
void	gc_free_by_type(t_gc_type type)
{
	t_garbage_node	*current;
	t_garbage_node	*prev;

	current = g_gc_list;
	prev = NULL;
	while (current)
	{
		if (current->type == type)
			current = free_gc_node(prev, current);
		else
			current = skip_gc_node(&prev, current);
	}
}
