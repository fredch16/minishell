/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_out_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:31:19 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/30 18:58:58 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_dollar_noquote(t_token_list *token_list, char *content)
{
	int				i;
	t_quote_state	quote_state;
	char			*new_content;
	char			*varname;
	char			*var_expansion;

	i = 0;
	quote_state = UNQUOTED;
	new_content = ft_strdup("");
	gc_track(new_content, GC_PARSE);

	while (content[i])
	{
		quote_state = update_quote_state(quote_state, content[i]);
		if (content[i] == '$' && content[i + 1] != '$' && quote_state != SINGLE_QUOTED)
		{
			// extract variable name
			varname = extract_var(&content[i]);
			if (varname)
			{
				// look up variable in ENV
				var_expansion = get_env_value(token_list->env, varname);
				if (var_expansion)
				{
					new_content = ft_strjoin(new_content, var_expansion);
					gc_track(new_content, GC_PARSE);
				}
				i += ft_strlen(varname) + 1;
				continue;
			}
			else
			{
				new_content = ft_charjoin(new_content, '$');
				gc_track(new_content, GC_PARSE);
				i++;
			}
		}
		else
		{
			// just add the char to the content
			// change this to char join because we only want to add a character
			new_content = ft_charjoin(new_content, content[i]);
			gc_track(new_content, GC_PARSE);
			i++;
		}
	}
	return (new_content);
}