/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extracts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:08:45 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/28 02:06:36 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/* OPERATOR EXTRACTION - CHECK MULTI-CHAR FIRST */
bool	try_extract_dbl_opr(t_tokenizer_state *state, char *input, size_t pos)
{
	if (pos + 1 < state->len)
	{
		if (input[pos] == '<' && input[pos + 1] == '<')
		{
			add_token(state->token_list, "<<", TK_REDIR_HEREDOC);
			state->pos += 2;
			return (true);
		}
		if (input[pos] == '>' && input[pos + 1] == '>')
		{
			add_token(state->token_list, ">>", TK_REDIR_APPEND);
			state->pos += 2;
			return (true);
		}
	}
	return (false);
}

bool	try_extract_sgl_opr(t_tokenizer_state *state, char *input, size_t pos)
{
	if (input[pos] == '|')
	{
		add_token(state->token_list, "|", TK_PIPE);
		state->pos++;
		return true;
	}
	else if (input[pos] == '<')
	{
		add_token(state->token_list, "<", TK_REDIR_IN);
		state->pos++;
		return true;
	}
	else if (input[pos] == '>')
	{
		add_token(state->token_list, ">", TK_REDIR_OUT);
		state->pos++;
		return true;
	}
	else
		return false;
}

bool	try_extract_operator(t_tokenizer_state *state)
{
	char *input = state->input;
	size_t pos = state->pos;
	
	// Skip if we're in quotes
	if (state->quote_state != UNQUOTED)
		return false;
	// Check two-character operators first
	if (try_extract_dbl_opr(state, input, pos) == true)
		return (true);
	// Check single-character operators
	return (try_extract_sgl_opr(state, input, pos));
}

/* WORD TOKEN EXTRACTION */
bool extract_word_token(t_tokenizer_state *state)
{
	char *buffer = malloc(state->len + 1); // Worst case: entire input is one token
	size_t buf_pos = 0;
	bool has_quotes = false;
	t_token_type quote_type = TK_WORD;
	
	while (state->pos < state->len)
	{
		char c = state->input[state->pos];
		// Handle quote state changes
		if (handle_quote_transition(state, c, &has_quotes, &quote_type))
		{
			state->pos++;
			continue; // Don't add quote characters to buffer
		}
		// If unquoted, check for token terminators
		if (state->quote_state == UNQUOTED)
		{
			if (is_whitespace(c) || is_operator_char(c))
				break;
		}
		// Add character to buffer
		buffer[buf_pos++] = c;
		state->pos++;
	}
	if (buf_pos == 0)
	{
		free(buffer);
		return false;
	}
	buffer[buf_pos] = '\0';
	// Determine token type
	t_token_type type = determine_token_type(buffer, has_quotes, quote_type);
	add_token(state->token_list, buffer, type);
	free(buffer);
	return true;
}
