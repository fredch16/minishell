/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+          */
/*   Created: 2025/06/07 16:35:11 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/07 19:10:43 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern volatile sig_atomic_t g_signal_recieved;

void	handle_sigint(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_sigint_hanlder(int signo)
{
	(void)signo;
	g_signal_recieved = 1;
}

/**
 * Set up signal handlers for when the shell is executing commands
 * This prevents the shell from reacting to signals meant for child processes
 */
void	setup_parent_signals_for_execution(void)
{
	signal(SIGINT, SIG_IGN);  // Ignore SIGINT in the parent during execution
	signal(SIGQUIT, SIG_IGN); // Continue ignoring SIGQUIT
}

/**
 * Reset signal handlers for when the shell is ready for input
 */
void	reset_parent_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, heredoc_sigint_hanlder);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
