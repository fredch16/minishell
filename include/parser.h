/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:49:09 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/28 00:20:00 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// BTW ALL OF THESE ARE IN ROOT/SRC/PARSER/

// parsing_utils1.c

void			skip_whitespace(t_tokenizer_state *state);
bool			is_whitespace(char c);
bool			is_operator_char(char c);
bool			is_builtin(char *token);

// parsing_errors.c

bool			handle_error(t_tokenizer_state *state);

// tokens.c

bool			add_token(t_token_list *list, char *token_str, t_token_type type);

// quotes1.c

size_t			find_quote_start(t_tokenizer_state *state, char quote_char);
bool			handle_quote_transition(t_tokenizer_state *state, char c, bool *has_quotes, t_token_type *quote_type);

// token_extracts.c

bool			try_extract_operator(t_tokenizer_state *state);

// token_post_processing.c

t_token_type	determine_token_type(char *token, bool has_quotes, t_token_type quote_type);

// token_linked_list.c

t_token_list	*init_token_list(char *input);
bool			add_token(t_token_list *list, char *token_str, t_token_type type);
void			free_token_list(t_token_list *list);

// token_extracts.c

bool			try_extract_operator(t_tokenizer_state *state);
bool			extract_word_token(t_tokenizer_state *state);

#endif