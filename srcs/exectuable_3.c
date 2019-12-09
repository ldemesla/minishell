/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exectuable_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:25:38 by mabois            #+#    #+#             */
/*   Updated: 2019/11/20 15:25:39 by mabois           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_search_path_in_env(t_all *g_all)
{
	t_export *temp;

	temp = g_all->env;
	while (temp)
	{
		if (ft_compare_str(temp->name, 4, "PATH"))
			return (temp->value);
		temp = temp->next;
	}
	printf("ERROR PATH NOT FOUND\n");
	return (FALSE);
}

int		ft_search_exec_path_abs_rel(t_all *g_all)
{
	int j;
	int k;

	ft_init_temp_str(g_all, 3);
	ft_init_exec_path(g_all);
	k = 0;
	j = 0;
	while (g_all->temp_str_1[k] && g_all->temp_str_1[k] != ' ')
		g_all->temp_str_3[j++] = g_all->temp_str_1[k++];
	if (stat(g_all->temp_str_3, &(g_all->sb)) == 0)
	{
		ft_strcpy(g_all->exec_path, g_all->temp_str_3);
		return (FALSE);
	}
	return (TRUE);
}

int		ft_search_exec_path(t_all *g_all, int i, int j, int k)
{
	char *all_path;

	if ((all_path = ft_search_path_in_env(g_all)) == NULL)
		return (FALSE);
	while (all_path[i])
		if (!(k = 0) && (all_path[i] == ':' || i == 5))
		{
			g_all->temp_str_3[j++] = '/';
			while (g_all->temp_str_1[k] && g_all->temp_str_1[k] != ' ')
				g_all->temp_str_3[j++] = g_all->temp_str_1[k++];
			if (i++ > 0 && stat(g_all->temp_str_3, &(g_all->sb)) == 0)
			{
				ft_strcpy(g_all->exec_path, g_all->temp_str_3);
				return (FALSE);
			}
			ft_init_exec_path(g_all);
			ft_init_temp_str(g_all, 3);
			j = 0;
		}
		else
			g_all->temp_str_3[j++] = all_path[i++];
	return (TRUE);
}
