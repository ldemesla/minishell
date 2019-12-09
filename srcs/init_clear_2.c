/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clear_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:12:08 by mabois            #+#    #+#             */
/*   Updated: 2019/11/20 16:37:24 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_bt_export_path(t_all *g_all)
{
	int i;

	i = 6;
	ft_strcpy(g_all->temp_str_1, "export PATH=/Users/mabois/.brew/bin:/usr\
/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");
	while (g_all->temp_str_1[i])
	{
		while (g_all->temp_str_1[i] == ' ')
			i++;
		if (is_char(g_all->temp_str_1[i], 0))
		{
			if ((i = save_env(i, g_all)) <= 0)
			{
				if (i == -1)
					write(1, "zsh: bad assignment\n", 20);
			}
			return (0);
		}
		else
		{
			i = wrong_identifier(i, g_all);
			return (1);
		}
	}
	return (check_export(g_all));
}
