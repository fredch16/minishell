/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:24:52 by apregitz          #+#    #+#             */
/*   Updated: 2025/05/30 17:02:17 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_files(t_cmd_node *cmd_node, t_exec_data *exec_data)
{
	int	hd_flags;
	int	flags;

	hd_flags = O_WRONLY | O_CREAT | O_APPEND;
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (cmd_node->file_list->head->redir_type == REDIR_HEREDOC)
		exec_data->output_file = open(exec_data->av[exec_data->ac - 1], hd_flags, 0777);
	else
	{
		exec_data->input_file = open(exec_data->av[1], O_RDONLY, 0777);
		exec_data->fd[0] = exec_data->input_file;
		exec_data->output_file = open(exec_data->av[exec_data->ac - 1], flags, 0777);
	}
	exec_data->fd[0] = exec_data->input_file;
	return (1);
}
