/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:23:06 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/30 15:53:41 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_var(t_token_list *token_list, char *variable)
{
	char	*expanded;
	int		i;
	int		len;

	if (!token_list->env)
	{
		expanded = ft_strdup("");
		return (gc_track(expanded), expanded);
	}
	len = ft_strlen(variable);
	i = 0;
	while (token_list->env[i])
	{
		if (ft_strncmp(token_list->env[i], variable, len) == 0
			&& token_list->env[i][len] == '=')
		{
			expanded = ft_strdup(token_list->env[i] + len + 1);
			return (gc_track(expanded), expanded);
		}
		i++;
	}
	expanded = ft_strdup("");
	return (gc_track(expanded), expanded);
}

//extract var NOT INCLUDING THE DOLLAR, JUST THE NAME
char	*extract_var(char *content)
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
	variable = (char *)gc_malloc(sizeof(char) * (i + 1));
	if (!variable)
		return (NULL);
	ft_strlcpy(variable, content, i + 1);
	return (variable);
}
