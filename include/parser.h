/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:37:00 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/02 00:23:21 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// cmd_linked_list.c

t_cmd_list *init_cmd_list(t_mini *mini, char *input);
t_cmd_node	*new_cmd(void);
void	cmd_add_back(t_cmd_list *cmd_list, t_cmd_node *new_cmd);

// file_linked_list.c

t_file_list *init_file_list(void);
t_file_node	*new_file(void);
void	file_add_back(t_file_list *file_list, t_file_node *new_file);

// redirections.c

bool	is_redirect(t_token_node *token);
void	add_redirection(t_file_list *file_list, t_token_node *redir_token, t_token_node *file_token);

// _parser.c

int	build_cmd_list(t_token_list *token_list, t_cmd_list *cmd_list);

// commands.c

void	add_arg_to_cmd(t_cmd_node *current_cmd, t_token_node *token);

#endif