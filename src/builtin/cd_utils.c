/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 09:09:13 by marvin            #+#    #+#             */
/*   Updated: 2023/06/06 09:09:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_new_path(t_shell *shell, char *new_path, char *value)
{
	char	*get;

	get = get_path(shell, "OLDPWD");
	if (!ft_strncmp(new_path, get, ft_strlen(get)))
		return (new_path);
	return (value);
}

char	*stock_pwd(char *old_pwd)
{
	char	*ret;

	ret = ft_strdup(old_pwd);
	return (ret);
}

void	cd_error(char *new_path)
{
	ft_putstr_fd("jean minishell crapaud: cd: ", 2);
	ft_putstr_fd(new_path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
