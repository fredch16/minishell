/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 23:38:38 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/07 19:11:58 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include "minishell.h"


void	setup_signals(void);
void	handle_sigint(int signo);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);

#endif