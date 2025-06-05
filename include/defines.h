/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:25:34 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/05 08:16:33 by apregitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

// String defines

// Error Messages

# define ERR_UNCLOSED_QUOTE "Syntax Error. Unclosed quote in prompt"
# define ERR_PIPE_AT_START "Syntax Error. Pipe at begging of input"
# define ERR_SYNTAX_PIPE "Syntax Error. Pipe needs action to follow"
# define ERR_SYNTAX_REDIR "Syntax Error. Redirect needs argument"
# define ERR_PIPE_AT_END "Syntax Error. Pipe at end of input"
# define ERR_MALLOC "Malloc Failed."

// Error Codes

# define EC_UNCLOSEQ 740
# define EC_PIPE_AT_START 741
# define EC_SYNTAX_PIPE 742
# define EC_SYNTAX_REDIR 743
# define EC_PIPE_AT_END 744
# define EC_MALLOC 999

// error function mode codes
# define EC_GC 0b0001
# define EC_FD 0b0010

#endif