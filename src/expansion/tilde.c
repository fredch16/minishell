/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:31:19 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/08 22:07:51 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_tilde(t_token_list *token_list, char *content)
{
	int				i;
	t_quote_state	quote_state;
	char			*new_content;
	char			*home;

	i = 0;
	quote_state = UNQUOTED;
	new_content = ft_strdup("");
	if (!new_content)
		return (tk_err(token_list, EC_MALLOC), NULL);
	gc_track(new_content, GC_PARSE);
	while (content[i])
	{
		quote_state = update_quote_state(quote_state, content[i]);
		// 🌟 Tilde Expansion
		if (content[i] == '~' && quote_state == UNQUOTED && ((i == 0 || is_whitespace(content[i - 1])) && ((content[i + 1] == '/') || is_whitespace(content[i + 1]) || !content[i + 1])))
		{
			home = get_env_value(token_list->env, "HOME");
			if (home)
			{
				new_content = ft_strjoin(new_content, home);
				if (!new_content)
					return (tk_err(token_list, EC_MALLOC), NULL);
				gc_track(new_content, GC_PARSE);
			}
			else
			{
				new_content = ft_charjoin(new_content, '~');
				if (!new_content)
					return (tk_err(token_list, EC_MALLOC), NULL);
				gc_track(new_content, GC_PARSE);
			}
			i++;
		}
		else
		{
			new_content = ft_charjoin(new_content, content[i]);
			if (!new_content)
				return (tk_err(token_list, EC_MALLOC), NULL);
			gc_track(new_content, GC_PARSE);
			i++;
		}
	}
	return (new_content);
}
