/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:58:05 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/09 14:28:46 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t g_signal_recieved = 0;

void	handle_input(t_mini *mini, char *line)
{
	mini->token_list = init_token_list(mini, line);
	tokenize_input(mini->token_list, line);
	if (!mini->token_list->head)
		return ;
	if (DEBUG)
	{
		print_tokens(mini->token_list);
		printf("\n%s=== EXPANSION STAGE ===%s\n", COLOR_BLUE, COLOR_RESET);
	}
	expansion(mini->token_list);
	if (handle_error(mini))
		return ;
	if (DEBUG)
		print_tokens(mini->token_list);	
	mini->cmd_list = init_cmd_list(mini, line);
	if (build_cmd_list(mini->token_list, mini->cmd_list))
	{
		handle_error(mini);
		return ;
	}
	if (DEBUG)
		print_cmd_list(mini->cmd_list);
	mini->exit_code = execution(mini);
	reverting_stds();
	gc_free_by_type(GC_PARSE);
}

void	handle_non_interactive(t_mini *mini, int ac, char **av)
{
	char	*line;

	(void)ac;
	line = ft_strjoin_arr(&av[1]);
	handle_input(mini, line);
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_mini			mini;

	mini.exit_code = 0;
	mini.error_code = 0;
	mini.env_list = env_array_to_list(env);
	if (!mini.env_list)
		return (1);
	if (ac > 1)
	{
		handle_non_interactive(&mini, ac, av);
		return (gc_free_all(), mini.exit_code);
	}
	setup_signals();
	while (1)
	{
		line = readline("minishell $> ");
		if (!line)  // Handle Ctrl+D (EOF)
			break;
		if (line[0] != '\0')
			add_history(line);
		gc_track(line, GC_PARSE);
		if (!ft_strcmp(line, "exit"))
		{
			gc_free_all();
			break;
		}
		handle_input(&mini, line);
		if (g_signal_recieved == SIGINT)
			g_signal_recieved = 0;
	}
	printf("exit\n");
	gc_free_all();
	return (0);
}
