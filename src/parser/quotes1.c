/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:03:30 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/28 00:22:27 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"


/* UTILITY: Find where a quote was opened (for better error messages) */
size_t find_quote_start(t_tokenizer_state *state, char quote_char)
{
	size_t pos = 0;
	t_quote_state temp_state = UNQUOTED;
	size_t quote_start = 0;
	
	while (pos < state->pos)
	{
		char c = state->input[pos];
		
		if (c == quote_char)
		{
			if (temp_state == UNQUOTED)
			{
				// Opening quote found
				if (quote_char == '\'')
					temp_state = SINGLE_QUOTED;
				else if (quote_char == '"')
					temp_state = DOUBLE_QUOTED;
				quote_start = pos;
			}
			else if ((quote_char == '\'' && temp_state == SINGLE_QUOTED) ||
					(quote_char == '"' && temp_state == DOUBLE_QUOTED))
			{
				// Closing quote found
				temp_state = UNQUOTED;
			}
		}
		else if (c == '"' && temp_state == UNQUOTED)
		{
			// Handle the other quote type
			temp_state = DOUBLE_QUOTED;
		}
		else if (c == '\'' && temp_state == UNQUOTED)
		{
			// Handle the other quote type
			temp_state = SINGLE_QUOTED;
		}
		else if (c == '"' && temp_state == SINGLE_QUOTED)
		{
			// Double quote inside single quotes - treat as literal
			// Do nothing
		}
		else if (c == '\'' && temp_state == DOUBLE_QUOTED)
		{
			// Single quote inside double quotes - treat as literal
			// Do nothing
		}
		
		pos++;
	}
	
	return (quote_start);
}

/* QUOTE HANDLING */
bool handle_quote_transition(t_tokenizer_state *state, char c, bool *has_quotes, t_token_type *quote_type)
{
	switch (c)
	{
		case '"':
			if (state->quote_state == UNQUOTED)
			{
				state->quote_state = DOUBLE_QUOTED;
				*has_quotes = true;
				*quote_type = TK_D_QUOTES;
			}
			else if (state->quote_state == DOUBLE_QUOTED)
			{
				state->quote_state = UNQUOTED;
			}
			else
			{
				return (false); // Inside single quotes, treat as literal
			}
			return (true);
			
		case '\'':
			if (state->quote_state == UNQUOTED)
			{
				state->quote_state = SINGLE_QUOTED;
				*has_quotes = true;
				*quote_type = TK_S_QUOTES;
			}
			else if (state->quote_state == SINGLE_QUOTED)
			{
				state->quote_state = UNQUOTED;
			}
			else
			{
				return (false); // Inside double quotes, treat as literal
			}
			return (true);
			
		default:
			return (false);
	}
}
