/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:22:47 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/31 17:08:39 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_command_token(t_token_list *token_list, t_token_node *current)
{
	char	*old_content;

	// expand $?
	old_content = current->content;
	current->content = expand_dollar_qmark(token_list, current->content);
	gc_free(old_content);
	// expand $when not in quotes
	old_content = current->content;
	current->content = expand_dollar_noquote(token_list, current->content);
	gc_free(old_content);
	// expand $ with quotes
	
}