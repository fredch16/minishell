/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:49:35 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/25 15:35:11 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Handle a single export argument with append operation (+=)
 * @param env_list Environment list
 * @param arg Argument string
 * @return 0 on success, 1 on failure
 */
static int	handle_export_append(t_env_list *env_list, char *arg)
{
	char	*var;
	char	*val;
	int		posplusequals;

	posplusequals = find_append(arg);
	if (posplusequals <= 0)
		return (0);
	var = ft_substr(arg, 0, posplusequals);
	if (!var)
		return (ft_printf("Malloc failed\n"), 2);
	gc_track(var, GC_EXEC);
	val = ft_strdup(arg + posplusequals + 2);
	if (!val)
		return (ft_printf("Malloc failed\n"), 2);
	gc_track(val, GC_EXEC);
	append_env_var(env_list, var, val);
	return (1);
}

/**
 * Handle a single export argument for normal assignment
 * @param env_list Environment list
 * @param arg Argument string
 * @return 0 on success, >0 on error
 */
static int	handle_export_assign(t_env_list *env_list, char *arg)
{
	char	*var;
	char	*val;
	int		posequals;

	posequals = trust_but_verify(arg);
	if (posequals <= 0)
		return (1);
	if (posequals > 0 && has_equals(arg) < 0)
		return (assign_empty_var(env_list, arg), 0);
	var = ft_substr(arg, 0, posequals);
	if (!var)
		return (ft_printf("Malloc failed\n"), 2);
	gc_track(var, GC_EXEC);
	val = ft_strdup(arg + posequals + 1);
	if (!val)
		return (ft_printf("Malloc failed\n"), 2);
	gc_track(val, GC_EXEC);
	set_env_var(env_list, var, val);
	return (0);
}

/**
 * Export builtin command implementation
 * @param env_list Environment variable list
 * @param args Command arguments (args[0] is "export")
 * @return Exit status (0 on success, >0 on error)
 */
int	export_builtin(t_env_list *env_list, char **args)
{
	int	i;
	int	result;
	int	exit_status;

	if (!args[1])
		return (export_no_arg(env_list));
	i = 1;
	exit_status = 0;
	while (args[i])
	{
		result = handle_export_append(env_list, args[i]);
		if (result == 2)
			return (2);
		else if (result == 0)
		{
			result = handle_export_assign(env_list, args[i]);
			if (result > 0)
				exit_status = result;
		}
		i++;
	}
	return (exit_status);
}
