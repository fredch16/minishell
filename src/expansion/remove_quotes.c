/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:23:43 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 22:06:06 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_quotes(t_token_list *tlist, char *content)
{
	int				i;
	t_quote_state	quote_state;
	char			*new_content;

	if (!g2g(tlist))
		return (NULL);
	i = 0;
	quote_state = UNQUOTED;
	new_content = ft_strdup("");
	if (!new_content)
		return (tk_err(tlist, EC_MALLOC), NULL);
	gc_track(new_content, GC_PARSE);
	while (content[i])
	{
		if (is_quote_toggle(quote_state, content[i]))
		{
			quote_state = update_quote_state(quote_state, content[i]);
			i++;
			continue ;
		}
		new_content = ft_charjoin(new_content, content[i]);
		if (!new_content)
			return (tk_err(tlist, EC_MALLOC), NULL);
		gc_track(new_content, GC_PARSE);
		i++;
	}
	return (new_content);
}
