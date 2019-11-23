/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:02:55 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/18 12:03:17 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*write_ret(t_all *g_all)
{
	int	nb;
	int len;

	nb = g_all->ret;
	len = 0;
	if (nb == 0)
		len = 1;
	while (nb)
	{
		nb = nb / 10;
		len++;
	}
	g_all->temp_str_3[len--] = '\0';
	nb = g_all->ret;
	while (len >= 0)
	{
		g_all->temp_str_3[len--] = nb % 10 + 48;
		nb = nb / 10;
	}
	return (g_all->temp_str_3);
}
