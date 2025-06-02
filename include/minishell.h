/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:38:49 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/01 13:05:08 by apregitz         ###   ########.fr       */
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

# include "../src/libft/libft.h"
# include "garbage_collector.h"
# include "struct.h"
# include "parser.h"
# include "expansion.h"
# include "env_list.h"
# include "execution.h"

// remember ECHo and echo is the same, same for all builtins

void			print_tokens(t_token_list *list);


#endif