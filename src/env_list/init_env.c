/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:41:59 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/23 16:07:38 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Initialize an empty environment variable list
 * @return Pointer to new list or NULL on failure
 */
t_env_list	*init_env_list(void)
{
	t_env_list	*list;

	list = (t_env_list *)gc_malloc(sizeof(t_env_list), GC_ENV);
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

/**
 * Create a new env node with given variable and value
 * @param variable Environment variable name
 * @param value Environment variable value
 * @return Pointer to new node or NULL on failure
 */
t_env_node	*create_env_node(char *variable, char *value)
{
	t_env_node	*new_node;

	new_node = (t_env_node *)gc_malloc(sizeof(t_env_node), GC_ENV);
	new_node->variable = ft_strdup(variable);
	if (!new_node->variable)
		return (gc_free(new_node), NULL);
	gc_track(new_node->variable, GC_ENV);
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (NULL);
		gc_track(new_node->value, GC_ENV);
	}
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

/**
 * Parse an environment string into variable and value
 * @param env_str String in format "VARIABLE=value"
 * @param variable Output pointer for variable part
 * @param value Output pointer for value part
 * @return 1 on success, 0 on failure
 */
int	parse_env_string(char *env_str, char **variable, char **value)
{
	char	*equals_pos;

	if (!env_str || !variable || !value)
		return (0);
	equals_pos = ft_strchr(env_str, '=');
	if (!equals_pos)
	{
		*variable = ft_strdup(env_str);
		*value = NULL;
		return (*variable != NULL);
	}
	*variable = ft_substr(env_str, 0, equals_pos - env_str);
	if (!*variable)
		return (0);
	*value = ft_strdup(equals_pos + 1);
	if (!*value)
	{
		free(*variable);
		*variable = NULL;
		return (0);
	}
	return (1);
}

/**
 * Add a node to the end of environment list
 * @param list Target environment list
 * @param node Node to add
 */
void	add_env_node(t_env_list *list, t_env_node *node)
{
	if (!list || !node)
		return ;
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}

/**
 * Convert environment array to linked list structure
 * @param env NULL-terminated array of environment strings
 * @return Pointer to populated list or NULL on failure
 */
t_env_list	*env_array_to_list(char **env)
{
	t_env_list	*list;
	t_env_node	*node;
	char		*variable;
	char		*value;
	int			i;

	if (!env)
		return (NULL);
	list = init_env_list();
	if (!list)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (parse_env_string(env[i], &variable, &value))
		{
			node = create_env_node(variable, value);
			if (node)
				add_env_node(list, node);
			free(variable);
			free(value);
		}
		i++;
	}
	return (list);
}
