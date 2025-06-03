/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:49:09 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 22:55:30 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_ANALYSIS_H
# define LEXICAL_ANALYSIS_H

# include "minishell.h"

// BTW ALL OF THESE ARE IN ROOT/SRC/PARSER/

// _lexical_analysis.c

void			tokenize_input(t_token_list *token_list, char *input);

// parsing_utils1.c

bool			is_whitespace(char c);
bool			is_operator_char(char c);
bool			is_builtin(char *token);

// tokens.c

bool			add_token(t_token_list *list, char *token_str,
					t_token_type type);

// token_post_processing.c

t_token_type	determine_token_type(char *token, bool has_quotes,
					t_token_type quote_type);

// token_linked_list.c

t_token_list	*init_token_list(t_mini *mini, char *input);
bool			add_token(t_token_list *list, char *token_str,
					t_token_type type);
void			free_token_list(t_token_list *list);
t_token_node	*new_token(void);
void			token_add_back(t_token_list *token_list,
					t_token_node *new_token);

// token_length.c

int				set_token_length(char *cmd_line);

// token_types.c

t_token_type	set_type(char *content, int token_length);

#endif