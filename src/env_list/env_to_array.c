/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:45:00 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 22:50:29 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Cleanup array in case of allocation failure
 * @param array Array to free
 * @param index Index up to which to free
 * @return NULL
 */
static char	**cleanup_env_array(char **array, int index)
{
	while (--index >= 0)
		gc_free(array[index]);
	gc_free(array);
	return (NULL);
}

/**
 * Create environment variable with value (VAR=VALUE)
 * @param var Variable name
 * @param value Variable value
 * @param array Environment array
 * @param index Current index in array
 * @return 1 on success, 0 on failure
 */
static int	create_env_with_value(char *var, char *value,
								char **array, int index)
{
	char	*temp;

	temp = ft_strjoin(var, "=");
	if (!temp)
		return (0);
	gc_track(temp, GC_ENV);
	array[index] = ft_strjoin(temp, value);
	gc_free(temp);
	if (!array[index])
		return (0);
	gc_track(array[index], GC_ENV);
	return (1);
}

/**
 * Create environment variable without value
 * @param var Variable name
 * @param array Environment array
 * @param index Current index in array
 * @return 1 on success, 0 on failure
 */
static int	create_env_no_value(char *var, char **array, int index)
{
	array[index] = ft_strdup(var);
	if (!array[index])
		return (0);
	gc_track(array[index], GC_ENV);
	return (1);
}

/**
 * Convert environment linked list to array of strings
 * @param list Environment list to convert
 * @return NULL-terminated array of environment strings or NULL on failure
 */
char	**env_list_to_array(t_env_list *list)
{
	char		**env_array;
	t_env_node	*current;
	int			i;

	if (!list)
		return (NULL);
	env_array = (char **)gc_malloc(sizeof(char *) * (list->size + 1), GC_ENV);
	if (!env_array)
		return (NULL);
	current = list->head;
	i = 0;
	while (current)
	{
		if (current->value)
		{
			if (!create_env_with_value(current->variable, current->value,
					env_array, i))
				return (cleanup_env_array(env_array, i));
		}
		else if (!create_env_no_value(current->variable, env_array, i))
			return (cleanup_env_array(env_array, i));
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
