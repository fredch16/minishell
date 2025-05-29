/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _lexical_analysis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:46:27 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/30 00:10:58 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/* MAIN TOKENIZATION FUNCTION */
void tokenize_input(t_token_list *token_list, char *input)
{
	t_token_node		*token;

	while (*input != '\0')
	{
		while (is_whitespace(*input))
			input++;
		if (*input == '\0')
			break;
		token = new_token();
		token->length = set_token_length(input);
		token->content = ft_substr(input, 0, token->length);
		gc_track(token->content);
		token->type = set_type(token->content, token->length);
		token_add_back(token_list, token);
		input += token->length;
	}
}
