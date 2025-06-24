/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_struct_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:06:07 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/23 18:15:46 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_hd_line	*create_hd_line(char *content)
{
	t_hd_line	*new;

	new = gc_malloc(sizeof(t_hd_line), GC_EXEC);
	if (!new)
		return (NULL);
	new->line = content;
	new->next = NULL;
	return (new);
}

t_hd_node	*create_hd_node(char *lim)
{
	t_hd_node	*new;

	new = gc_malloc(sizeof(t_hd_node), GC_EXEC);
	if (!new)
		return (NULL);
	new->lines = NULL;
	new->lim = ft_strdup(lim);
	if (!new->lim)
		return (NULL);
	gc_track(new->lim, GC_EXEC);
	new->file_node = NULL;
	new->next = NULL;
	return (new);
}

void	add_line_to_heredoc(t_hd_node *hd_node, char *line)
{
	t_hd_line	*new_line;
	t_hd_line	*current;

	new_line = create_hd_line(line);
	if (!new_line)
		return ;
	if (!hd_node->lines)
	{
		hd_node->lines = new_line;
		return ;
	}
	current = hd_node->lines;
	while (current->next)
		current = current->next;
	current->next = new_line;
}
