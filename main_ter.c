/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:33:23 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/20 18:33:39 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_term(char *buffer)
{
	int res;

	res = read(0, buffer, 1);
	if (*buffer == '\n' || *buffer == '\0')
	{
		write(1, "> ", 2);
		res = read(0, buffer, 1);
		if (*buffer == '\\')
			return (new_term(buffer));
	}
	return (res);
}
