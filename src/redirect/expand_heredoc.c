/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:23:49 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/10 17:35:35 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*hd_expand_dollar_vars(t_token_list *token_list, char *content)
{
	int				i;
	char			*new_content;
	char			*varname;
	char			*var_expansion;

	i = 0;
	new_content = ft_strdup("");
	if (!new_content)
		return (tk_err(token_list, EC_MALLOC), NULL);
	gc_track(new_content, GC_PARSE);
	while (content[i])
	{
		if (content[i] == '$' && content[i + 1] != '?')
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
	return (new_content);
}

char	*hd_expand_dollar_qmark(t_token_list *token_list, char *content)
{
	int				i;
	char			*new_content;
	char			*expansion;

	if (!g2g(token_list))
		return (NULL);
	i = 0;
	new_content = ft_strdup("");
	if (!new_content)
		return (tk_err(token_list, EC_MALLOC), NULL);
	gc_track(new_content, GC_PARSE);
	while (content[i])
	{
		if (content[i] == '$' && content[i + 1] == '?')
		{
			expansion = ft_itoa(token_list->exit_code);
			if (!expansion)
				return (tk_err(token_list, EC_MALLOC), NULL);
			gc_track(expansion, GC_PARSE);
			new_content = ft_strjoin(new_content, expansion);
			if (!new_content)
				return (tk_err(token_list, EC_MALLOC), NULL);
			i += 2;
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

char	*expand_heredoc(t_mini *mini, char *line)
{
	line = hd_expand_dollar_vars(mini->token_list, line);
	if (mini->token_list->error_code)
		return (NULL);
	line = hd_expand_dollar_qmark(mini->token_list, line);
	return (line);
}