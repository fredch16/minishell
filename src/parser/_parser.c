/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:35:05 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/23 18:21:25 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	finalize_command(t_cmd_node *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return ;
	while (cmd->cmd[0][i])
	{
		cmd->cmd[0][i] = ft_tolower(cmd->cmd[0][i]);
		i++;
	}
	if (is_builtin(cmd->cmd[0]))
		cmd->cmd_type = BUILTIN;
	else
		cmd->cmd_type = STDCMD;
}

void	build_pipe(t_cmd_list **cmd_list, t_cmd_node **current_cmd,
	t_file_list **file_list)
{
	finalize_command(*current_cmd);
	(*current_cmd)->files = *file_list;
	cmd_add_back(*cmd_list, *current_cmd);
	*current_cmd = new_cmd();
	*file_list = init_file_list();
}

int	build_redirect(t_file_list **file_list, t_token_node **current_token,
	t_token_list **token_list)
{
	if (!(*current_token)->next || (*current_token)->next->type != TK_CMD)
	{
		(*token_list)->error_code = 998;
		return (1);
	}
	add_redirection(*file_list, *current_token, (*current_token)->next);
	*current_token = (*current_token)->next;
	return (0);
}

int	build_cmd_list(t_token_list *token_list, t_cmd_list *cmd_list)
{
	t_cmd_node		*current_cmd;
	t_file_list		*file_list;
	t_token_node	*current_token;

	current_cmd = new_cmd();
	file_list = init_file_list();
	current_token = token_list->head;
	if (check_syntax_errors(token_list))
		return (-1);
	while (current_token)
	{
		if (current_token->type == TK_PIPE)
			build_pipe(&cmd_list, &current_cmd, &file_list);
		else if (is_redirect(current_token))
		{
			if (build_redirect(&file_list, &current_token, &token_list))
				return (998);
		}
		else
			add_arg_to_cmd(current_cmd, current_token);
		current_token = current_token->next;
	}
	finalize_command(current_cmd);
	current_cmd->files = file_list;
	return (cmd_add_back(cmd_list, current_cmd), 0);
}
