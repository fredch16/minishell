/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:37:09 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 22:05:47 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Determines if a character toggles the current quote state.
 *
 * @param quote_state The current quote state (UNQUOTED, SINGLE, DOUBLE)
 * @param c The character to check
 * @return True if c starts or ends the current quote context, false otherwise.
 */
bool	is_quote_toggle(t_quote_state quote_state, char c)
{
	if (quote_state == UNQUOTED)
		return (c == '\'' || c == '"');
	if (quote_state == SINGLE_QUOTED)
		return (c == '\'');
	if (quote_state == DOUBLE_QUOTED)
		return (c == '"');
	return (false);
}

t_quote_state	update_quote_state(t_quote_state state, char curr)
{
	if (state == UNQUOTED)
	{
		if (curr == '\'')
			return (SINGLE_QUOTED);
		else if (curr == '"')
			return (DOUBLE_QUOTED);
	}
	else if (state == SINGLE_QUOTED)
	{
		if (curr == '\'')
			return (UNQUOTED);
	}
	else if (state == DOUBLE_QUOTED)
	{
		if (curr == '"')
			return (UNQUOTED);
	}
	return (state);
}

t_quote_state	update_quote_state_debug(t_quote_state state, char curr)
{
	if (state == UNQUOTED)
	{
		if (curr == '\'')
		{
			printf("Found |%c|: Updating State to SINGLE QOUTED\n", curr);
			return (SINGLE_QUOTED);
		}
		else if (curr == '"')
		{
			printf("Found |%c|: Updating State to DOUBLE QUOTED\n", curr);
			return (DOUBLE_QUOTED);
		}
	}
	else if (state == SINGLE_QUOTED)
	{
		if (curr == '\'')
		{
			printf("Found |%c|: Updating State to UNQOUTED\n", curr);
			return (UNQUOTED);
		}
	}
	else if (state == DOUBLE_QUOTED)
	{
		if (curr == '"')
		{
			printf("Found |%c|: Updating State to UNQOUTED\n", curr);
			return (UNQUOTED);
		}
	}
	return (state);
}
