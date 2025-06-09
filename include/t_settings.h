/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_settings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 07:18:00 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/08 07:25:10 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SETTINGS_H
# define T_SETTINGS_H

# include "minishell.h"

void    restore_terminal(void);
int     save_terminal_settings(void);

#endif