/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:38:49 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/08 07:38:28 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
#define _POSIX_C_SOURCE 200809L


# include "libft/libft.h"
# include "garbage_collector.h"
# include "struct.h"
# include "lexical_analysis.h"
# include "expansion.h"
# include "debug.h"
# include "env_list.h"
# include "defines.h"
# include "utilities.h"
# include "parser.h"
# include "execution.h"
# include "builtins.h"
# include "signals.h"
# include "redirects.h"
# include "t_settings.h"

# ifndef DEBUG
#  define DEBUG 0
# endif

void			print_tokens(t_token_list *list);


#endif