/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:35:11 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/20 16:58:16 by fredchar         ###   ########.fr       */
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

void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	g_signal_recieved = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	setup_parent_signals_for_execution(void)
{
	struct sigaction	sa_int, sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = SIG_IGN;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	reset_parent_signals(void)
{
	struct sigaction	sa_int, sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int, sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = heredoc_sigint_handler;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	setup_child_signals(void)
{
	struct sigaction	sa_int, sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = SIG_DFL;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_DFL;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	setup_signals(void)
{
	struct sigaction	sa_int, sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}