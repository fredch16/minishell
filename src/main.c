/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 21:58:05 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/28 18:51:17 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char			*line;
	t_token_list	*token_list;

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
		token_list = tokenize_input(line);
		// if (token_list && tokenise(token_list, line) == 0)
		if (token_list)
			print_tokens(token_list);
		free(line);
		gc_free_all();  // Clear all allocated memory after each command
	}
	printf("minishell is over\n");
	return (0);
}
