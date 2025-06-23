/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:57 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/23 15:50:36 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	valid_set(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9')
				|| (i == 0 && (str[i] == '-' || str[i] == '+'))))
			return (1);
		i++;
	}
	return (0);
}

static int	get_exit_code(const char *str)
{
	unsigned char	exit_code;
	int				sign;

	sign = 1;
	if (*str == '+' || *str == '-')
		sign = 1 - 2 * (*str++ == '-');
	exit_code = 0;
	while (*str >= '0' && *str <= '9')
		exit_code = (exit_code * 10) + ((*str++ - '0') * sign);
	return (exit_code);
}

int	exit_minishell(t_cmd_node *cmd_node)
{
	int	i;

	i = 0;
	while (cmd_node->cmd[i])
		i++;
	if (i > 2)
		return (perror("too many struments"), 255);
	if (i == 1)
		exit(0);
	else if (valid_set(cmd_node->cmd[1]) == 1)
	{
		reverting_stds();
		gc_free_all();
		exit(255);
	}
	i = get_exit_code(cmd_node->cmd[1]);
	reverting_stds();
	gc_free_all();
	exit(i);
}
