/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _execution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:29:32 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/23 17:29:43 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execution(t_mini *mini)
{
	if (!mini->cmd_list || !mini->cmd_list->head)
		return (0);
	setup_parent_signals_for_execution();
	init_exec_data(mini);
	if (create_heredoc_list(mini) == -1)
	{
		reset_parent_signals();
		gc_free_by_type(GC_EXEC);
		return (mini->exit_code);
	}
	mini->exit_code = execute_pipeline(mini);
	gc_free_by_type(GC_EXEC);
	return (mini->exit_code);
}
