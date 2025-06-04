/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:49:28 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/04 06:10:34 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_child_input(t_mini *mini)
{
	if (mini->exec_data.input_file != STDIN_FILENO)
	{
		if (dup2(mini->exec_data.input_file, STDIN_FILENO) == -1)
			ft_error(1, "dup2");
		close(mini->exec_data.input_file);
	}
}

void	setup_child_output(t_mini *mini)
{
	if (mini->exec_data.output_file != STDOUT_FILENO)
	{
		if (dup2(mini->exec_data.output_file, STDOUT_FILENO) == -1)
			ft_error(1, "dup2");
		close(mini->exec_data.output_file);
	}
}
