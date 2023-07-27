/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:17:16 by lcamilo-          #+#    #+#             */
/*   Updated: 2023/06/08 10:48:21 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_shell *shell, char *var_name)
{
	if (!get_env_value(shell, var_name))
	{
		ft_printf("cd : %s not set\n", var_name);
		return (NULL);
	}
	return (get_env_value(shell, var_name));
}

void	update_env_value(t_shell *shell, char *name, char *value)
{
	t_variable	*env;

	env = shell->env;
	while (env)
	{
		if (!ft_strcmp(env->name, name))
		{
			free(env->value);
			env->value = NULL;
			env->value = ft_strdup(value);
			break ;
		}
		env = env->next;
	}
}

void	chdir_part(t_shell *shell, char *path_updated, char *new_path)
{
	char	*path_now;
	char	buffer[2048];
	char	*old_pwd;

	old_pwd = getcwd(buffer, sizeof(buffer));
	old_pwd = stock_pwd(old_pwd);
	path_now = NULL;
	if (!chdir(new_path))
	{
		path_now = getcwd(buffer, sizeof(buffer));
		path_updated = ft_new_path(shell, new_path, path_now);
		update_env_value(shell, "PWD", path_updated);
		update_env_value(shell, "OLDPWD", old_pwd);
	}
	else
		cd_error(new_path);
	free(old_pwd);
	old_pwd = NULL;
}

void	cd(t_shell *shell, char **cmd)
{
	char	*new_path;
	char	*path_updated;

	g_error_num = 0;
	new_path = NULL;
	path_updated = NULL;
	if (!cmd[1])
		new_path = get_path(shell, "HOME");
	else if (cmd[1][0] == '-' && !cmd[1][1])
		new_path = get_path(shell, "OLDPWD");
	else if (cmd[1])
		new_path = cmd[1];
	if (!new_path)
		return ;
	chdir_part(shell, path_updated, new_path);
}
