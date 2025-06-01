/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 00:07:26 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/02 00:48:58 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_arg_to_cmd(t_cmd_node *current_cmd, t_token_node *token)
{
	int	i;
	char	**new_arr;

	i = 0;
	if (token->type != TK_CMD)
		return ;
	if (!current_cmd->cmd)
	{
		new_arr = (char **)malloc(sizeof(char *) * 2);
		if (!new_arr)
			return ;
		gc_track(new_arr, GC_PARSE);
	}
	else
	{
		while (current_cmd->cmd[i])
			i++;
		new_arr = (char **)malloc(sizeof(char *) * (i + 2));
		gc_track(new_arr, GC_PARSE);
		i = 0;
		while (current_cmd->cmd[i])
		{
			new_arr[i] = ft_strdup(current_cmd->cmd[i]);
			gc_track(new_arr[i++], GC_PARSE);
		}
	}
	new_arr[i] = ft_strdup(token->content);
	gc_track(new_arr[i++], GC_PARSE);
	new_arr[i] = NULL;
	current_cmd->cmd = new_arr;
}
