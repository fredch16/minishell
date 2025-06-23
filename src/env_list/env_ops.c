/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:25:20 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/23 16:08:11 by fredchar         ###   ########.fr       */
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
		if (!ft_strncmp(current->variable, variable, ft_strlen(variable)))
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
 */
static int	update_env_var(t_env_node *existing, char *value)
{
	char	*new_value;

	if (value)
	{
		new_value = ft_strdup(value);
		if (!new_value)
			return (-1);
		gc_track(new_value, GC_ENV);
		if (existing->value)
			gc_free(existing->value);
		existing->value = new_value;
	}
	else
	{
		if (existing->value)
			gc_free(existing->value);
		existing->value = NULL;
	}
	return (0);
}

/**
 * Add a new environment variable
 */
static int	add_new_env_var(t_env_list *list, char *variable, char *value)
{
	t_env_node	*new_node;

	new_node = create_env_node(variable, value);
	if (!new_node)
		return (-1);
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
