/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:34:46 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/25 15:35:15 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	assign_empty_var(t_env_list *env_list, char *arg)
{
	char	*var;

	var = NULL;
	safe_ft_strdup(&var, arg);
	set_env_var(env_list, var, NULL);
}

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
		return (-1);
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
	return (i);
}

int	has_equals(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}
