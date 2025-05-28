/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:46:27 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/28 18:56:01 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/* MAIN TOKENIZATION FUNCTION */
t_token_list *tokenize_input(char *input)
{
	t_tokenizer_state   state;
	
	state.input = input;
	state.pos = 0;
	state.len = strlen(input);
	state.quote_state = UNQUOTED;
	state.token_list = init_token_list(input);

	while (state.pos < state.len)
	{
		skip_whitespace(&state);
		if (state.pos >= state.len)
			break;
		// Check for operators first (they have precedence)
		if (try_extract_operator(&state))
			continue;
		// Extract word/quoted token
		if (extract_word_token(&state))
			continue;
		// If we get here, there's an unexpected character
	}
	if (handle_error(&state) == true)
		return (NULL);
	
	return state.token_list;
}
