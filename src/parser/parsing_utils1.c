/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:48:01 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/29 15:36:33 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	skip_whitespace(t_tokenizer_state *state)
{
	while (state->pos < state->len
		&& is_whitespace(state->input[state->pos]))
		state->pos++;
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	is_builtin(char *token)
{
	static char	*builtins[] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit", NULL};
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (strcmp(token, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
