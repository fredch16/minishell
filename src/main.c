/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:58:05 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/30 17:09:00 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_token_list	*token_list;

	(void)ac;
	(void)av;
	token_list = gc_malloc(sizeof(t_token_list));

	/* Example of env list usage in main */
	t_env_list *env_list = env_array_to_list(env);
	if (!env_list)
		return (1);

	// Set a new variable
	set_env_var(env_list, "MINISHELL", "1");

	// // Get a value
	// char *home = get_env_value(env_list, "HOME");
	// if (home)
	// 	printf("HOME=%s\n", home);

	return (0);
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
		token_list = init_token_list(line);
		tokenize_input(token_list, line);
		print_tokens(token_list);
		free(line);
		gc_free_all();
	}
	printf("minishell is over\n");
	return (0);
}
