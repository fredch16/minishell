/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverting_stds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 07:19:27 by apregitz          #+#    #+#             */
/*   Updated: 2025/06/07 07:39:49 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_fd(int fd)
{
	struct stat	st;

	return (fstat(fd, &st));
}

int	reverting_stds(void)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 1024)
	{
		if (check_fd(i) == 0)
			close(i);
		i++;
	}
	fd = open("/dev/tty", O_RDONLY);
	if (fd == -1)
		ft_error(1, "open", 0);
	dup2(fd, STDIN_FILENO);
	fd = open("/dev/tty", O_WRONLY);
	if (fd == -1)
		ft_error(1, "open", 0);
	dup2(fd, STDOUT_FILENO);
	fd = open("/dev/tty", O_WRONLY);
	if (fd == -1)
		ft_error(1, "open", 0);
	dup2(fd, STDERR_FILENO);
	return (0);
}
