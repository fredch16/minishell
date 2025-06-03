/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 08:52:17 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/02 10:31:30 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd_list	*get_fd_list(void)
{
	static t_fd_list *list;

	return (list);
}

t_fd_node	*new_fd_node(int fd)
{
	t_fd_node	*new;

	new = malloc(sizeof(t_fd_node));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	return (new);
}

int	*get_new_fd(int *fd, size_t size)
{
	size_t		i;
	t_fd_list	*list;
	t_fd_node	*node;

	if (size < 1)
		return (NULL);
	list = get_fd_list();
	i = 0;
	node = list->head;
	while (node->next)
		node = node->next;
	while (i < size)
	{
		node->next = new_fd_node(fd[i]);
		if (!node->next)
			return (NULL);
		node = node->next;
	}
	return (fd);
}

void	clear_fd_list(void)
{
	t_fd_list	*list;
	t_fd_node	*node;
	t_fd_node	*temp;

	list = get_fd_list();
	node = list->head;
	while (node)
	{
		temp = node;
		node = node->next;
		free(temp);
	}
}

// int	clear_fd_node(int fd)
// {
// 	t_fd_list	*list;
// 	t_fd_node	*temp1;
// 	t_fd_node	*temp2;

// 	list = get_fd_list();
// 	if (list->head->fd = fd)
// 	{
// 		temp1 = list->head;
// 		list->head = temp1->next;
// 		return (free(temp1), 0);
// 	}
// 	temp1 = list->head;
// 	while (temp1)
// 	{
// 		if (temp1->fd == fd)
// 		{
			
// 		}
// 	}
// }
