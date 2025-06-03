/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:05:02 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/02 16:57:38 by apregitz         ###   ########.fr       */
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