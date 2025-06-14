/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 23:10:54 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/08 21:50:26 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "minishell.h"

// _expansion.c

void			expansion(t_token_list *token_list);

// command_expansion.c

void			expand_token(t_token_list *token_list, t_token_node *current);

// dollar_out_quote.c

char			*expand_dollar_vars(t_token_list *token_list, char *content);

// quote_state.c

bool			is_quote_toggle(t_quote_state quote_state, char c);
t_quote_state	update_quote_state(t_quote_state state, char curr);
void			exit_error(char *msg);

// env_variable.c

char			*extract_var(t_token_list *tlist, char *content);

// dollar_question.c

char			*expand_dollar_qmark(t_token_list *token_list, char *content);

// remove_quotes.c

char			*remove_quotes(t_token_list *tlist, char *content);

// tilde.c

char			*expand_tilde(t_token_list *token_list, char *content);

#endif