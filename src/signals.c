/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:35:11 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/21 20:13:50y fredchar         ###   ########.fr       */
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

/**
 * Empty SIGQUIT handler to prevent ^\ from being printed
 * This handler does nothing but exists to catch the signal
 */
void	empty_sigquit_handler(int signo)
{
	(void)signo;
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int, sa_quit;
	struct termios		term;

	// Get the current terminal attributes
	tcgetattr(STDIN_FILENO, &term);
	
	// Disable ECHOCTL to prevent control characters from being displayed
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	// Set up SIGINT handler
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = heredoc_sigint_handler;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	// Set up SIGQUIT handler with empty function
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = empty_sigquit_handler;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/**
 * Reset signal handlers and terminal settings for main shell
 */
void	reset_parent_signals(void)
{
	struct sigaction	sa_int, sa_quit;
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
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