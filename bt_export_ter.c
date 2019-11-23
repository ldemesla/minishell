/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_export_ter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:12:11 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/19 15:33:36 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env(char *s, t_all *g_all)
{
	t_export *temp;
	t_export *last;

	temp = g_all->env;
	last = 0;
	while (temp)
	{
		if (ft_strcmp(s, temp->name))
		{
			if (last == 0)
				g_all->env = temp->next;
			else
				last->next = temp->next;
			free(temp);
			return ;
		}
		last = temp;
		temp = temp->next;
	}
}

int		print_env_error(t_all *g_all, int i)
{
	write(1, "env: ", 5);
	if (g_all->temp_str_1[i] == '\'' || g_all->temp_str_1[i] == '\"')
		i++;
	while (g_all->temp_str_1[i] != ' ' && g_all->temp_str_1[i] != '\0' &&
	g_all->temp_str_1[i] != '\'' && g_all->temp_str_1[i] != '\"')
		write(1, &g_all->temp_str_1[i++], 1);
	write(1, ": No such file or directory\n", 28);
	return (127);
}

void	env_write(t_export *temp)
{
	ft_putstr(temp->name);
	write(1, "=", 1);
	ft_putstr(temp->value);
	write(1, "\n", 1);
}

int		quote_error(void)
{
	write(1, "unset: : invalid parameter name\n", 32);
	return (127);
}

int		print_env_export(t_all *g_all)
{
	t_export	*temp;
	int			i;
	int			j;

	i = 5;
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
