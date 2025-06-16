/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:31:19 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/17 00:24:08 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Check if a tilde should be expanded at the current position
 * @param content Original content string
 * @param i Current position in the string
 * @return 1 if the tilde should be expanded, 0 otherwise
 */
static int	is_expandable_tilde(char *content, int i)
{
	return ((i == 0 || is_whitespace(content[i - 1]))
		&& ((content[i + 1] == '/') || is_whitespace(content[i + 1])
			|| !content[i + 1]));
}

/**
 * Process a character during tilde expansion
 * @param token_list Token list containing environment variables
 * @param content Original content string
 * @param params Expansion parameters (position, quote state, result)
 */
static void	process_tilde_char(t_token_list *token_list, char *content,
							t_expansion_params *params)
{
	char	*home;

	params->quote_state = update_quote_state(params->quote_state,
			content[params->i]);
	if (content[params->i] == '~' && params->quote_state == UNQUOTED
		&& is_expandable_tilde(content, params->i))
	{
		home = get_env_value(token_list->env, "HOME");
		if (home)
			safe_ft_strjoin(params->new_content, *(params->new_content), home);
		else
			safe_ft_charjoin(params->new_content, *(params->new_content), '~');
	}
	else
	{
		safe_ft_charjoin(params->new_content, *(params->new_content),
			content[params->i]);
	}
	params->i++;
}

/**
 * Expand tildes in the input content
 * @param token_list Token list containing environment variables
 * @param content Original content string
 * @return New string with expanded tildes
 */
char	*expand_tilde(t_token_list *token_list, char *content)
{
	t_expansion_params	params;
	char				*new_content;

	params.i = 0;
	params.quote_state = UNQUOTED;
	safe_ft_strdup(&new_content, "");
	params.new_content = &new_content;
	while (content[params.i])
		process_tilde_char(token_list, content, &params);
	return (new_content);
}
