/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:05:07 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/16 21:09:43 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_node(char *env_var)
{
    t_env	*new_node; 

	if (env_var == NULL)
		return (NULL);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->env_value = ft_strdup(env_var);
	if (new_node->env_value == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_env	*append_node(t_env *head, char *env_var)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_node(env_var);
	if (new_node == NULL)
		return (NULL);    
	if (head == NULL)
        return (new_node);
    current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (head);
}

void	free_envp(t_env *head)
{
    t_env	*current;
	t_env	*temp;

	current = head;
    while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->env_value);
		free(temp);
	}
}

void	print_envp(t_env *head)
{
    t_env	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->env_value);
		current = current->next;
	}
}

t_env	*create_envp(char **envp)
{
    t_env	*head;
	int		i;	

	i = 0;
	head = NULL;
	if (!envp)
		return (NULL);
    while (envp[i] != NULL)
	{
        head = append_node(head, envp[i]);
		i++;
    }
	return (head);
}
