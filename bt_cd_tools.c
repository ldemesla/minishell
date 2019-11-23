/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:54:39 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/18 11:55:06 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parse_quote_cd_cut_1(t_all *g_all, char *mod, int *i, int *j)
{
	int ii;
	int jj;

	ii = *i;
	jj = *j;
	if (g_all->temp_str_1[ii] == '\'')
	{
		if (g_all->temp_str_1[ii + 1] == '\'')
			g_all->temp_str_2[jj++] = '@';
		*mod = '\'';
	}
	else if (g_all->temp_str_1[ii] == '"')
	{
		if (g_all->temp_str_1[ii + 1] == '"')
			g_all->temp_str_2[jj++] = '@';
		*mod = '"';
	}
	else
		g_all->temp_str_2[jj++] = g_all->temp_str_1[ii];
	*i = ii;
	*j = jj;
	return (0);
}

int		ft_parse_quote_cd_cut_2(t_all *g_all, char *mod, int *i, int *j)
{
	int ii;
	int jj;
	int ret;

	ii = *i;
	jj = *j;
	ret = 0;
	if (g_all->temp_str_1[ii] == '\'')
	{
		ret = 1;
		*mod = '_';
	}
	else if (ft_only_space(g_all, *i, *mod) == TRUE)
		g_all->temp_str_2[jj++] = '@';
	else
		g_all->temp_str_2[jj++] = g_all->temp_str_1[ii];
	*i = ii;
	*j = jj;
	return (ret);
}

int		ft_parse_quote_cd_cut_3(t_all *g_all, char *mod, int *i, int *j)
{
	int ii;
	int jj;
	int ret;

	ii = *i;
	jj = *j;
	ret = 0;
	if (g_all->temp_str_1[ii] == '"')
	{
		ret = 1;
		*mod = '_';
	}
	else if (ft_only_space(g_all, *i, *mod) == TRUE)
		g_all->temp_str_2[jj++] = '@';
	else
		g_all->temp_str_2[jj++] = g_all->temp_str_1[ii];
	*i = ii;
	*j = jj;
	return (ret);
}

int		ft_parse_quote_cd_cut_4(t_all *g_all, char *mod, int *i, int *j)
{
	int ii;
	int jj;

	ii = *i;
	jj = *j;
	if (g_all->temp_str_1[ii] == '\'')
	{
		if (((*mod = '\'') != -4) && g_all->temp_str_1[ii + 1] == '\'')
			g_all->temp_str_2[jj++] = '@';
	}
	else if (g_all->temp_str_1[ii] == '"')
	{
		if (((*mod = '"') != -4) && g_all->temp_str_1[ii + 1] == '"')
			g_all->temp_str_2[jj++] = '@';
	}
	else
	{
		g_all->temp_str_2[jj++] = g_all->temp_str_1[ii];
		*mod = '.';
	}
	if (g_all->temp_str_1[ii] == ' ')
		*mod = '-';
	*i = ii;
	*j = jj;
	return (0);
}

int		ft_parse_quote_cd_cut_5(t_all *g_all, char *mod, int *i, int *j)
{
	int ii;
	int jj;

	ii = *i;
	jj = *j;
	if (g_all->temp_str_1[ii] == '\'')
	{
		if (g_all->temp_str_1[ii + 1] == '\'')
			g_all->temp_str_2[jj++] = '@';
		*mod = '\'';
	}
	else if (g_all->temp_str_1[ii] == '"')
	{
		if (g_all->temp_str_1[ii + 1] == '"')
			g_all->temp_str_2[jj++] = '@';
		*mod = '"';
	}
	else if (g_all->temp_str_1[ii] != ' ')
	{
		g_all->temp_str_2[jj++] = g_all->temp_str_1[ii];
		*mod = '.';
	}
	*i = ii;
	*j = jj;
	return (0);
}
