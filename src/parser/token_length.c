/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:36:46 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/29 17:45:17 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	handle_cmd_quotes(t_tokenizer_state *state, char curr)
{
	if (curr == '"' || curr == '\'')
	{
		if (state->quote_state == UNQUOTED)
		{
			state->quote_state = SINGLE_QUOTED;
			state->quote_type = '\'';
			if (curr == '"')
			{
				state->quote_state = DOUBLE_QUOTED;
				state->quote_type = '"';
			}
		}
		else if (state->quote_type == curr)
		{
			state->quote_state = UNQUOTED;
			state->quote_type = '\'';
		}
	}
}

size_t	try_dbl_opr_len(char *input)
{
	printf("input in double is |%s|\n", input);
	if (input[0] == '<' && input[1] == '<') //going to need extra implementation for tripple oppr BS
		return (2);
	else if (input[0] == '>' && input[1] == '>') //going to need extra implementation for tripple oppr BS
		return (2);
	return (0);
}

size_t	try_sgl_opr_len(char *input)
{
	if (input[0] == '<' || input[0] == '>' || input[0] == '|')
		return (1);
	return (0);
}

size_t	try_cmd_len(t_tokenizer_state *state)
{
	size_t	len;

	len = 0;
	state->quote_state = UNQUOTED;
	state->quote_type = '\0';
	while (state->input[len])
	{
		handle_cmd_quotes(state, state->input[len]);
		if (state->quote_state == UNQUOTED && (is_whitespace(state->input[len]) || try_sgl_opr_len(&state->input[len])))
			break ;
		len++;
	}
	return (len);
}

size_t	try_quote_len(t_tokenizer_state *state)
{
	size_t	len;

	state->quote_state = DOUBLE_QUOTED;
	state->quote_type = '"';
	if (*state->input == '\'')
	{
		state->quote_state = SINGLE_QUOTED;
		state->quote_type = '\'';
	}
	len = 1;
	while (state->input[len] && state->input[len] != state->quote_type)
		len++;
	if (state->input[len] == state->quote_type)
		len++;
	while(!is_whitespace(state->input[len]) && !try_sgl_opr_len(&state->input[len]) && state->input[len] != '\0')
		len++;
	return (len);

}

size_t	set_token_length(t_tokenizer_state *state)
{
	size_t	len;

	len = try_dbl_opr_len(state->input);
	if (len > 0)
		return (len);
	else if (try_sgl_opr_len(state->input))
		return (1);
	else if (state->input[0] == '"' || state->input[0] == '\'')
		return (try_quote_len(state));
	else
		return(try_cmd_len(state));
	return (len);
}