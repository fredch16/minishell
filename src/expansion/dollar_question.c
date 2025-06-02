/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_question.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:57:42 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/02 15:54:39 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_dollar_qmark(t_token_list *token_list, char *content)
{
	int				i;
	t_quote_state	quote_state;
	char			*new_content;
	char			*expansion;

	i = 0;
	quote_state = UNQUOTED;
	new_content = ft_strdup("");
	gc_track(new_content, GC_PARSE);
	while (content[i])
	{
		quote_state = update_quote_state(quote_state, content[i]);
		if (content[i] == '$' && content[i + 1] == '?' && quote_state != SINGLE_QUOTED)
		{
			expansion = ft_itoa(token_list->exit_code);
			gc_track(expansion, GC_PARSE);
			new_content = ft_strjoin(new_content, expansion);
			i += 2;
		}
		else
		{
			new_content = ft_charjoin(new_content, content[i]);
			gc_track(new_content, GC_PARSE);
			i++;
		}
	}
	return (new_content);
}
