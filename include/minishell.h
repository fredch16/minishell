/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:38:49 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 22:55:43 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

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

// remember ECHo and echo is the same, same for all builtins

void			print_tokens(t_token_list *list);

#endif