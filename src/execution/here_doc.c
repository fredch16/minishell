/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:13:39 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/16 16:38:37 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t g_signal_recieved;

t_hd_line	*create_hd_line(void)
{
	t_hd_line	*new;

	new = malloc(sizeof(t_hd_line));
	if (!new)
		return (NULL);
	new->line = NULL;
	new->next = NULL;
	return (new);
}

t_hd_node	*create_hd_node(char *lim)
{
	t_hd_node	*new;

	new = malloc(sizeof(t_hd_node));
	if (!new)
		return (NULL);
	new->lines = create_hd_line();
	if (!new->lines)
		return (NULL);
	new->lim = lim;
	new->next = NULL;
	return (new);
}

static int	is_delimiter(char *line, char *delimiter)
{
	if (!line || !delimiter)
		return (0);
	return (ft_strcmp(line, delimiter) == 0);
}

static void	read_heredoc_lines(t_mini *mini, t_cmd_node *cmd_node, t_hd_node *hd_node)
{
	char		*line;
	t_hd_line	*hd_line;

	hd_line = hd_node->lines;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_delimiter(line, hd_node->lim))
		{
			free(line);
			break ;
		}
		hd_line = expand_heredoc(mini, line);
		free(line);
		if (!hd_line)
			break ;
		hd_line->next = create_hd_line();
		hd_line = hd_line->next;
	}
}

int	create_heredoc(char *lim, t_mini *mini, t_cmd_node *cmd_node, t_file_node *file_node)
{
	if (!cmd_node->hd_list.head)
	{
		cmd_node->hd_list.head = create_hd_node(lim);
		if (!cmd_node->hd_list.head)
			return (1);
			cmd_node->hd_list.tail = cmd_node->hd_list.head;
	}
	else
	{
		cmd_node->hd_list.tail->next = create_hd_node(lim);
		if (!cmd_node->hd_list.tail->next)
			return (1);
			cmd_node->hd_list.tail = cmd_node->hd_list.tail->next;
	}
	cmd_node->hd_list.tail->file_node = file_node;
	read_heredoc_lines(mini, cmd_node, cmd_node->hd_list.tail);
	return (0);
}

int	create_heredoc_list(t_mini *mini)
{
	t_cmd_node	*cmd_node;
	t_file_node	*file_node;

	cmd_node = mini->cmd_list->head;
	while (cmd_node)
	{
		file_node = cmd_node->files->head;
		while (file_node)
		{
			if (file_node->redir_type == REDIR_HEREDOC)
				create_heredoc(file_node->filename, mini, cmd_node, file_node);
			file_node = file_node->next;
		}
		cmd_node = cmd_node->next;
	}
	return (0);
}
