/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:58:05 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/25 17:09:43 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal_recieved = 0;

void	handle_input(t_mini *mini, char *line)
{
	g_signal_recieved = 0;
	mini->token_list = init_token_list(mini, line);
	tokenize_input(mini->token_list, line);
	if (!mini->token_list->head)
		return ;
	expansion(mini->token_list);
	if (handle_error(mini))
		return ;
	mini->cmd_list = init_cmd_list(mini, line);
	if (build_cmd_list(mini->token_list, mini->cmd_list))
	{
		handle_error(mini);
		return ;
	}
	mini->exit_code = execution(mini);
	reverting_stds();
	gc_free_by_type(GC_PARSE);
}

int	non_interactive(t_mini *mini)
{
	char	*line;	
	char	*temp_line;

	if (!isatty(STDIN_FILENO))
	{
		temp_line = get_next_line(fileno(stdin));
		if (temp_line)
		{
			line = ft_strtrim(temp_line, "\n");
			free(temp_line);
			if (line && line[0] != '\0')
			{
				gc_track(line, GC_PARSE);
				handle_input(mini, line);
			}
		}
		gc_free_all();
		return (1);
	}
	return (0);
}

int	prep_it(t_mini *mini, int ac, char **av, char **env)
{
	char	*cwd;

	(void)av;
	(void)ac;
	mini->exit_code = 0;
	mini->error_code = 0;
	mini->env_list = env_array_to_list(env);
	if (!env[0])
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			destroy_minishell(999);
		gc_track(cwd, GC_ENV);
		set_env_var(mini->env_list, "OLDPWD", NULL);
		set_env_var(mini->env_list, "PWD", cwd);
		set_env_var(mini->env_list, "SHLVL", "1");
	}
	else
		increase_shlvl(mini);
	if (!mini->env_list)
		destroy_minishell(999);
	if (non_interactive(mini))
		return (mini->exit_code);
	return (-50);
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_mini			mini;

	if (prep_it(&mini, ac, av, env) != -50)
		return (mini.exit_code);
	setup_signals();
	while (1)
	{
		line = readline("\033[35mminishell $> \033[0m");
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		gc_track(line, GC_PARSE);
		if (!ft_strcmp(line, "exit"))
		{
			gc_free_all();
			break ;
		}
		handle_input(&mini, line);
	}
	printf("exit\n");
	gc_free_all();
	restore_terminal();
	return (0);
}
