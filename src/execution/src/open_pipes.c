/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:31:33 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/30 17:32:01 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipes(t_cmd_node *cmd_node, t_exec_data *exec_data)
{
	int	fd[2];

	if (cmd_node->next && pipe(fd) == -1)
		error();
	if (!cmd_node->next)
		exec_data->fd[1] = exec_data->output_file;
	else
		exec_data->fd[1] = fd[1];
	exec_cmd(cmd_node, exec_data);
	close(exec_data->fd[0]);
	if (!cmd_node->next)
		close(exec_data->fd[1]);
	else
	{
		close(fd[1]);
		exec_data->fd[0] = fd[0];
	}
}


