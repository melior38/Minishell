/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:17:16 by lcamilo-          #+#    #+#             */
/*   Updated: 2023/05/22 17:02:10 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*redir_create(char *file, int cases, char *hd)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (file)
		redir->file = ft_strdup(file);
	else
		redir->file = ft_strdup("");
	redir->cases = cases;
	if (hd)
		redir->here_doc = hd;
	else
		redir->here_doc = ft_strdup("");
	redir->next = NULL;
	redir->prev = NULL;
	return (redir);
}

void	redir_add_back(t_redir **redir, t_redir *new)
{
	t_redir	*current;
	t_redir	*tmp_previous;

	if (*redir == NULL)
		*redir = new;
	else
	{
		tmp_previous = *redir;
		current = *redir;
		while (current->next)
		{
			tmp_previous = current;
			current = current->next;
		}
		current->next = new;
		current->prev = tmp_previous;
	}
}
