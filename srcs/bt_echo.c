/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:55:10 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/21 15:59:39 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_echo(t_echo *echo, t_all *g_all)
{
	echo->to_line = 1;
	echo->s_quote = 0;
	echo->d_quote = 0;
	ft_input_to_temp_str(g_all, 1);
	ft_init_str_for_pipe(g_all);
	g_all->last_is_echo = 1;
	echo->i = 4;
}

void	write_space(t_echo *echo, int *j)
{
	if (g_all.temp_str_1[echo->i] == ' ')
	{
		while (g_all.temp_str_1[echo->i] && g_all.temp_str_1[echo->i] == ' ')
			echo->i++;
		if (g_all.temp_str_1[echo->i] == '\'' ||
		g_all.temp_str_1[echo->i] == '\"' ||
		is_char(g_all.temp_str_1[echo->i], 0) || (g_all.temp_str_1[echo->i] >=
		'0' && g_all.temp_str_1[echo->i] <= '9'))
			g_all.str_for_pipe[(*j)++] = ' ';
	}
}

void	write_until(char c, t_all *g_all, t_echo *echo, int *j)
{
	int k;

	k = 0;
	if (g_all->temp_str_1[echo->i] == c)
		echo->i++;
	while (g_all->temp_str_1[echo->i + k] != c &&
			g_all->temp_str_1[echo->i + k] != '\0')
	{
		if (g_all->temp_str_1[echo->i + k] == '\\' &&
		g_all->temp_str_1[echo->i + k] != ' ' && (k = k + 1))
		{
			if (g_all->temp_str_1[echo->i + k] == 'n')
				g_all->temp_str_1[echo->i + k] = '\n';
			else if (g_all->temp_str_1[echo->i + k] == 't')
				g_all->temp_str_1[echo->i + k] = '\t';
		}
		if (g_all->temp_str_1[echo->i + k])
			g_all->str_for_pipe[(*j)++] = g_all->temp_str_1[echo->i + k];
		echo->i++;
	}
	echo->i = echo->i + k;
	write_space(echo, j);
}

void	write_echo(t_all *g_all, t_echo *echo, int *j)
{
	while (g_all->temp_str_1[echo->i] == ' ')
		echo->i++;
	if (g_all->temp_str_1[echo->i] == '\'')
		write_until('\'', g_all, echo, j);
	else if (g_all->temp_str_1[echo->i] == '\"')
		write_until('\"', g_all, echo, j);
	else
		write_until(' ', g_all, echo, j);
	if (echo->to_line == 1)
		g_all->str_for_pipe[*j] = '\n';
	if (g_all->temp_str_1[echo->i] == '\0')
		*j = 0;
}

int		ft_bt_echo(t_all *g_all)
{
	static int	j = 0;
	t_echo		echo;

	init_echo(&echo, g_all);
	g_all->str_for_pipe[0] = '\n';
	while (g_all->temp_str_1[echo.i] == ' ')
		echo.i++;
	if (g_all->temp_str_1[echo.i] == '-' && g_all->temp_str_1[echo.i + 1] == 'n'
	&& (echo.i += 2))
		echo.to_line = 0;
	while (g_all->temp_str_1[echo.i])
		write_echo(g_all, &echo, &j);
	if (g_all->mod != '|' && g_all->mod != '>' && g_all->mod != 'r' &&
	g_all->mod != '<')
		ft_putstr(g_all->str_for_pipe);
	return (0);
}
