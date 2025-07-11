/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 05:34:17 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/23 19:37:34 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile sig_atomic_t	g_signal_recieved;

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
	int	exit_code;

	exit_code = 0;
	if (!cmd || !cmd->cmd)
		return (0);
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
		exit_code = exit_minishell(cmd);
	return (exit_code);
}

static void	child_execution_instructions(int **pipes, t_cmd_node *cmd,
	t_mini *mini, int index)
{
	int	redir_result;

	setup_child_signals();
	setup_child_pipes(pipes, index, mini->cmd_list->size - 1);
	redir_result = handle_redirections(cmd, mini, 0);
	if (redir_result == -1)
		ft_error(1, "Redirection failed", 0);
	if (cmd->cmd_type == BUILTIN)
		execute_builtin(cmd, mini);
	else
		execute_external(cmd, mini);
	ft_error(127, "Command execution failed", 0);
}

int	fork_and_exec(t_cmd_node *cmd, t_mini *mini, int **pipes, int index)
{
	pid_t	pid;
	int		pipe_count;
	int		redir_result;

	redir_result = 0;
	pipe_count = mini->cmd_list->size - 1;
	if (cmd->cmd_type == BUILTIN && pipe_count == 0)
	{
		redir_result = handle_redirections(cmd, mini, 1);
		if (redir_result == -1)
			return (-1);
		mini->exit_code = execute_builtin_parent(cmd, mini);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		child_execution_instructions(pipes, cmd, mini, index);
	return (pid);
}
