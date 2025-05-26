/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:46:27 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/27 01:08:54 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Initialize a new token list
 * @return Pointer to the newly created token list or NULL if allocation fails
 */
t_token_list	*init_token_list(void)
{
	t_token_list	*list;

	list = (t_token_list *)gc_malloc(sizeof(t_token_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

/**
 * Create a new token node
 * @param token String content for the token
 * @return Pointer to the newly created node or NULL if allocation fails
 */
t_token_node	*create_token_node(char *token)
{
	t_token_node	*new_node;

	new_node = (t_token_node *)gc_malloc(sizeof(t_token_node));
	if (!new_node)
		return (NULL);
	new_node->token = ft_strdup(token); // THIS LEAKS BECAUSE NO GC_MALLOCCCCC
	if (!new_node->token)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

/**
 * Add a node to the end of the token list
 * @param list The token list to add to
 * @param node The node to add
 */
void	add_token_to_list(t_token_list *list, t_token_node *node)
{
	if (!list || !node)
		return ;
	if (!list->head)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}

/**
 * Free all resources allocated for the token list
 * @param list The token list to free
 */
void	free_token_list(t_token_list *list)
{
	t_token_node	*current;
	t_token_node	*next;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
	free(list);
}

/**
 * Tokenize the input line into a linked list of tokens
 * @param token_list The list to populate with tokens
 * @param line The input line to tokenize
 * @return 0 on success, -1 on error
 */

int	tokenise(t_token_list *token_list, char *line)
{
	char	**tokens;
	int		i;
	t_token_node *new_node;

	if (!token_list || !line)
		return (-1);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (-1);
	i = 0;
	while (tokens[i])
	{
		new_node = create_token_node(tokens[i]);
		if (!new_node)
		{
			// Free everything allocated so far
			while (tokens[i])
				free(tokens[i++]);
			free(tokens);
			return (-1);
		}
		add_token_to_list(token_list, new_node);
		i++;
	}
	// Free the array of strings but not the individual strings
	// as those are now copied into our token nodes
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return (0);
}

/**
 * Print all tokens in the token list (for debugging)
 * @param list The token list to print
 */
void	print_tokens(t_token_list *list)
{
	t_token_node	*current;
	int				i;

	if (!list)
		return ;
	current = list->head;
	i = 0;
	while (current)
	{
		printf("Token %d: '%s'\n", i++, current->token);
		current = current->next;
	}
	printf("Total tokens: %zu\n", list->size);
}