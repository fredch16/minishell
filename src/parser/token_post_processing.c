/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_post_processing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:12:45 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/28 02:06:55 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

/* TOKEN TYPE DETERMINATION */
t_token_type determine_token_type(char *token, bool has_quotes, t_token_type quote_type)
{
	// If it was quoted, return the quote type
	if (has_quotes)
		return quote_type;
	// Check if it's a builtin command
	if (is_builtin(token))
		return TK_BUILTIN;
	// Default to word
	return TK_WORD;
}