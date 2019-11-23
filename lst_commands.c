/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:03:57 by mabois            #+#    #+#             */
/*   Updated: 2019/11/19 14:03:58 by mabois           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_export **lst)
{
	t_export *temp;
	t_export *next;

	if (lst == NULL || *lst == NULL)
		return ;
	next = *lst;
	while (next)
	{
		temp = next;
		next = temp->next;
		free(temp);
	}
	*lst = 0;
}
