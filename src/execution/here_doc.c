/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:13:39 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/17 10:29:09 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t g_signal_recieved;

static t_hd_line	*create_hd_line(char *content)
{
	t_hd_line	*new;

	new = gc_malloc(sizeof(t_hd_line), GC_EXEC);
	if (!new)
		return (NULL);
	new->line = content;
	new->next = NULL;
	return (new);
}

static t_hd_node	*create_hd_node(char *lim)
{
	t_hd_node	*new;

	new = gc_malloc(sizeof(t_hd_node), GC_EXEC);
	if (!new)
		return (NULL);
	new->lines = NULL;
	new->lim = ft_strdup(lim);
	if (!new->lim)
		return (NULL);
	gc_track(new->lim, GC_EXEC);
	new->file_node = NULL;
	new->next = NULL;
	return (new);
}

static int	is_delimiter(char *line, char *delimiter)
{
	if (!line || !delimiter)
		return (0);
	return (ft_strcmp(line, delimiter) == 0);
}

static void	add_line_to_heredoc(t_hd_node *hd_node, char *line)
{
	t_hd_line	*new_line;
	t_hd_line	*current;

	new_line = create_hd_line(line);
	if (!new_line)
		return;
	
	if (!hd_node->lines)
	{
		hd_node->lines = new_line;
		return;
	}
	
	current = hd_node->lines;
	while (current->next)
		current = current->next;
	current->next = new_line;
}

static int	read_heredoc_lines(t_mini *mini, t_hd_node *hd_node)
{
	char		*line;
	char		*expanded_line;

	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file\n", 2);
			break;
		}
		if (g_signal_recieved == SIGINT)
		{
			free(line);
			mini->exit_code = 130;
			return (-1);
		}
		if (is_delimiter(line, hd_node->lim))
		{
			free(line);
			break;
		}
		expanded_line = expand_heredoc(mini, line);
		free(line);
		if (!expanded_line)
			return (-1);
		
		add_line_to_heredoc(hd_node, expanded_line);
	}
	reset_parent_signals();
	return (0);
}

static int	write_heredoc_to_pipe(t_hd_node *hd_node, int write_fd)
{
	t_hd_line	*current;

	current = hd_node->lines;
	while (current)
	{
		if (current->line)
		{
			write(write_fd, current->line, ft_strlen(current->line));
			write(write_fd, "\n", 1);
		}
		current = current->next;
	}
	return (0);
}

int	create_heredoc_fd(t_hd_node *hd_node)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	
	write_heredoc_to_pipe(hd_node, pipe_fd[1]);
	close(pipe_fd[1]);
	
	return (pipe_fd[0]);
}

int	create_heredoc(char *lim, t_mini *mini, t_cmd_node *cmd_node, t_file_node *file_node)
{
	t_hd_node	*new_hd;

	new_hd = create_hd_node(lim);
	if (!new_hd)
		return (-1);
	new_hd->file_node = file_node;
	if (!cmd_node->hd_list.head)
	{
		cmd_node->hd_list.head = new_hd;
		cmd_node->hd_list.tail = new_hd;
		cmd_node->hd_list.size = 1;
	}
	else
	{
		cmd_node->hd_list.tail->next = new_hd;
		cmd_node->hd_list.tail = new_hd;
		cmd_node->hd_list.size++;
	}
	if (read_heredoc_lines(mini, new_hd) == -1)
		return (-1);
	return (0);
}

int	create_heredoc_list(t_mini *mini)
{
	t_cmd_node	*cmd_node;
	t_file_node	*file_node;

	g_signal_recieved = 0;
	cmd_node = mini->cmd_list->head;
	while (cmd_node)
	{
		file_node = cmd_node->files->head;
		while (file_node)
		{
			if (file_node->redir_type == REDIR_HEREDOC)
			{
				if (create_heredoc(file_node->filename, mini, cmd_node, file_node) == -1)
					return (-1);
			}
			file_node = file_node->next;
		}
		cmd_node = cmd_node->next;
	}
	return (0);
}