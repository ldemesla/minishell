/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:13:24 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/20 16:36:39 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char(char c, int quotes)
{
	if (quotes == 1)
	{
		if (c == '\'' || c == '\"')
			return (1);
	}
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	check_export(t_all *all)
{
	if (all->temp_str_1[6] == '\0')
	{
		print_env_export(all);
		return (1);
	}
	else
		return (0);
}
