/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:17:16 by lcamilo-          #+#    #+#             */
/*   Updated: 2023/06/01 10:41:05 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exit_code(char **args)
{
	unsigned int	i;

	if (!args || !args[1])
		return (g_error_num);
	i = 0;
	if ((args[1][0] == '-' || args[1][0] == '+') && args[1][1])
		i++;
	while (args[1][i] && (args[1][i] >= '0' && args[1][i] <= '9'))
		i++;
	if (args[1][i])
	{
		perror("exit: numeric argument required");
		return (255);
	}
	return (ft_atoi(args[1]));
}

void	ft_exit(t_shell *shell, char **args)
{
	int	code;

	code = check_exit_code(args);
	if (code != 255 && args && args[1] && args[2])
	{
		perror("exit: too many arguments");
		g_error_num = 1;
		return ;
	}
	ft_printf("Salam khouya j'espere ta kiffer ;) (mets 100 stp)\n");
	free_cmd(shell);
	free_exec(shell);
	free(shell->read);
	clear_history();
	exit(code % 256);
}
