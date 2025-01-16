/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:02:22 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/16 22:00:42 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signo;

void	handle_eof(void)
{
	write(STDOUT_FILENO, "exit\n", 5);
	rl_clear_history();
	exit(0);
}

int	process_empty_input(char *input)
{
	if (!input)
		handle_eof();
	if (!input[0] || input[0] == ':' || input[0] == '!')
	{
		free(input);
		return (1);
	}
	return (0);
}

static void	restore_prompt(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	g_signo = 0;
	signal(SIGINT, restore_prompt);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
