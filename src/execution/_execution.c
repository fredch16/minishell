/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:34 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/09 15:39:00 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	execution(t_mini *mini)
// {
// 	int			exit_code;
// 	t_cmd_node	*cmd_node;

// 	if (!mini->cmd_list.head)
// 		return (0);
// 	init_exec_data(mini);
// 	cmd_node = mini->cmd_list.head;
// 	while (cmd_node)
// 	{
// 		cmd_node = cmd_node->next;
// 	}
// 	exit_code = execute_pipeline(mini);
// 	free_2d_array(mini->exec_data.ep);
// 	return (exit_code);
// }

int	execution(t_mini *mini)
{
	// int	exit_code;

	if (!mini->cmd_list || !mini->cmd_list->head)
		return (0);
	setup_parent_signals_for_execution();
	init_exec_data(mini);
	execute_pipeline(mini);
	return (mini->exit_code);
}
