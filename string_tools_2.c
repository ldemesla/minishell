/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:00:59 by mabois            #+#    #+#             */
/*   Updated: 2019/11/21 15:57:57 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(char *s, t_all *g_all, int j)
{
	t_export	*temp;
	int			i;

	temp = g_all->env;
	i = 0;
	j = 0;
	if (ft_compare_str(s, 1, "?") || ft_compare_str(s, 2, "?\"") ||
	ft_compare_str(s, 2, "?\""))
		return (write_ret(g_all));
	while (temp)
	{
		if (ft_compare_str(temp->name, ft_strlen(temp->name), s))
		{
			while (temp->name[i])
				i++;
			if (s[i] == '\0' || s[i] == ' ' || s[i] == '\'' || s[i] == '\"'
			|| s[i] == '\\' || s[i] == '$')
				return (temp->value);
		}
		temp = temp->next;
	}
	return (" ");
}

int		replace_env(t_all *g_all, int i, char *s)
{
	int j;
	int k;
	int ret;

	j = 0;
	k = i;
	i++;
	while (g_all->temp_str_1[i] != ' ' && g_all->temp_str_1[i] != '\0' &&
	g_all->temp_str_1[i] != '\'' && g_all->temp_str_1[i] != '\"' &&
	g_all->temp_str_1[i] != '\\' && g_all->temp_str_1[i] != '$')
		i++;
	while (g_all->temp_str_1[i])
		g_all->temp_str_2[j++] = g_all->temp_str_1[i++];
	g_all->temp_str_2[j] = '\0';
	i = k;
	j = 0;
	while (s[j])
		g_all->temp_str_1[k++] = s[j++];
	ret = k;
	j = 0;
	while (g_all->temp_str_2[j])
		g_all->temp_str_1[k++] = g_all->temp_str_2[j++];
	g_all->temp_str_1[k] = '\0';
	return (ret);
}

void	set_env(t_all *g_all)
{
	int		i;
	char	*s;

	i = 0;
	s = 0;
	while (g_all->temp_str_1[i])
	{
		if (g_all->temp_str_1[i] == '$' && g_all->temp_str_1[i - 1] != '\\')
		{
			s = find_env(g_all->temp_str_1 + i + 1, g_all, i - 1);
			i = replace_env(g_all, i, s) - 1;
		}
		i++;
	}
}

void	ft_input_to_temp_str(t_all *g_all, int mod)
{
	int i;
	int s;
	int len;

	i = 0;
	s = 0;
	len = g_all->end - g_all->start;
	ft_init_temp_str(g_all, 1);
	while (s < len && g_all->input[g_all->start + s] == ' ')
		s++;
	while (i + s < len)
	{
		if (g_all->input[g_all->start + i + s] == '<' && mod == 0)
			g_all->temp_str_1[i] = ' ';
		else if (g_all->input[g_all->start + i + s] == '<' && mod == 1)
			g_all->temp_str_1[i] = '\0';
		else
			g_all->temp_str_1[i] = g_all->input[g_all->start + i + s];
		i++;
	}
	set_env(g_all);
	set_path(g_all);
}

void	ft_strcpy(char *dst, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
