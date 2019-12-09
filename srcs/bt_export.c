/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:11:05 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/20 17:34:05 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		write_env(int i, t_all *g_all)
{
	int		j;
	char	c;

	j = 0;
	c = set_separator(&i, g_all);
	while (g_all->temp_str_1[i] != c)
		g_all->env->name[j++] = g_all->temp_str_1[i++];
	i++;
	if (c != '=')
		i++;
	j = 0;
	c = set_separator(&i, g_all);
	while (g_all->temp_str_1[i] != '\0' && g_all->temp_str_1[i] != ' '
	&& g_all->temp_str_1[i] != c)
		g_all->env->value[j++] = g_all->temp_str_1[i++];
	delete_double(g_all);
	return (i);
}

void	ft_bzero_env(t_all *g_all)
{
	int i;

	i = 0;
	while (i < 50)
	{
		g_all->env->name[i] = '\0';
		g_all->env->value[i] = '\0';
		i++;
	}
}

int		save_env(int i, t_all *g_all)
{
	t_export	*temp;
	t_export	*new;
	int			j;

	j = i;
	while (g_all->temp_str_1[i] && g_all->temp_str_1[i] != ' ')
	{
		if (g_all->temp_str_1[i] == '=')
			break ;
		i++;
	}
	if (g_all->temp_str_1[i] == '\0')
		return (i);
	if (g_all->temp_str_1[i] == ' ' || g_all->temp_str_1[i + 1] == '=')
		return (-1);
	else
	{
		temp = g_all->env;
		if (!(new = malloc(sizeof(t_export))))
			return (0);
		g_all->env = new;
		g_all->env->next = temp;
		ft_bzero_env(g_all);
		return (write_env(j, g_all));
	}
}

int		print_env(t_all *g_all)
{
	t_export	*temp;
	int			i;
	int			j;

	i = 2;
	ft_input_to_temp_str(g_all, 1);
	while (g_all->temp_str_1[++i])
		if (g_all->temp_str_1[i] != ' ' && g_all->temp_str_1[i] != '\0')
			return (print_env_error(g_all, i));
	i = 0;
	temp = g_all->env;
	while (temp && (i = i + 1) >= 0)
		temp = temp->next;
	while (i && (j = -1) == -1)
	{
		temp = g_all->env;
		while (++j < i - 1)
			temp = temp->next;
		env_write(temp);
		temp = temp->next;
		i--;
	}
	return (0);
}

int		ft_bt_export(t_all *g_all)
{
	int i;

	ft_input_to_temp_str(g_all, 1);
	i = 6;
	while (g_all->temp_str_1[i])
	{
		while (g_all->temp_str_1[i] == ' ')
			i++;
		if (is_char(g_all->temp_str_1[i], 1))
		{
			if ((i = save_env(i, g_all)) <= 0)
			{
				if (i == -1)
					write(1, "zsh: bad assignment\n", 20);
			}
			return (0);
		}
		else
		{
			i = wrong_identifier(i, g_all);
			return (1);
		}
	}
	return (check_export(g_all));
}
