/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:48:01 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/05 15:15:02 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/**
 * @brief Checks if a character is a whitespace
 *
 * Determines if the given character is a space, tab, or newline.
 *
 * @param c The character to check
 * @return true if the character is a whitespace character, false otherwise
 */
bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * @brief Checks if a character is a shell operator
 *
 * Determines if the given character is a pipe ('|') or a redirection
 * operator ('<', '>')
 *
 * @param c The character to check
 * @return true if the character is an operator, false otherwise
 */
bool	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * @brief Checks if a token string is a shell builtin command
 *
 * Compares the given token against a list of known shell builtins
 * (echo, cd, pwd, export, unset, env, exit) to determine if it's
 * a builtin command.
 *
 * @param token The token string to check
 * @return true if the token is a builtin command, false otherwise
 */
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
