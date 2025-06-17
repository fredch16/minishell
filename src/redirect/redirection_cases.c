/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:11:05 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/17 10:29:37 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_hd_node	*find_heredoc_node(t_cmd_node *cmd_node, t_file_node *file_node)
{
	t_hd_node	*current;

	current = cmd_node->hd_list.head;
	while (current)
	{
		if (current->file_node == file_node)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	handle_heredoc_redir(char *delimiter, t_mini *mini, t_cmd_node *cmd_node, int builtins)
{
	t_file_node	*file_node;
	t_hd_node	*hd_node;
	
	(void)delimiter;
	(void)mini;
	(void)builtins;
	file_node = cmd_node->files->head;
	while (file_node)
	{
		if (file_node->redir_type == REDIR_HEREDOC && 
			ft_strcmp(file_node->filename, delimiter) == 0)
			break;
		file_node = file_node->next;
	}
	if (!file_node)
		return (-1);
	hd_node = find_heredoc_node(cmd_node, file_node);
	if (!hd_node)
		return (-1);
	return (create_heredoc_fd(hd_node));
}

int	handle_input_redir(t_file_node *file_node, t_mini *mini)
{
	int	fd;

	(void)mini;
	fd = open(file_node->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_node->filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	return (fd);
}

int	handle_output_redir(t_file_node *file_node, t_mini *mini)
{
	int	fd;

	(void)mini;
	fd = open(file_node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_node->filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_append_redir(t_file_node *file_node, t_mini *mini)
{
	int	fd;

	(void)mini;
	fd = open(file_node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_node->filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}