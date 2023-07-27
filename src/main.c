/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:17:16 by lcamilo-          #+#    #+#             */
/*   Updated: 2023/06/09 09:53:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// Check si un token < > | est en fin de commande
/// \param shell Structure shell
/// \return return 1 si il y a une erreur
int	check_error(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmd;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->cmd[0] == '>' || tmp->cmd[0] == '<')
	{
		ft_printf("syntax error near unexpected token `newline\'\n");
		return (1);
	}
	else if (tmp->cmd[0] == '|')
	{
		ft_printf("syntax error near unexpected token `|\'\n");
		return (1);
	}
	else
		return (0);
}

/// Ajoute dans l'historique la commande passé, rentre dans la fonction parsing
/// Fais l'execution et free les linked list
/// \param shell Structure shell
void	parsing(t_shell *shell)
{
	if (shell->read)
		add_history(shell->read);
	shell->cmd = parse_rd(shell);
	if (check_error(shell))
	{
		free_cmd(shell);
		free(shell->read);
		return ;
	}
	if (!check_quotes(shell))
	{
		error_msg(shell, "Quotes error");
		return ;
	}
	parse_cmd(shell);
	execution(shell);
	free_cmd(shell);
	free_exec(shell);
	free(shell->read);
}

/// Initialise les variables de la structure shell
/// \param shell Structure shell
void	init_shell(t_shell *shell, char **env)
{
	static int	i;

	i++;
	shell->pid = NULL;
	shell->level = 0;
	shell->cmd = NULL;
	shell->exec = NULL;
	shell->read = NULL;
	if (!shell->ft_sett_env)
		shell->ft_sett_env = NULL;
	shell->env = init_env(env);
	sh_level_update(shell->env);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void) ac;
	(void) av;
	init_shell(&shell, env);
	while (1)
	{
		run_signals(1);
		shell.read = readline("Jean minishell crapaud:");
		if (!shell.read)
			run_signals(3);
		if (ft_strcmp(shell.read, "exit") == 0)
			break ;
		else if (shell.read && ft_strlen(shell.read) > 0)
			parsing(&shell);
	}
	free(shell.read);
	free_env(&shell);
	return (0);
}
