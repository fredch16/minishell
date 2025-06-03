/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:31:19 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 22:04:40 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_dollar_vars(t_token_list *token_list, char *content)
{
	int				i;
	t_quote_state	quote_state;
	char			*new_content;
	char			*varname;
	char			*var_expansion;

	i = 0;
	quote_state = UNQUOTED;
	new_content = ft_strdup("");
	if (!new_content)
		return (tk_err(token_list, EC_MALLOC), NULL);
	gc_track(new_content, GC_PARSE);
	while (content[i])
	{
		quote_state = update_quote_state(quote_state, content[i]);
		if (content[i] == '$' && content[i + 1] != '?'
			&& quote_state != SINGLE_QUOTED)
		{
			varname = extract_var(token_list, &content[i]);
			if (varname)
			{
				var_expansion = get_env_value(token_list->env, varname);
				if (var_expansion)
				{
					new_content = ft_strjoin(new_content, var_expansion);
					if (!new_content)
						return (tk_err(token_list, EC_MALLOC), NULL);
					gc_track(new_content, GC_PARSE);
				}
				i += ft_strlen(varname) + 1;
				continue ;
			}
			else
			{
				new_content = ft_charjoin(new_content, '$');
				if (!new_content)
					return (tk_err(token_list, EC_MALLOC), NULL);
				gc_track(new_content, GC_PARSE);
				i++;
			}
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
	if (quote_state != UNQUOTED)
		token_list->error_code = EC_UNCLOSEQ;
	return (new_content);
}
