/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 10:35:53 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/02 17:55:59 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

// exec_cmd.c
void	    exec_cmd(t_cmd_node *cmd_node, t_mini *mini);
void	    setup_exec(t_cmd_node *cmd_node, t_mini *mini);

// error.c
void	    ft_error(int error_code, char *error_msg);

// init.c
void	    init_exec_data(t_mini *mini);

// fd_collector.c
void	    clear_fd_list(void);
int	        *get_new_fd(int *fd, size_t size);
t_fd_node	*new_fd_node(int fd);
t_fd_list	*get_fd_list(void);

// get_path.c
char	    *get_command_path(t_cmd_node *cmd_node, t_mini *mini);

// here_doc.c
int	        create_heredoc(char *delimiter);

// redirection_cases.c
int	        handle_heredoc_redir(char *delimiter, t_mini *mini);
int	        handle_input_redir(t_file_node *file_node, t_mini *mini);
int	        handle_output_redir(t_file_node *file_node, t_mini *mini);
int	        handle_append_redir(t_file_node *file_node, t_mini *mini);

// redirections.c
int     	handle_redirections(t_cmd_node *cmd_node, t_mini *mini);

// setup_child.c
void	    setup_child_input(t_mini *mini);

// execution.c
int        	execution(t_mini *mini);

#endif