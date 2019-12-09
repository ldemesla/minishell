/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:29:11 by mabois            #+#    #+#             */
/*   Updated: 2019/11/19 17:29:14 by mabois           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bt_pwd(t_all *g_all)
{
	int i;

	ft_input_to_temp_str(g_all, 1);
	i = 3;
	while (g_all->temp_str_1[i])
	{
		if (g_all->temp_str_1[i] != ' ')
		{
			ft_putstr("pwd: too many arguments\n");
			return ;
		}
		i++;
	}
	ft_putstr(getcwd(g_all->current_path, MAX_LEN_PATH));
	write(1, "\n", 1);
}
