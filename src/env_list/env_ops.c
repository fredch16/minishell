/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:25:20 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/09 16:08:41 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Look up an environment variable in the list
 * @param list Environment list to search
 * @param variable Variable name to find
 * @return Pointer to node if found, NULL otherwise
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
 * @param list Environment list
 * @param variable Name of variable to look up
 * @return Value of variable or NULL if not found
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
 * Add or update an environment variable
 * @param list Environment list
 * @param variable Variable name
 * @param value Variable value (can be NULL)
 * @return 0 on success, -1 on failure
 */
int	set_env_var(t_env_list *list, char *variable, char *value)
{
	t_env_node	*existing;
	t_env_node	*new_node;
	char		*new_value;
	
	if (!list || !variable)
		return (-1);
		
	existing = find_env_var(list, variable);
	if (existing)
	{
		// Update existing variable
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
	else
	{
		// Add new variable
		new_node = create_env_node(variable, value);
		if (!new_node)
			return (-1);
			
		add_env_node(list, new_node);
		return (0);
	}
}

/**
 * Append value to an existing environment variable or set if not found
 * @param list Environment list
 * @param variable Variable name
 * @param value Value to append (can be NULL)
 * @return 0 on success, -1 on failure
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
		// Append to existing variable
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
	{
		// Set new variable if not found
		return (set_env_var(list, variable, value));
	}
}

/**
 * Remove an environment variable
 * @param list Environment list
 * @param variable Name of variable to remove
 * @return 1 if removed, 0 if not found or error
 */
int	unset_env_var(t_env_list *list, char *variable)
{
	t_env_node	*current;
	t_env_node	*prev;
	
	if (!list || !variable || !list->head)
		return (0);
		
	// Check if it's the head node
	if (ft_strncmp(list->head->variable, variable, ft_strlen(variable)) == 0)
	{
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
	
	// Search through the rest of the list
	prev = list->head;
	current = list->head->next;
	while (current)
	{
		if (ft_strncmp(current->variable, variable, ft_strlen(variable)) == 0)
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
		prev = current;
		current = current->next;
	}
	
	return (0);
}

/**
 * Print the environment variables to standard output
 * @param list Environment list to print
 */
void	print_env(t_env_list *list)
{
	t_env_node	*current;

	if (!list)
		return;
		
	current = list->head;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->variable, current->value);
		current = current->next;
	}
}
