/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:08:21 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/23 19:40:41 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Append to existing var or create new one if not exist
 */
int	append_env_var(t_env_list *list, char *variable, char *value)
{
	t_env_node	*existing;
	char		*new_value;
	char		*temp;

	if (!list || !variable || !value)
		return (-1);
	existing = find_env_var(list, variable);
	if (existing && existing->value)
	{
		temp = ft_strjoin(existing->value, value);
		if (!temp)
			return (-1);
		new_value = temp;
		gc_track(new_value, GC_ENV);
		gc_free(existing->value);
		existing->value = new_value;
		return (0);
	}
	else
		return (set_env_var(list, variable, value));
}

/**
 * Remove head node from environment list
 */
static int	remove_head_node(t_env_list *list)
{
	t_env_node	*current;

	current = list->head;
	list->head = current->next;
	if (list->tail == current)
		list->tail = NULL;
	gc_free(current->variable);
	if (current->value)
		gc_free(current->value);
	gc_free(current);
	list->size--;
	return (1);
}

/**
 * Remove non-head node from environment list
 */
static int	remove_other_node(t_env_list *list, t_env_node *prev,
							t_env_node *current)
{
	prev->next = current->next;
	if (list->tail == current)
		list->tail = prev;
	gc_free(current->variable);
	if (current->value)
		gc_free(current->value);
	gc_free(current);
	list->size--;
	return (1);
}

/**
 * Remove an environment variable
 */
int	unset_env_var(t_env_list *list, char *variable)
{
	t_env_node	*current;
	t_env_node	*prev;

	if (!list || !variable || !list->head)
		return (0);
	if (ft_strcmp(list->head->variable, variable) == 0)
		return (remove_head_node(list));
	prev = list->head;
	current = list->head->next;
	while (current)
	{
		if (ft_strcmp(current->variable, variable) == 0)
			return (remove_other_node(list, prev, current));
		prev = current;
		current = current->next;
	}
	return (0);
}

/**
 * Print the environment variables to standard output
 */
void	print_env(t_env_list *list)
{
	t_env_node	*current;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->variable, current->value);
		current = current->next;
	}
}
