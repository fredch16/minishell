/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:37:00 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/01 22:00:51 by fredchar         ###   ########.fr       */
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

t_file_list *init_file_list(t_mini *mini, char *input);
t_file_node	*new_file(void);
void	cmd_file_back(t_file_list *cmd_list, t_file_node *new_cmd);

#endif