/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:31:19 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/17 00:04:08 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	safe_ft_strjoin(char **s3, char *s1, char *s2)
{
	*s3 = ft_strjoin(s1, s2);
	if (!*s3)
		return (-1); // pack exit strategy in this return
	gc_track(*s3, GC_PARSE);
	return (0);
}

int	safe_ft_charjoin(char **s3, char *s1, char s2)
{
	*s3 = ft_charjoin(s1, s2);
	if (!*s3)
		return (-1); // pack exit strategy in this return
	gc_track(*s3, GC_PARSE);
	return (1);
}

int	safe_ft_strdup(char **s1, char *s2)
{
	*s1 = ft_strdup(s2);
	if (!*s1)
		return (-1);
	gc_track(*s1, GC_PARSE);
	return (1);
}

/**
 * Process a single character during variable expansion
 * @param token_list Token list for error handling and environment access
 * @param content Original content string
 * @param pm Struct containing the iteration state
 * @return Number of characters processed 
 * (1 for normal char, variable length for variables)
 */

static int	process_var_char(t_token_list *token_list, char *content,
	t_expansion_params *pm)
{
	char	*varname;
	char	*vaexp;
	int		chars_processed;

	pm->quote_state = update_quote_state(pm->quote_state,
			content[pm->i]);
	if (content[pm->i] == '$'
		&& (ft_isalpha(content[pm->i + 1]) || content[pm->i + 1] == '_')
		&& pm->quote_state != SINGLE_QUOTED)
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

/**
 * Expand variable references ($NAME) in the given content
 * @param token_list Token list for error handling and environment access
 * @param content Content string to expand
 * @return New string with expanded variables
 */
char	*expand_dollar_vars(t_token_list *token_list, char *content)
{
	t_expansion_params	params;
	char				*new_content;
	int					chars_processed;

	params.i = 0;
	params.quote_state = UNQUOTED;
	safe_ft_strdup(&new_content, "");
	params.new_content = &new_content;
	while (content[params.i])
	{
		chars_processed = process_var_char(token_list, content, &params);
		if (chars_processed < 0)
			return (NULL);
		params.i += chars_processed;
	}
	if (params.quote_state != UNQUOTED)
		token_list->error_code = EC_UNCLOSEQ;
	return (new_content);
}
