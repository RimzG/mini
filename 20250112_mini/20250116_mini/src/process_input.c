/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 22:03:44 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/17 00:08:45 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input(char *input, t_shell *shell)
{
	char	**args;

	add_history(input);
	if (!syntax_error(input))
	{
		shell->input_start = input;
		args = get_args(input);
		if (args)
		{
			shell->exit_status = execute_command(args, shell);
			free_args(args);
		}
		free_args(args);
		}
	
	else
		shell->exit_status = 2;
}
