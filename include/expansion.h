/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:10:54 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/01 17:39:05 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "minishell.h"

// _expansion.c

void	expansion(t_token_list *token_list);

// command_expansion.c

void	expand_token(t_token_list *token_list, t_token_node *current);

// dollar_out_quote.c

char	*expand_dollar_vars(t_token_list *token_list, char *content);

// quote_state.c

t_quote_state update_quote_state(t_quote_state state, char curr);
void	exit_error(char *msg);

// env_variable.c

char	*extract_var(char *content);

// dollar_question.c

char	*expand_dollar_qmark(t_token_list *token_list, char *content);

// remove_quotes.c

char	*remove_quotes(char *content);

#endif