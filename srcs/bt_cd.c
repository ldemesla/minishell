/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:54:32 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/18 11:54:34 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parse_quote_cd(t_all *g_all, int i)
{
	int		j;
	int		k;
	char	mod;

	j = 0;
	k = 0;
	mod = '.';
	ft_init_temp_str(g_all, 2);
	while (g_all->temp_str_1[i])
	{
		if (mod == '.')
			k += ft_parse_quote_cd_cut_1(g_all, &mod, &i, &j);
		else if (mod == '\'')
			k += ft_parse_quote_cd_cut_2(g_all, &mod, &i, &j);
		else if (mod == '"')
			k += ft_parse_quote_cd_cut_3(g_all, &mod, &i, &j);
		else if (mod == '_')
			k += ft_parse_quote_cd_cut_4(g_all, &mod, &i, &j);
		else if (mod == '-')
			k += ft_parse_quote_cd_cut_5(g_all, &mod, &i, &j);
		i++;
	}
	return (k);
}

void	ft_active_slash(t_all *g_all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ft_init_temp_str(g_all, 3);
	while (g_all->temp_str_2[i])
	{
		if (g_all->temp_str_2[i] == '\n')
		{
			g_all->temp_str_3[j] = '\\';
			j++;
			g_all->temp_str_3[j] = 'n';
		}
		else
			g_all->temp_str_3[j] = g_all->temp_str_2[i];
		j++;
		i++;
	}
}

int		ft_no_arg(t_all *g_all)
{
	int i;

	i = 2;
	if (!(g_all->temp_str_1[2]))
		return (TRUE);
	while (g_all->temp_str_1[i])
	{
		if (g_all->temp_str_1[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ft_skip_space(t_all *g_all)
{
	int i;
	int j;
	int start;

	i = 0;
	j = 0;
	start = 0;
	ft_init_temp_str(g_all, 3);
	while (g_all->temp_str_2[i])
	{
		if (g_all->temp_str_2[i] == ' ' && (g_all->temp_str_2[i + 1] == ' ' ||
				g_all->temp_str_2[i + 1] == '\0' || start == 0))
		{
			i++;
			continue;
		}
		start = 1;
		g_all->temp_str_3[j] = g_all->temp_str_2[i];
		i++;
		j++;
	}
	ft_init_temp_str(g_all, 2);
	ft_strcpy(g_all->temp_str_2, g_all->temp_str_3);
	ft_init_temp_str(g_all, 3);
}

int		ft_bt_cd(t_all *g_all)
{
	int			ret;
	const char	*path;

	ft_input_to_temp_str(g_all, 1);
	if (ft_no_arg(g_all))
		path = INITIAL_PATH;
	else
	{
		ft_parse_quote_cd(g_all, 3);
		ft_put_tab(g_all);
		path = (const char*)(g_all->temp_str_2);
	}
	ft_skip_space(g_all);
	if (!(ret = 0) && g_all->mod != '|')
		ret = chdir(path);
	if (ret == -1)
	{
		ft_active_slash(g_all);
		ft_putstr("cd: no such file or directory: ");
		ft_putstr(g_all->temp_str_3);
		ft_putstr("\n");
		return (1);
	}
	return (FALSE);
}
