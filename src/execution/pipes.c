/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:34:17 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/14 01:20:09 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_child_pipes(int **pipes, int cmd_index, int pipe_count)
{
	int	i;

	if (cmd_index > 0)
	{
		if (dup2(pipes[cmd_index - 1][0], STDIN_FILENO) == -1)
			ft_error(1, "dup2 input failed", 0);
	}
	if (cmd_index < pipe_count)
	{
		if (dup2(pipes[cmd_index][1], STDOUT_FILENO) == -1)
			ft_error(1, "dup2 output failed", 0);
	}
	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	execute_builtin_parent(t_cmd_node *cmd, t_mini *mini)
{
	int	exit_code = 0;

	if (!cmd || !cmd->cmd)
		return 0;
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		exit_code = echo_builtin(cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		exit_code = pwd_builtin();
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		exit_code = export_builtin(mini->env_list, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		exit_code = unset_builtin(mini->env_list, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		exit_code = env_builtin(mini->env_list);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		exit_code = cd_builtin(mini->env_list, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
	{
		printf("exit\n");
		gc_free_all();
		exit(0);
	}
	return (exit_code);
}

int	fork_and_exec(t_cmd_node *cmd, t_mini *mini, int **pipes, int index)
{
	pid_t	pid;
	int		pipe_count;

	pipe_count = mini->cmd_list->size - 1;
	if (cmd->cmd_type == BUILTIN && pipe_count == 0)
	{
		if (handle_redirections(cmd, mini, 1) == -1)
			return (-1);
		mini->exit_code = execute_builtin_parent(cmd, mini);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		setup_child_signals();
		setup_child_pipes(pipes, index, pipe_count);
		if (handle_redirections(cmd, mini, 0) == -1)
			ft_error(1, "Redirection failed", 0);
		execute_external(cmd, mini);
		ft_error(127, "Command execution failed", 0);
	}
	return (pid);
}
