/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:28:12 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/25 12:40:59 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "minishell.h"

char		*expand_heredoc(t_mini *mini, char *line);

t_hd_node	*get_heredoc_for_file(t_cmd_node *cmd_node,
				t_file_node *file_node);
int			process_input_redirection(t_file_node *file_node, t_mini *mini,
				t_cmd_node *cmd_node, int builtins);
int			process_output_redirection(t_file_node *file_node, t_mini *mini);
int			dup_fd(int last_input_fd);

#endif