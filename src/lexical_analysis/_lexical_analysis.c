/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexical_analysis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:46:27 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/15 13:23:31 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* MAIN TOKENIZATION FUNCTION */
void	tokenize_input(t_token_list *token_list, char *input)
{
	t_token_node		*token;

	while (*input != '\0')
	{
		while (is_whitespace(*input))
			input++;
		if (*input == '\0')
			break ;
		token = new_token();
		if (!token)
			return (tk_err(token_list, EC_MALLOC));
		token->length = set_token_length(input);
		token->content = ft_substr(input, 0, token->length);
		if (!token->content)
			return (tk_err(token_list, EC_MALLOC));
		gc_track(token->content, GC_PARSE);
		token->type = set_type(token->content, token->length);
		token_add_back(token_list, token);
		input += token->length;
	}
}
