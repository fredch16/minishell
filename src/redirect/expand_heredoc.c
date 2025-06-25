/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:23:49 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/25 11:38:50 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	process_var_char(t_token_list *token_list, char *content,
	t_expansion_params *pm)
{
	char	*varname;
	char	*vaexp;
	int		chars_processed;

	if (content[pm->i] == '$'
		&& (ft_isalpha(content[pm->i + 1]) || content[pm->i + 1] == '_'))
	{
		varname = extract_var(token_list, &content[pm->i]);
		if (varname)
		{
			vaexp = get_env_value(token_list->env, varname);
			if (vaexp)
				safe_ft_strjoin(pm->new_content, *(pm->new_content), vaexp);
			chars_processed = ft_strlen(varname) + 1;
			return (chars_processed);
		}
	}
	chars_processed = safe_ft_charjoin(pm->new_content, *(pm->new_content),
			content[pm->i]);
	return (chars_processed);
}

char	*hd_expand_dollar_vars(t_token_list *token_list, char *content)
{
	t_expansion_params	params;
	char				*new_content;
	int					chars_processed;

	params.i = 0;
	safe_ft_strdup(&new_content, "");
	params.new_content = &new_content;
	while (content[params.i])
	{
		chars_processed = process_var_char(token_list, content, &params);
		if (chars_processed < 0)
			return (NULL);
		params.i += chars_processed;
	}
	return (new_content);
}

/**
 * Process a single character during dollar expansion
 * @param token_list Token list for error handling and exit code
 * @param content Original content string
 * @param params Struct containing the iteration state
 * @return 1 on success, 0 on error
 */
static int	process_char(t_token_list *token_list, char *content,
	t_expansion_params *params)
{
	char	*expansion;

	if (content[params->i] == '$' && content[params->i + 1] == '?')
	{
		expansion = ft_itoa(token_list->exit_code);
		if (!expansion)
			return (tk_err(token_list, EC_MALLOC), 0);
		gc_track(expansion, GC_PARSE);
		*(params->new_content) = ft_strjoin(*(params->new_content), expansion);
		if (!*(params->new_content))
			return (tk_err(token_list, EC_MALLOC), 0);
		params->i += 2;
	}
	else
		params->i += safe_ft_charjoin(params->new_content,
				*(params->new_content), content[params->i]);
	return (1);
}

/**
 * Expand $? in the given content string
 * @param token_list Token list for error handling and exit code
 * @param content Original content string
 * @return Expanded content string or NULL on error
 */
char	*hd_expand_dollar_qmark(t_token_list *token_list, char *content)
{
	t_expansion_params	params;
	char				*new_content;

	if (!g2g(token_list))
		return (NULL);
	params.i = 0;
	new_content = ft_strdup("");
	if (!new_content)
		return (tk_err(token_list, EC_MALLOC), NULL);
	gc_track(new_content, GC_PARSE);
	params.new_content = &new_content;
	while (content[params.i])
	{
		if (!process_char(token_list, content, &params))
			return (NULL);
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
