/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:05:02 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/01 17:08:30 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_error(t_mini *mini)
{
	if (!mini->token_list->error_code)
		return (0);
	else if (mini->token_list->error_code == EC_UNCLOSEQ)
		return(printf("Error: %s\n", ERR_UNCLOSED_QUOTE), gc_free_by_type(GC_PARSE), -1);
	return (0);
}