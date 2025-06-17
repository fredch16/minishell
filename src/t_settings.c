/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_settings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 07:08:21 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/08 07:46:00 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_t_settings	*get_t_settings(void)
{
	static t_t_settings	t_settings;

	return (&t_settings);
}

void	restore_terminal(void)
{
	t_t_settings	*t_settings;

	t_settings = get_t_settings();
	if (t_settings->termios_saved)
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &t_settings->termios);
		t_settings->termios_saved = 0;
	}
}

int	save_terminal_settings(void)
{
	t_t_settings	*t_settings;

	t_settings = get_t_settings();
	if (tcgetattr(STDIN_FILENO, &t_settings->termios) == -1)
		ft_error(1, "tcgetattr", 0);
	t_settings->termios_saved = 1;
	return (0);
}
