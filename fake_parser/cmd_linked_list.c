/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_linked_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:14:50 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 22:38:14 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd_list	*init_cmd_list(t_mini *mini, char *input)
{
	t_cmd_list	*list;

	(void)input;
	list = gc_malloc(sizeof(t_cmd_list), GC_PARSE);
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->exit_code = mini->exit_code;
	list->env = mini->env_list;
	list->error_code = mini->error_code;
	return (list);
}

t_cmd_node	*new_cmd(void)
{
	t_cmd_node	*new_cmd;

	new_cmd = (t_cmd_node *)ft_calloc(1, sizeof(t_cmd_node));
	if (new_cmd == NULL)
		return (perror("New cmd failed to malloc\n"), NULL);
	gc_track(new_cmd, GC_PARSE);
	return (new_cmd);
}

void	cmd_add_back(t_cmd_list *cmd_list, t_cmd_node *new_cmd)
{
	if (cmd_list->head == NULL)
	{
		cmd_list->head = new_cmd;
		cmd_list->tail = new_cmd;
		cmd_list->size = 1;
	}
	else
	{
		cmd_list->tail->next = new_cmd;
		cmd_list->tail = new_cmd;
		cmd_list->size++;
	}
}
