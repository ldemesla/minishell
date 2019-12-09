/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:14:01 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/18 12:14:52 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quotes(t_redir *data, t_all *g_all)
{
	if (g_all->temp_str_1[0] == '\'')
	{
		data->sq = 1;
		data->dq = 0;
	}
	else if (g_all->temp_str_1[0] == '\"')
	{
		data->dq = 1;
		data->sq = 0;
	}
	else
	{
		data->dq = 0;
		data->sq = 0;
	}
}

void	remove_quotes(t_all *g_all)
{
	t_redir data;
	int		i;
	int		j;

	i = 0;
	j = 0;
	init_quotes(&data, g_all);
	if (data.sq == 1 || data.dq == 1)
		i++;
	while (g_all->temp_str_1[i])
	{
		if ((data.sq == 1 && g_all->temp_str_1[i] == '\'') || (data.dq == 1 &&
		g_all->temp_str_1[i] == '\"') || (data.sq == 0 && data.dq == 0 &&
		g_all->temp_str_1[i] == ' '))
			break ;
		g_all->temp_str_1[j] = g_all->temp_str_1[i];
		i++;
		j++;
	}
	while (j < MAX_LEN_TEMP_STR)
		g_all->temp_str_1[j++] = '\0';
}

void	error_redir(t_all *g_all)
{
	int		i;
	char	c;

	i = 0;
	c = ' ';
	if (g_all->last_is_echo != 1)
		return ;
	ft_putstr("zsh: no such file or directory: ");
	while (g_all->temp_str_1[i] == ' ')
		i++;
	if (g_all->temp_str_1[i] == '\'')
		c = '\'';
	else if (g_all->temp_str_1[i] == '\"')
		c = '\"';
	if (c != ' ')
		i++;
	while (g_all->temp_str_1[i] && g_all->temp_str_1[i] != c)
		write(1, &g_all->temp_str_1[i++], 1);
	write(1, "\n", 1);
	g_all->last_is_echo = 0;
}

void	create_file(t_all *g_all)
{
	int fd;

	fd = 0;
	ft_input_to_temp_str(g_all, 1);
	remove_quotes(g_all);
	if (g_all->last_is_rdr == 1)
		fd = open(g_all->temp_str_1, O_WRONLY | O_APPEND | O_TRUNC | O_CREAT,
		0644);
	else if (g_all->last_is_rdr == 3)
	{
		if (open(g_all->temp_str_1, O_RDWR) <= 0 &&
		opendir(g_all->temp_str_1) <= 0)
		{
			error_redir(g_all);
			return ;
		}
	}
	else
		fd = open(g_all->temp_str_1, O_WRONLY | O_APPEND | O_CREAT, 0644);
	write(fd, g_all->str_for_pipe, ft_strlen(g_all->str_for_pipe));
	close(fd);
}
