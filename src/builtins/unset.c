/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:00:33 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/10 00:22:51 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset_builtin(t_env_list *env_list, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_env_var(env_list, args[i++]);
	}
	return (0);
}