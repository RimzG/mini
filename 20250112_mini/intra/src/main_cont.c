/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cont.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:56:21 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/14 23:11:52 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_shell	shell;

	(void)argc;
	(void)argv;
	initialize_shell(&shell, env);
	while (1)
	{
		input = readline(PROMPT);
		if (g_signo == SIGINT)
			shell.exit_status = 130;
		g_signo = 0;
		if (process_empty_input(input))
			continue ;
		if (input[0] != '\0')
			process_valid_input(input, &shell);
		free(input);
	}
	free_args(shell.env);
	return (0);
}