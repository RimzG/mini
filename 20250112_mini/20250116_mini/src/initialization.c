/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:01:55 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/16 22:00:33 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_shell(t_shell *shell, char **envp)
{
	char	*shlvl_str;
	char	*new_level;
	int		level;
	t_env	*env_node;

	shell->exit_status = 0;
	shell->envp = create_envp(envp);
	if (!shell->envp)
		return ;
	env_node = shell->envp;
	while (env_node != NULL)
	{
		if (ft_strncmp(env_node->env_value, "SHLVL=", 6) == 0)
		{
			shlvl_str = env_node->env_value + 6;
			level = ft_atoi(shlvl_str) + 1;
			new_level = ft_itoa(level);
			if (!new_level)
				return ;
			if (ft_setenv("SHLVL", new_level, shell->envp) != 0)
			{
				perror("setenv");
				free(new_level);
				return ;
			}
			free(new_level);
			break ;
		}
		env_node = env_node->next;
	}
	setup_signals();
}



// void	process_valid_input(char *input, t_shell *shell)
// {
// 	t_token	*tokens;
// 	char	**args;

// 	add_history(input);
// 	if (!syntax_check(input))
// 	{
// 		shell->input_start = input;
// 		tokens = tokenize_input(input, shell);
// 		if (tokens)
// 		{
// 			args = tokens_to_args(tokens);
// 			if (args)
// 			{
// 				shell->exit_status = execute_command(args, shell);
// 				free_args(args);
// 			}
// 			free_tokens(tokens);
// 		}
// 	}
// 	else
// 		shell->exit_status = 2;
// }
