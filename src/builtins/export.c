/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:49:35 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/09 15:58:25 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_append(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]))
	{
		ft_printf("export: not an identifier: %c\n", arg[i]);
		return (-1);
	}
	if ((!ft_isalpha(arg[i]) && (arg[i] != '_') && (arg[i] != '+')))
	{
		ft_printf("export: not valid in this context PLUSEQALS: %c\n", arg[i]);
		return (-1);
	}
	printf("about to serach thru arg |%s|\n", arg);
	while (arg[i] && arg[i] != '=' && !(arg[i] == '+' && arg[i + 1] == '='))
		i++;
	if (arg[i] == '+' && arg[i + 1] == '=')
		return (i);
	return (-1);
}

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
	int		posplusequals;
	
	i = 1;
	// in theory this should actually print them in alphabetical order with a prefix
	if (!args[i])
		print_env(env_list);
	while (args[i])
	{
		posplusequals = find_append(args[i]);
		printf("found plus equals at pos |%d|\n", posplusequals);
		if (posplusequals > 0)
		{
			printf("Appending content |%s|\n", &args[i][posplusequals]);
			i++;
			continue ;
		}
		posequals = trust_but_verify(args[i]);
		if (posequals < 0)
			return (1);
		else
		{
			var = ft_substr(args[i], 0, posequals);
			if (!var)
				return (ft_printf("Malloc failed\n"), 2);
			gc_track(var, GC_EXEC);
			val = ft_strdup(args[i] + posequals + 1);
			if (!val)
				return (ft_printf("Malloc failed\n"), 2);
			gc_track(val, GC_EXEC);
			set_env_var(env_list, var, val);
			i++;
		}
	}
	return (0);
}