/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:46:27 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/29 17:46:25 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/* MAIN TOKENIZATION FUNCTION */
t_token_list *tokenize_input(char *input)
{
	
	t_tokenizer_state	state;
	t_token_node		*token;


	state.token_list = init_token_list(input);
	state.input = input;
	state.quote_state = UNQUOTED;
	while (*state.input != '\0')
	{
		while (is_whitespace(*state.input))
			state.input++;
		if (*state.input == '\0')
			break;
		token = new_token();
		token->length = set_token_length(&state);
		token->content = ft_substr(state.input, 0, token->length);
		token->type = set_type(token->content, token->length);
		token_add_back(state.token_list, token);
		state.input += token->length;
	}
	// if (handle_error(&state) == true)
	// 	return (NULL);
	
	return (state.token_list);
}
