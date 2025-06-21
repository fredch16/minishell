/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:13:39 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/21 18:50:56 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t g_signal_recieved;

// hd struct functions

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

// Child process functions for heredoc collection

static int	is_delimiter(char *line, char *delimiter)
{
	int	len;

	if (!line || !delimiter)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (ft_strcmp(line, delimiter) == 0);
}

static int	collect_heredoc_in_child(t_mini *mini, char *delimiter, int write_fd)
{
	char	*line;
	char	*expanded_line;

	setup_heredoc_signals();
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break;
		if (g_signal_recieved == SIGINT)
			return (free(line), close(write_fd), exit(130), 1);
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break;
		}
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

static int	read_from_child_and_store(t_hd_node *hd_node, int read_fd)
{
	char	*line;
	char	*processed_line;

	while ((line = get_next_line(read_fd)) != NULL)
	{
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

// int	get_hd_data_in_parrent(int *pipe_fd, t_hd_node *hd_node, pid_t child_pid, t_mini *mini)
// {
// 	int	*status;

// 	close(pipe_fd[1]);
// 	if (read_from_child_and_store(hd_node, pipe_fd[0]) == -1)
// 		return (close(pipe_fd[0]), waitpid(child_pid, &status, 0), -1);
// 	close(pipe_fd[0]);
// 	waitpid(child_pid, &status, 0);
// 	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
// 	{
// 		mini->exit_code = 130;
// 		return (-1);
// 	}
// 	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
// 		return (-1);
// 	return (0);
// }

static int	create_heredoc_with_child(char *delimiter, t_mini *mini, t_hd_node *hd_node)
{
	int		pipe_fd[2];
	pid_t	child_pid;

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
		// if (get_hd_data_in_parrent(pipe_fd, hd_node, child_pid, mini) == -1)
		// 	return (-1);
		int	status;

		close(pipe_fd[1]);
		if (read_from_child_and_store(hd_node, pipe_fd[0]) == -1)
			return (close(pipe_fd[0]), waitpid(child_pid, &status, 0), -1);
		close(pipe_fd[0]);
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			mini->exit_code = 130;
			return (-1);
		}
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			return (-1);
		return (0);
	}
	return (0);
}

// hd fds functions

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
				if (create_heredoc(file_node->filename, mini, cmd_node, file_node) == -1)
					return (-1);
			}
			file_node = file_node->next;
		}
		cmd_node = cmd_node->next;
	}
	return (0);
}
