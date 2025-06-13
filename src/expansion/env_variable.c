/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:23:06 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/13 14:10:59 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//extract var NOT INCLUDING THE DOLLAR, JUST THE NAME
char	*extract_var(t_token_list *tlist, char *content)
{
	int		i;
	char	*variable;

	i = 0;
	if (*content != '$')
		return (NULL);
	content++;
	if (!(ft_isalpha(content[0]) && content[0] != '_'))
		return (NULL);
	while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
		i++;
	variable = (char *)gc_malloc(sizeof(char) * (i + 1), GC_PARSE);
	if (!variable)
		return (tk_err(tlist, EC_MALLOC), NULL);
	ft_strlcpy(variable, content, i + 1);
	return (variable);
}
