/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:23:43 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/15 16:53:21 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	init_content(char **nc, t_token_list *tlist, t_quote_state *qs)
{
	*qs = UNQUOTED;
	*nc = ft_strdup("");
	if (!nc)
		return (tk_err(tlist, EC_MALLOC), 1);
	gc_track(*nc, GC_PARSE);
	return (0);
}

char	*remove_quotes(t_token_list *tlist, char *content)
{
	int				i;
	t_quote_state	quote_state;
	char			*new_content;

	if (!g2g(tlist))
		return (NULL);
	if (init_content(&new_content, tlist, &quote_state))
		return (NULL);
	i = 0;
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
