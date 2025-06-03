/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:31:44 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/03 07:06:06 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_cmd_node *cmd_node, t_mini *mini)
{
	setup_child_input(mini);
	setup_child_output(mini);
	if (handle_redirections(cmd_node, mini) == -1)
		ft_error(1, NULL);
	execve(cmd_node->path, cmd_node->cmd, mini->exec_data.ep);
	ft_error(127, "execve");
}

void	setup_exec(t_cmd_node *cmd_node, t_mini *mini)
{
	pid_t	pid;

	if (cmd_node->next && pipe(cmd_node->fd) == -1)
		ft_error(1, "pipe");
	pid = fork();
	if (pid == -1)	
		ft_error(1, "fork");
	if (pid == 0)
		exec_cmd(cmd_node, mini);
}
