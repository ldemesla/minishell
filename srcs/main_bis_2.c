/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:22:14 by mabois            #+#    #+#             */
/*   Updated: 2019/11/20 15:22:16 by mabois           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_commas_init(int *i, char *c)
{
	*i = g_all.start;
	*c = '\0';
}

int		ft_check_commas(void)
{
	int		i;
	char	c;

	ft_check_commas_init(&i, &c);
	while (g_all.input[i])
	{
		if (g_all.input[i] == '\'')
			c = '\'';
		if (g_all.input[i] == '\"')
			c = '\"';
		if (c != '\0')
			i++;
		while (g_all.input[i] != c && g_all.input[i] && c != '\0')
			i++;
		if (g_all.input[i] == '\'' || g_all.input[i] == '\"')
			i++;
		c = '\0';
		if (g_all.input[i] == ';')
			return (set_mod(i));
		else if (g_all.input[i] == '\'' || g_all.input[i]
		== '\"')
			continue ;
		i++;
	}
	return (0);
}
