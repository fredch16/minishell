/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 06:06:15 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/23 17:48:23 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_builtin(t_cmd_node *cmd, t_mini *mini)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		exit_code = echo_builtin(cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		exit_code = pwd_builtin();
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		exit_code = cd_builtin(mini->env_list, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		exit_code = export_builtin(mini->env_list, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		exit_code = unset_builtin(mini->env_list, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		exit_code = env_builtin(mini->env_list);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		exit_code = exit_minishell(cmd);
	gc_free_all();
	exit(exit_code);
}

void	execute_external(t_cmd_node *cmd, t_mini *mini)
{
	char	*cmd_path;
	char	**env_array;

	cmd_path = get_command_path(cmd, mini);
	if (!cmd_path)
		ft_error(127, "Command not found", 0);
	env_array = env_list_to_array(mini->env_list);
	if (!env_array)
		ft_error(1, "Failed to convert environment", 0);
	if (DEBUG)
	{
		ft_putstr_fd("\n\nExecuting command: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putstr_fd("\n\n\n", STDERR_FILENO);
	}
	execve(cmd_path, cmd->cmd, env_array);
	ft_error(127, "execve failed", 0);
}

int	wait_for_children(pid_t *pids, int cmd_count)
{
	int	status;
	int	exit_code;
	int	i;

	status = 0;
	exit_code = 0;
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				exit_code = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGINT)
					write(STDOUT_FILENO, "\n", 1);
			}
		}
		i++;
	}
	reset_parent_signals();
	return (exit_code);
}
