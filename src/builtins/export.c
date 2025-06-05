/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:49:35 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/05 16:11:20 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	trust_but_verify(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]))
	{
		ft_printf("export: not an identifier: %c\n", arg[i]);
		return (-1);
	}
	if ((!ft_isalpha(arg[i]) && (arg[i] != '_')))
	{
		ft_printf("export: not valid in this context: %c\n", arg[i]);
		return (-1);

	}
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=' && arg[i + 1])
		return (i);
	return (-1);
}

int	export_builtin(t_env_list *env_list, char **args)
{
	char	*var;
	char	*val;
	int		i;
	int		posequals;
	
	i = 1;
	// in theory this should actually print them in alphabetical order with a prefix
	if (!args[i])
		print_env(env_list);
	while (args[i])
	{
		posequals = trust_but_verify(args[i]);
		if (posequals < 0)
			return (1);
		var = ft_substr(args[i], 0, posequals);
		if (!var)
			return (ft_printf("Malloc failed\n" -1));
		gc_track(var, GC_EXEC);
		val = ft_strdup(args[i] + posequals + 1);
		if (!val)
			return (ft_printf("Malloc failed\n" -1));
		gc_track(val, GC_EXEC);
		set_env_var(env_list, var, val);
		i++;
	}
	return (0);
}