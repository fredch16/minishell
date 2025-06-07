/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:39:48 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/07 14:57:33 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_garbage_list	*get_gc_data(void)
{
	static t_garbage_list	llist = {NULL, NULL, 0};

	return (&llist);
}

/**
 * Allocate memory and track it for automatic cleanup
 * @param size Size of memory to allocate
 * @return Pointer to allocated memory or NULL on failure
 */
void	*gc_malloc(size_t size, t_gc_type type)
{
	void			*ptr;
	t_garbage_node	*new_node;
	t_garbage_list	*llist;

	llist = get_gc_data();
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
		return (free(ptr), NULL);
	new_node->ptr = ptr;
	new_node->next = NULL;
	new_node->type = type;
	if (!llist->head)
	{
		llist->head = new_node;
		llist->tail = new_node;
	}
	else
	{
		llist->tail->next = new_node;
		llist->tail = new_node;
	}
	llist->size++;
	return (ptr);
}

int	gc_track(void *ptr, t_gc_type type)
{
	t_garbage_node	*new_node;
	t_garbage_list	*llist;

	llist = get_gc_data();
	if (!ptr)
		return (0);
	new_node = malloc(sizeof(t_garbage_node));
	if (!new_node)
		return (0);
	new_node->ptr = ptr;
	new_node->next = NULL;
	new_node->type = type;
	if (!llist->head)
	{
		llist->head = new_node;
		llist->tail = new_node;
	}
	else
	{
		llist->tail->next = new_node;
		llist->tail = new_node;
	}
	llist->size++;
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
	t_garbage_list	*llist;

	llist = get_gc_data();
	if (!ptr || !llist->head)
		return (0);
	if (llist->head->ptr == ptr)
	{
		current = llist->head;
		llist->head = llist->head->next;
		if (!llist->head)
			llist->tail = NULL;
		llist->size--;
		return (free(current->ptr), free(current), 1);
	}
	prev = llist->head;
	current = llist->head->next;
	while (current)
	{
		if (current->ptr == ptr)
		{
			prev->next = current->next;
			if (current == llist->tail)
				llist->tail = prev;
			llist->size--;
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
		prev->next = node->next;
	else
		llist->head = node->next;
	if (node == llist->tail)
		llist->tail = prev;
	free(node->ptr);
	free(node);
	llist->size--;
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
	t_garbage_list	*llist;

	llist = get_gc_data();
	current = llist->head;
	prev = NULL;
	while (current)
	{
		if (current->type == type)
			current = free_gc_node(prev, current);
		else
			current = skip_gc_node(&prev, current);
	}
}