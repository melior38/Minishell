/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:17:16 by lcamilo-          #+#    #+#             */
/*   Updated: 2023/06/09 09:55:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_variable	*create_env(char *name, char *value)
{
	t_variable	*tmp;

	tmp = malloc(sizeof(t_variable));
	tmp->name = ft_strdup(name);
	if (value)
		tmp->value = ft_strdup(value);
	else
		tmp->value = NULL;
	tmp->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}

void	env_add_back(t_variable **env, t_variable *new)
{
	t_variable	*current;
	t_variable	*previous;

	if (*env == NULL)
		*env = new;
	else
	{
		previous = *env;
		current = *env;
		while (current->next)
		{
			previous = current;
			current = current->next;
		}
		current->next = new;
		new->prev = current;
	}
}

void	add_to_env(char **args, t_shell *shell)
{
	t_variable	*env;
	t_variable	*head;

	env = shell->env;
	head = shell->env;
	while (env)
	{
		if ((ft_strcmp(env->name, args[0]) == 0))
		{
			free(env->value);
			env->value = NULL;
			if (args[1])
				env->value = ft_strdup(args[1]);
			return ;
		}
		env = env->next;
	}
	shell->env = head;
	if (args[1])
		env_add_back(&shell->env, create_env(args[0], args[1]));
	else
		env_add_back(&shell->env, create_env(args[0], NULL));
}
