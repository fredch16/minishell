/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_settings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 07:18:00 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/17 02:30:08 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_SETTINGS_H
# define T_SETTINGS_H

# include "minishell.h"

void	restore_terminal(void);
int		save_terminal_settings(void);

#endif