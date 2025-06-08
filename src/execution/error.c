/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:25:21 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/08 05:48:09 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void process_mode(int mode)
{
	if (mode == 0b0001)
		gc_free_all();
}

void	ft_error(int error_code, char *error_msg, int mode)
{
	process_mode(mode);
	perror(error_msg);
	exit(error_code);
}
