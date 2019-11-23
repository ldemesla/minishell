/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:11:38 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/19 15:26:47 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_data(t_all *g_all)
{
	if (g_all->env == 0)
	{
		if (!(g_all->env = malloc(sizeof(t_export))))
			return (0);
	}
	return (1);
}

int		wrong_identifier(int i, t_all *g_all)
{
	if (g_all->temp_str_1[i] == '\0')
	{
		print_env_export(g_all);
		return (i);
	}
	write(1, "export: not an identifier: ", 27);
	while (g_all->temp_str_1[i] != ' ' && g_all->temp_str_1[i] != '\0' &&
	g_all->temp_str_1[i] != '=')
		write(1, &g_all->temp_str_1[i++], 1);
	if (g_all->temp_str_1[i] == '=')
	{
		while (g_all->temp_str_1[i] != ' ' || g_all->temp_str_1[i] != '\0')
			i++;
	}
	write(1, "\n", 1);
	return (i);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	delete_double(t_all *g_all)
{
	t_export *temp;
	t_export *temp2;
	t_export *last;

	temp = g_all->env->next;
	temp2 = 0;
	last = g_all->env;
	while (temp)
	{
		if (ft_strcmp(temp->name, g_all->env->name))
		{
			temp2 = temp->next;
			free(temp);
			last->next = temp2;
		}
		last = temp;
		temp = temp->next;
	}
}

int		unset(t_all *g_all)
{
	int		i;
	int		j;
	char	env[50];

	i = 0;
	j = 0;
	while (i < 50)
		env[i++] = '\0';
	i = 5;
	ft_input_to_temp_str(g_all, 1);
	while (g_all->temp_str_1[i] == ' ')
		i++;
	if ((g_all->temp_str_1[i] == '\'' || g_all->temp_str_1[i] == '\"') &&
	(g_all->temp_str_1[i + 1] == '\'' || g_all->temp_str_1[i + 1] == '\"'))
		return (quote_error());
	while (g_all->temp_str_1[i])
		env[j++] = g_all->temp_str_1[i++];
	remove_env(env, g_all);
	return (0);
}
