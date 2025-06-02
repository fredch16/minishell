/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:37:09 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/02 15:33:47 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_quote_state update_quote_state(t_quote_state state, char curr)
{
	if (state == UNQUOTED)
	{
		if (curr == '\'')
		{
			// printf("Found |%c|: Updating State to SINGLE QOUTED\n", curr);
			return (SINGLE_QUOTED);
		}
		else if (curr == '"')
		{
			// printf("Found |%c|: Updating State to DOUBLE QUOTED\n", curr);
			return (DOUBLE_QUOTED);
		}
	}
	else if (state == SINGLE_QUOTED)
	{
		if (curr == '\'')
		{
			// printf("Found |%c|: Updating State to UNQOUTED\n", curr);
			return (UNQUOTED);
		}
	}
	else if (state == DOUBLE_QUOTED)
	{
		if (curr == '"')
		{
			// printf("Found |%c|: Updating State to UNQOUTED\n", curr);
			return (UNQUOTED);
		}
	}
	return (state);
}
