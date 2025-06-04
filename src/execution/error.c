/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:25:21 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/04 12:06:40 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error(int error_code, char *error_msg)
{
    perror(error_msg);
    gc_free_all();
    // clear_fd_list();
    exit(error_code);
}
