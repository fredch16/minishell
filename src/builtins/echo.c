/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 00:18:49 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/04 00:30:32 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo_builtin(char **args)
{
	int	nl_flag;
	int	i;

	nl_flag = 0;
	i = 1;
	if (args[i] && !ft_strcmp(args[i], "-n"))
	{
		nl_flag = 1;
		i++;
	}
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
