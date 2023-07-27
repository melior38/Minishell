/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:17:16 by lcamilo-          #+#    #+#             */
/*   Updated: 2023/06/09 09:54:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**degeu_plus_plus(char **args)
{
	char	**ret;

	ret = malloc(sizeof(char *) * 3);
	ret[0] = ft_strtrim(args[1], "=");
	ret[1] = ft_strdup("");
	ret[2] = NULL;
	return (ret);
}

int	degeu(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (str[i] == '=')
		return (1);
	return (0);
}

void	print_export(t_shell *shell)
{
	t_variable	*env;

	env = shell->env;
	bubblesort(env);
	printlist(env);
}

char	**parse_args(char **args)
{
	char	**ret;

	ret = NULL;
	if (degeu(args[1]))
		ret = degeu_plus_plus(args);
	else
		ret = ft_split(args[1], '=');
	return (ret);
}

void	ft_export(t_shell *shell, char **args)
{
	int		i;
	char	**tmp;

	g_error_num = 0;
	i = 0;
	tmp = NULL;
	if (args[1] && args[1][0] != '#')
	{
		tmp = parse_args(args);
		if (!check_non_authorized_names(tmp[i], &i))
			add_to_env(tmp, shell);
		i = 0;
		while (tmp[i])
		{
			free(tmp[i]);
			tmp[i] = NULL;
			i++;
		}
		free(tmp);
		tmp = NULL;
	}
	else
		print_export(shell);
}
