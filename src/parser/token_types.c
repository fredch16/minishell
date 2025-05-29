/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:53:19 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/29 17:56:47 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_token_type	token_type_one_symbol(char *content)
{
	if (*content == '|')
		return (TK_PIPE);
	if (*content == '<')
		return (TK_REDIR_IN);
	if (*content == '>')
		return (TK_REDIR_OUT);
	return (TK_CMD);
}

t_token_type	token_type_two_symbols(char *content)
{
	if (ft_strncmp(content, "<<", 2) == 0)
		return (TK_REDIR_HEREDOC);
	if (ft_strncmp(content, ">>", 2) == 0)
		return (TK_REDIR_APPEND);
	return (TK_CMD);
}

t_token_type	set_type(char *content, int token_length)
{
	t_token_type	type;

	type = TK_CMD;
	if (token_length == 1)
		type = token_type_one_symbol(content);
	else if (token_length == 2)
		type = token_type_two_symbols(content);
	if (token_length > 1)
	{
		if (content[0] == '\'' && content[token_length - 1] == '\'')
			type = TK_S_QUOTES;
		else if (content[0] == '"' && content[token_length - 1] == '"')
			type = TK_CMD;
	}
	return (type);
}