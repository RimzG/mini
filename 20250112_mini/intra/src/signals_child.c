/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:02:22 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/23 21:57:09 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_sigint(int signo)
{
	if (signo == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

static void	handle_child_sigquit(int signo)
{
	if (signo == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 18);
		exit(131);
	}
}

void	setup_child_signals(void)
{
	signal(SIGINT, handle_child_sigint);
	signal(SIGQUIT, handle_child_sigquit);
}
