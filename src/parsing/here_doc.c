/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamilo- <marvin@42.fr>      8======D      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:17:16 by lcamilo-          #+#    #+#             */
/*   Updated: 2023/01/16 11:17:18 by lcamilo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*import_heredoc(t_cmd *cmd, char *hd)
{
	t_redir	*heredoc;
	t_redir	*redir;

	redir = NULL;
	heredoc = redir_create(NULL, 3, hd);
	while (cmd)
	{
		if (cmd->cmd[0] == '|')
			break ;
		if (cmd->cmd[0] == '>' || cmd->cmd[0] == '<')
		{
			redir = redirection(redir, cmd);
			redir_add_back(&heredoc, redir);
			break ;
		}
		cmd = cmd->next;
	}
	return (heredoc);
}

char	*execute_heredoc(char *rd, char *limiter)
{
	char	*nl;
	char	*str;
	size_t	len;

	str = ft_strdup("");
	while (1)
	{
		nl = malloc(sizeof(char *) * (ft_strlen(rd) + 1));
		nl = ft_memcpy(nl, rd, ft_strlen(rd));
		len = ft_strlen(rd);
		nl[len] = '\n';
		nl[len + 1] = '\0';
		str = ft_strjoin(str, nl);
		free(rd);
		rd = NULL;
		rd = readline("> ");
		if (!rd || g_error_num == 130)
			return (NULL);
		if (ft_strncmp(rd, limiter, ft_strlen(limiter)) == 0)
			break ;
	}
	return (str);
}

//Faire comme varialbe d'env (rajouter dans linked list a la suite)
t_redir	*here_doc(t_cmd *tmp, char *limiter)
{
	char	*rd;
	char	*str;

	(void) tmp;
	run_signals(2);
	printf("Limiter [%s]\n", limiter);
	rd = readline("> ");
	if (!rd || g_error_num == 130)
		return (NULL);
	if (ft_strncmp(rd, limiter, ft_strlen(limiter)) == 0)
		return (redir_create(NULL, 3, NULL));
	str = execute_heredoc(rd, limiter);
	return (redir_create(NULL, 3, str));
}
