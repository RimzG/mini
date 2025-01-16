/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:02:22 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/28 00:14:36 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_sigint(int signo)
{
	if (signo == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}
