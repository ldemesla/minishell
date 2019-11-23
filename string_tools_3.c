/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:29:01 by mabois            #+#    #+#             */
/*   Updated: 2019/11/21 10:29:47 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_tild(t_all *g_all, int i, char *s)
{
	int j;
	int k;

	j = 0;
	k = i + 1;
	while (g_all->temp_str_1[k])
		g_all->temp_str_2[j++] = g_all->temp_str_1[k++];
	g_all->temp_str_2[j] = '\0';
	j = 0;
	k = i + 1;
	while (s[j])
		g_all->temp_str_1[i++] = s[j++];
	while (g_all->temp_str_2[k])
		g_all->temp_str_1[i++] = g_all->temp_str_2[k++];
	g_all->temp_str_1[i] = '\0';
}

void	set_path(t_all *g_all)
{
	int		i;
	char	c;

	i = 0;
	c = ' ';
	while (g_all->temp_str_1[i])
	{
		if (g_all->temp_str_1[i] == '~')
			replace_tild(g_all, i, "/Users/mabois");
		while (g_all->temp_str_1[i] && g_all->temp_str_1[i] != c)
			i++;
		i++;
	}
}
