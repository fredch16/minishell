/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:25:20 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/25 14:55:36 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Look up an environment variable in the list
 */
t_env_node	*find_env_var(t_env_list *list, char *variable)
{
	t_env_node	*current;

	if (!list || !variable)
		return (NULL);
	current = list->head;
	while (current)
	{
		if (!ft_strcmp(current->variable, variable))
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * Get value of an environment variable
 */
char	*get_env_value(t_env_list *list, char *variable)
{
	t_env_node	*node;

	node = find_env_var(list, variable);
	if (node)
		return (node->value);
	return (NULL);
}

/**
 * Update an existing environment variable
 * Always sets a value (empty string if NULL is passed)
 */
static int	update_env_var(t_env_node *existing, char *value)
{
	char	*new_value;

	if (existing->value)
		gc_free(existing->value);
	if (!value)
		new_value = NULL;
	else
	{
		new_value = ft_strdup(value);
		if (!new_value)
			destroy_minishell(999);
		gc_track(new_value, GC_ENV);
	}
	existing->value = new_value;
	return (0);
}

/**
 * Add a new environment variable
 * Always sets a value (empty string if NULL is passed)
 */
static int	add_new_env_var(t_env_list *list, char *variable, char *value)
{
	t_env_node	*new_node;
	char		*var_copy;
	char		*val_copy;

	var_copy = ft_strdup(variable);
	if (!var_copy)
		destroy_minishell(999);
	gc_track(var_copy, GC_ENV);
	if (!value)
		val_copy = NULL;
	else
	{
		val_copy = ft_strdup(value);
		if (!val_copy)
			destroy_minishell(999);
		gc_track(val_copy, GC_ENV);
	}
	new_node = gc_malloc(sizeof(t_env_node), GC_ENV);
	new_node->variable = var_copy;
	new_node->value = val_copy;
	new_node->next = NULL;
	add_env_node(list, new_node);
	return (0);
}

/**
 * Add or update an environment variable
 */
int	set_env_var(t_env_list *list, char *variable, char *value)
{
	t_env_node	*existing;

	if (!list || !variable)
		return (-1);
	existing = find_env_var(list, variable);
	if (existing)
		return (update_env_var(existing, value));
	else
		return (add_new_env_var(list, variable, value));
}
