/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:36:46 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 22:34:08 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	get_single_char_len(char c)
{
	return (ft_strchr("|<>", c) != NULL);
}

static int	get_quote_len(char *cmd_line)
{
	int		len;
	char	quote_type;

	quote_type = cmd_line[0];
	len = 0;
	while (cmd_line[len] != '\0')
	{
		if (cmd_line[len] == '"' || cmd_line[len] == '\'')
		{
			quote_type = cmd_line[len++];
			while (cmd_line[len] != '\0' && cmd_line[len] != quote_type)
				len++;
			if (cmd_line[len] == quote_type)
				len++;
		}
		else if (is_whitespace(cmd_line[len])
			|| get_single_char_len(cmd_line[len]))
			break ;
		else
			len++;
	}
	return (len);
}

static int	get_double_char_len(char *cmd_line)
{
	const char	*symbols[] = {"<<", ">>", NULL};
	int			len;

	len = 0;
	while (symbols[len] != NULL)
	{
		if (ft_strncmp(cmd_line, symbols[len], ft_strlen(symbols[len])) == 0)
			return (ft_strlen(symbols[len]));
		len++;
	}
	return (0);
}

static void	handle_command_quotes(bool *quotes, char *quote_type, char current)
{
	if (current == '"' || current == '\'')
	{
		if (!(*quotes))
		{
			*quotes = true;
			*quote_type = current;
		}
		else if (*quote_type == current)
		{
			*quotes = false;
			*quote_type = '\'';
		}
	}
}

static int	get_command_len(char *cmd_line)
{
	int		len;
	bool	quotes;
	char	quote_type;

	len = 0;
	quotes = false;
	quote_type = '\0';
	while (cmd_line[len] != '\0')
	{
		handle_command_quotes(&quotes, &quote_type, cmd_line[len]);
		if (!quotes && (is_whitespace(cmd_line[len])
				|| get_single_char_len(cmd_line[len])))
			break ;
		len++;
	}
	return (len);
}

int	set_token_length(char *cmd_line)
{
	int	len;

	len = get_double_char_len(cmd_line);
	if (len > 0)
		return (len);
	else if (get_single_char_len(cmd_line[0]))
		return (1);
	else if (cmd_line[0] == '"' || cmd_line[0] == '\'')
		return (get_quote_len(cmd_line));
	else
		return (get_command_len(cmd_line));
	return (len);
}
