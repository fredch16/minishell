/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:58:05 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/30 00:13:57 by fredchar         ###   ########.fr       */
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
	token_list->env = env;
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
