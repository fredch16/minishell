/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:46:27 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/29 19:33:15 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/* MAIN TOKENIZATION FUNCTION */
t_token_list *tokenize_input(char *input)
{
	t_token_list		*token_list;
	t_token_node		*token;


	token_list = init_token_list(input);
	while (*input != '\0')
	{
		while (is_whitespace(*input))
			input++;
		if (*input == '\0')
			break;
		token = new_token();
		token->length = set_token_length(input);
		token->content = ft_substr(input, 0, token->length);
		token->type = set_type(token->content, token->length);
		token_add_back(token_list, token);
		input += token->length;
	}
	
	return (token_list);
}
