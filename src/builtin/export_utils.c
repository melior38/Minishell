/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asouchet <asouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:17:16 by lcamilo-          #+#    #+#             */
/*   Updated: 2023/05/22 15:53:03 by asouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(t_variable *a, t_variable *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

void	bubblesort(t_variable *head)
{
	int			swapped;
	t_variable	*ptr1;
	t_variable	*lptr;

	lptr = NULL;
	swapped = 1;
	if (head == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->name, ptr1->next->name) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void	printlist(t_variable *node)
{
	t_variable	*head;

	head = node;
	while (node != NULL)
	{
		if (node->value)
			printf("declare -x %s=\"%s\"\n", node->name, node->value);
		else
		{
			if (degeu(node->name))
				printf("declare -x %s=\"\"\n", node->name);
			else
				printf("declare -x %s\n", node->name);
		}
		node = node->next;
	}
	node = head;
}

int	ft_is_alphanum_(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	return (0);
}

int	check_non_authorized_names(char *str, int *i)
{
	unsigned int	j;

	j = 0;
	if (!(str[0] <= '9' && str[0] >= '0'))
		while (str[j] && ft_is_alphanum_(str[j]))
			++j;
	if (!j || (str[j] && str[j] != '='))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_error_num = 1;
		++(*i);
		return (1);
	}
	return (0);
}
