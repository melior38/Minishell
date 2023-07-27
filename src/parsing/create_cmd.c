/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:17:16 by lcamilo-          #+#    #+#             */
/*   Updated: 2023/06/08 09:04:09 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*skip_pipe(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->cmd[0] == '|')
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

int	check_redir(t_cmd *cmd)
{
	if (cmd->prev && (cmd->prev->cmd[0] == '<' || cmd->prev->cmd[0] == '>'))
		return (0);
	if ((cmd->cmd[0] == '>' || cmd->cmd[0] == '<')
		&& cmd->prev && cmd->prev->prev
		&& (cmd->prev->prev->cmd[0] == '>' || cmd->prev->prev->cmd[0] == '<'))
		return (0);
	if (cmd->cmd[0] == '|' || cmd->cmd[0] == ' '
		|| cmd->cmd[0] == '>' || cmd->cmd[0] == '<')
		return (0);
	return (1);
}

char	**get_cmd_args(t_cmd *cmd)
{
	char	**cmd_args;
	int		i;

	if (!count_args(cmd))
		return (NULL);
	cmd_args = malloc(sizeof(char *) * (count_args(cmd) + 1));
	if (!cmd_args)
		return (NULL);
	i = 0;
	while (cmd)
	{
		if (check_redir(cmd))
		{
			cmd_args[i] = ft_strdup(cmd->cmd);
			i++;
		}
		if (cmd->cmd[0] == '|')
			break ;
		cmd = cmd->next;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

void	create_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*redir;
	char	**cmd_args;

	cmd = shell->cmd;
	while (cmd)
	{
		cmd_args = get_cmd_args(cmd);
		redir = create_redir(cmd);
		exec_add_back(&shell->exec, exec_create(cmd_args, redir));
		cmd = skip_pipe(cmd);
		if (cmd)
			cmd = cmd->next;
	}
}
