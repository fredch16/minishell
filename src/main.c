/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:58:05 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/31 17:02:38 by fredchar         ###   ########.fr       */
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
	// mini.token_list = gc_malloc(sizeof(t_token_list));

	/* Example of env list usage in main */
	mini.env_list = env_array_to_list(env);
	if (!mini.env_list)
		return (1);
	while (1)
	{
		line = readline("minishell$> ");
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
		mini.token_list = init_token_list(line);
		mini.token_list->exit_code = mini.exit_code;
		mini.token_list->env = mini.env_list;
		tokenize_input(mini.token_list, line);
		print_tokens(mini.token_list);
		printf("\n%s=== EXPANSION STAGE ===%s\n", COLOR_BLUE, COLOR_RESET);
		expansion(mini.token_list);
		print_tokens(mini.token_list);
		free(line);
		gc_free_by_type(GC_PARSE);
	}
	printf("minishell is over\n");
	gc_free_all();
	return (0);
}
