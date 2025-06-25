/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:28 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/25 11:39:42 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Swap two node pointers in the array
 * @param arr Array of node pointers
 * @param i First index
 * @param j Second index
 */
static void	swap_nodes(t_env_node **arr, int i, int j)
{
	t_env_node	*temp;

	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

/**
 * Create a sorted array of environment nodes
 * @param env_list Environment list to sort
 * @return Array of sorted node pointers, NULL on error
 */
static t_env_node	**create_sorted_env_array(t_env_list *env_list)
{
	t_env_node	**sorted;
	t_env_node	*node;
	size_t		i;
	size_t		j;

	sorted = gc_malloc(sizeof(t_env_node *) * (env_list->size + 1), GC_EXEC);
	node = env_list->head;
	i = 0;
	while (node)
	{
		sorted[i++] = node;
		node = node->next;
	}
	sorted[i] = NULL;
	i = -1;
	while (++i < env_list->size - 1)
	{
		j = -1;
		while (++j < env_list->size - i - 1)
		{
			if (ft_strcmp(sorted[j]->variable, sorted[j + 1]->variable) > 0)
				swap_nodes(sorted, j, j + 1);
		}
	}
	return (sorted);
}

/**
 * Print environment variable in "declare -x" format
 * @param node Environment node to print
 */
static void	print_declare_format(t_env_node *node)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(node->variable, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	if (node->value)
		ft_putstr_fd(node->value, STDOUT_FILENO);
	ft_putstr_fd("\"", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

/**
 * Print environment variables in sorted order with declare -x format
 * @param env_list Environment list to print
 * @return 0 on success, 1 on error
 */
int	export_no_arg(t_env_list *env_list)
{
	t_env_node	**sorted_env;
	int			i;

	if (!env_list || env_list->size == 0)
		return (0);
	sorted_env = create_sorted_env_array(env_list);
	if (!sorted_env)
		return (1);
	i = 0;
	while (sorted_env[i])
	{
		print_declare_format(sorted_env[i]);
		i++;
	}
	return (0);
}
