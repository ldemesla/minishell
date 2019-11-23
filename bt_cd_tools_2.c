/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:18:21 by mabois            #+#    #+#             */
/*   Updated: 2019/11/22 10:18:22 by mabois           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_only_space(t_all *g_all, int i, char mod)
{
	while (g_all->temp_str_1[i] && g_all->temp_str_1[i] != mod)
	{
		if (g_all->temp_str_1[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ft_put_tab(t_all *g_all)
{
	int i;

	i = 0;
	while (g_all->temp_str_2[i])
	{
		if (g_all->temp_str_2[i] == '@')
			g_all->temp_str_2[i] = 9;
		i++;
	}
	if (g_all->temp_str_2[0] == 9 && g_all->temp_str_2[1] == '\0')
		g_all->temp_str_2[0] = '.';
}
