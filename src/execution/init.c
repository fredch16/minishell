/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:41:24 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/04 06:53:36 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_exec_data(t_mini *mini)
{
	mini->exec_data.ep = env_list_to_array(mini->env_list);
	mini->exec_data.input_file = STDIN_FILENO;
	mini->exec_data.output_file = STDOUT_FILENO;
}
