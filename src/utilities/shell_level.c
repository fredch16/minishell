/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:02:20 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/25 12:33:37 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	increase_shlvl(t_mini *mini)
{
	t_env_node	*node;
	int			lvl;

	node = mini->env_list->head;
	while (node)
	{
		if (ft_strcmp(node->variable, "SHLVL") == 0)
		{
			lvl = ft_atoi(node->value);
			gc_free(node->value);
			node->value = ft_itoa(++lvl);
			if (!node->next)
				ft_error(1, "malloc", EC_FD | EC_GC);
			gc_track(node->value, GC_ENV);
			return (0);
		}
		node = node->next;
	}
	return (1);
}
