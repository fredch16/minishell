/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:58:05 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/10 08:19:30 by apregitz         ###   ########.fr       */
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
	gc_track(line, GC_PARSE);
	handle_input(mini, line);
}

int	increase_shlvl(t_mini *mini)
{
	t_env_node	*node;
	int			lvl;

	node = mini->env_list->head;
	while (node)
	{
		if (ft_strcmp(node->variable, "SHLVL") == 0)
		{
			gc_free(node->value);
			lvl = ft_atoi(node->value);
			node->value = ft_itoa(++lvl);
			if (!node->next)
				ft_error(1, "malloc", EC_FD | EC_GC);
			gc_track(node->value, GC_ENV);
			return (0);
		}
		node = node->next;
	}
	return (1);
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

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_mini			mini;

	(void)av;
	(void)ac;
	mini.exit_code = 0;
	mini.error_code = 0;
	mini.env_list = env_array_to_list(env);
	if (!mini.env_list)
		return (1);
	increase_shlvl(&mini);
	if (non_interactive(&mini))
		return (mini.exit_code);
	setup_signals();

	while (1)
	{
		line = readline("\033[35mminishell $> \033[0m");
		if (!line)
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
	restore_terminal();
	return (0);
}
