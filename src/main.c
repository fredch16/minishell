/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:58:05 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/04 05:37:19 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_mini			mini;

	(void)ac;
	(void)av;
	mini.exit_code = 0;
	mini.error_code = 0;
	mini.env_list = env_array_to_list(env);
	if (!mini.env_list)
		return (1);
	while (1)
	{
		line = readline("minishell $> ");
		if (!line)  // Handle Ctrl+D (EOF)
			break;
		if (line[0] != '\0')
			add_history(line);
		if (!ft_strncmp(line, "exit", ft_strlen(line)))
		{
			free(line);
			gc_free_all();
			break;
		}
		mini.token_list = init_token_list(&mini, line);
		tokenize_input(mini.token_list, line);
		print_tokens(mini.token_list);
		printf("\n%s=== EXPANSION STAGE ===%s\n", COLOR_BLUE, COLOR_RESET);
		expansion(mini.token_list);
		if (handle_error(&mini))
			continue;
		// print_tokens(mini.token_list);
		mini.cmd_list = init_cmd_list(&mini, line);
		if (build_cmd_list(mini.token_list, mini.cmd_list))
		{
			handle_error(&mini);
			continue;
		}
		print_cmd_list(mini.cmd_list);
		mini.exit_code = execution(&mini);
		free(line);
		gc_free_by_type(GC_PARSE);
	}
	printf("minishell is over\n");
	gc_free_all();
	return (0);
}
