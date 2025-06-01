/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:23:43 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/01 22:36:03 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/**
 * Determines if a character toggles the current quote state.
 *
 * @param quote_state The current quote state (UNQUOTED, SINGLE_QUOTED, DOUBLE_QUOTED)
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

char	*remove_quotes(char *content)
{
	int				i;
	t_quote_state	quote_state;
	char			*new_content;

	i = 0;
	quote_state = UNQUOTED;
	new_content = ft_strdup("");
	gc_track(new_content, GC_PARSE);
	while (content[i])
	{
		if (is_quote_toggle(quote_state, content[i]))
		{
			quote_state = update_quote_state(quote_state, content[i]);
			i++;
			continue;
		}
		new_content = ft_charjoin(new_content, content[i]);
		gc_track(new_content, GC_PARSE);
		i++;
	}
	return (new_content);
}