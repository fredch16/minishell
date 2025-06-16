/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_question.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:57:42 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/16 23:56:31 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

	params->quote_state = update_quote_state(params->quote_state,
			content[params->i]);
	if (content[params->i] == '$' && content[params->i + 1] == '?'
		&& params->quote_state != SINGLE_QUOTED)
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
char	*expand_dollar_qmark(t_token_list *token_list, char *content)
{
	t_expansion_params	params;
	char				*new_content;

	if (!g2g(token_list))
		return (NULL);
	params.i = 0;
	params.quote_state = UNQUOTED;
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
