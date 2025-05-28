/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:52:31 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/28 02:10:20 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

bool handle_error(t_tokenizer_state *state)
{
	char c = state->input[state->pos];
	// Check for unclosed quotes at end of input
	if (state->quote_state != UNQUOTED && state->pos >= state->len - 1)
	{
		if (state->quote_state == SINGLE_QUOTED)
			printf("minishell: syntax error: unclosed single quote\n");
		else if (state->quote_state == DOUBLE_QUOTED)
			printf("minishell: syntax error: unclosed double quote\n");
		return false;
	}
	// Handle unexpected characters
	if (c == '\0')
	{
		printf("minishell: unexpected null character at position %zu\n", state->pos);
		return false;
	}
	// For any other unexpected character, treat as part of a word
	// This is more forgiving and matches bash behavior
	printf("minishell: warning: unexpected character '%c' at position %zu, treating as literal\n", 
		c, state->pos);
	// Try to extract it as a single character word token
	char single_char[2] = {c, '\0'};
	add_token(state->token_list, single_char, TK_WORD);
	state->pos++;
	return true; // Continue processing
}

/* ALTERNATIVE: More strict error handling */
bool handle_error_strict(t_tokenizer_state *state)
{
	char c = state->input[state->pos];
	
	// Check for unclosed quotes
	if (state->quote_state != UNQUOTED)
	{
		if (state->quote_state == SINGLE_QUOTED)
			printf("minishell: syntax error: unclosed single quote starting at position %zu\n",
				find_quote_start(state, '\''));
		else if (state->quote_state == DOUBLE_QUOTED)
			printf("minishell: syntax error: unclosed double quote starting at position %zu\n",
				find_quote_start(state, '"'));
		return false;
	}
	// Handle control characters
	if (c >= 0 && c < 32 && c != '\t' && c != '\n')
	{
		printf("minishell: syntax error: invalid control character (ASCII %d) at position %zu\n",
			(int)c, state->pos);
		return false;
	}
	// Handle invalid characters for shell
	if (c == '\0')
	{
		printf("minishell: syntax error: unexpected null character\n");
		return false;
	}
	// Generic unexpected character error
	printf("minishell: syntax error: unexpected character '%c' at position %zu\n",
		c, state->pos);
	return false;
}