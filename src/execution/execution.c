/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:34 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/03 10:45:01 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution(t_mini *mini)
{
	int			exit_code;
	t_cmd_node	*cmd_node;

	if (!mini->cmd_list->head)
		return (0);
	init_exec_data(mini);
	cmd_node = mini->cmd_list->head;
	while (cmd_node)
	{
		cmd_node->path = get_command_path(cmd_node, mini);
		if (!cmd_node->path)
		{
			fprintf(stderr, "minishell: %s: command not found\n", cmd_node->cmd[0]);
			cmd_node = cmd_node->next;
			continue ;
		}
		// printf("%s\n", cmd_node->cmd[0]);
		setup_exec(cmd_node, mini);
		cmd_node = cmd_node->next;
	}
	while (wait(&exit_code) > 0)
		;
	free_2d_array(mini->exec_data.ep);
	return (WEXITSTATUS(exit_code));
}
