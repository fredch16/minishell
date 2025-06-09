/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:18:49 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/09 17:14:31 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	only_flag(char *arg, int *is_flag)
{
	int	i;

	i = 1;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
	{
		*is_flag = 1;
		return (1);
	}
	return (0);
}

static int	is_flag(char **args, int *is_flag)
{
	int	i;

	i = 1;
	while (args[i] && args[i][0] == '-' && only_flag(args[i], is_flag))
		i++;
	return (i);
}

int	echo_builtin(char **args)
{
	int	nl_flag;
	int	i;

	nl_flag = 0;
	i = is_flag(args, &nl_flag);
	while (args[i])
	{
		write(1, args[i], strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!nl_flag)
		write(1, "\n", 1);
	return (0);
}
