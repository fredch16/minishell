/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:35:05 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/01 21:55:41 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	build_cmd_list(t_token_list *token_list, t_cmd_list *cmd_list)
{
	t_cmd_node		*current_cmd;
	t_file_list		*file_list;
	t_token_node	*curr_token;
	// traverse tokens
	//   if token is PIPE:
	//       finalize current_cmd
	//       append to cmd_list
	//       reset current_cmd and file_list
	//   else if token is REDIRECTION:
	//       verify next token (filename)
	//       add to file_list
	//       skip filename
	//   else:
	//       add to current_cmd->cmd (char **)
	// finalize last current_cmd

}