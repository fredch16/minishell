/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:22:47 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/01 16:08:43 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_token(t_token_list *token_list, t_token_node *current)
{
	// char	*old_content;

	// expand $?
	// expand $when not in quotes
	current->content = expand_dollar_noquote(token_list, current->content);
	current->content = expand_dollar_qmark(token_list, current->content);
	// expand $ with quotes
	
}