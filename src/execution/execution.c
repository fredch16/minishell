/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:34 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/30 16:27:16 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution(t_cmd_list *data, char **envp)
{
	int			exit_code;
	t_exec_data	exec_data;
	t_cmd_node	*cmd_node;

	exec_data.ep = envp;
	cmd_node = data->head;
	while (cmd_node->next)
	{
		build_child(cmd_node, &exec_data);
		cmd_node->next = cmd_node->next->next;
	}
	while (wait(&exit_code) > 0)
		;
	if (WIFEXITED(exit_code))
		return (WEXITSTATUS(exit_code));
	return (0);
}
