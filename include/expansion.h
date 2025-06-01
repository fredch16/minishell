/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:10:54 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/30 01:43:47 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "minishell.h"

// command_expansion.c

void	expand_command_token(t_token_list *token_list, t_token_node *current);

// dollar_out_quote.c

char	*expand_dollar_noquote(t_token_list *token_list, char *content);

// quote_state.c

t_quote_state update_quote_state(t_quote_state state, char curr);

#endif