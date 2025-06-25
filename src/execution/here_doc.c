/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:13:39 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/25 16:52:29 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t	g_signal_recieved;

static int	collect_heredoc_in_child(t_mini *mini, char *delimiter,
	int write_fd)
{
	char	*line;
	char	*expanded_line;

	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (g_signal_recieved == SIGINT)
			return (free(line), close(write_fd), exit(130), 1);
		if (is_delimiter(line, delimiter))
			break ;
		expanded_line = expand_heredoc(mini, line);
		free(line);
		if (!expanded_line)
			return (close(write_fd), exit(1), 1);
		write(write_fd, expanded_line, ft_strlen(expanded_line));
		write(write_fd, "\n", 1);
		free(expanded_line);
	}
	return (close(write_fd), exit(0), 0);
}

static int	read_from_child_and_store(t_hd_node *hd_node, int read_fd)
{
	char	*line;
	char	*processed_line;

	while (1)
	{
		line = get_next_line(read_fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		processed_line = ft_strdup(line);
		if (!processed_line)
			return (free(line), -1);
		gc_track(processed_line, GC_EXEC);
		add_line_to_heredoc(hd_node, processed_line);
		free(line);
	}
	return (0);
}

static int	create_heredoc_with_child(char *delimiter, t_mini *mini,
	t_hd_node *hd_node)
{
	int		pipe_fd[2];
	pid_t	child_pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (-1);
	child_pid = fork();
	if (child_pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	if (child_pid == 0)
	{
		close(pipe_fd[0]);
		collect_heredoc_in_child(mini, delimiter, pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]);
		if (read_from_child_and_store(hd_node, pipe_fd[0]) == -1)
			return (close(pipe_fd[0]), waitpid(child_pid, &status, 0), -1);
		close(pipe_fd[0]);
		return (check_exit_status(child_pid, mini));
	}
	return (0);
}

int	create_heredoc(char *lim, t_mini *mini, t_cmd_node *cmd_node,
	t_file_node *file_node)
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
	if (create_heredoc_with_child(lim, mini, new_hd) == -1)
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
				if (create_heredoc(file_node->filename,
						mini, cmd_node, file_node) == -1)
					return (-1);
			}
			file_node = file_node->next;
		}
		cmd_node = cmd_node->next;
	}
	return (0);
}
