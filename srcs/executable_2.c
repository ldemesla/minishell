/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:20:21 by mabois            #+#    #+#             */
/*   Updated: 2019/11/19 13:20:23 by mabois           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_number_arg_exec(t_all *g_all)
{
	int		i;
	int		mod;
	int		arg_number;

	i = 0;
	mod = SPACE_BEFORE;
	arg_number = 0;
	while (g_all->temp_str_1[i] && g_all->temp_str_1[i] != ' ')
		i++;
	if (g_all->temp_str_1[i] != ' ')
		return (arg_number);
	while (g_all->temp_str_1[i])
	{
		if (mod == SPACE_BEFORE && g_all->temp_str_1[i] != ' ')
		{
			mod = CHAR_BEFORE;
			arg_number++;
		}
		else if (mod == CHAR_BEFORE && g_all->temp_str_1[i] == ' ')
			mod = SPACE_BEFORE;
		i++;
	}
	return (arg_number);
}

char	*ft_create_one_arg_exec(t_all *g_all, int arg_number, int i)
{
	int len;

	len = 0;
	while (g_all->temp_str_1[i + len] && g_all->temp_str_1[i + len] != ' ')
		len++;
	if ((g_all->arg_exec[arg_number] = malloc(sizeof(char) *
			(len + 1))) == NULL)
		return (NULL);
	g_all->arg_exec[arg_number][len--] = '\0';
	while (len >= 0)
	{
		g_all->arg_exec[arg_number][len] = g_all->temp_str_1[i + len];
		len--;
	}
	return (g_all->arg_exec[arg_number]);
}

void	execve_error(t_all *g_all)
{
	char	c;
	int		i;

	c = ' ';
	i = 0;
	ft_putstr("minishell: command not found: ");
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
}

int		ft_create_arg_exec_init(t_all *g_all, int *i, int *mod, int *arg_number)
{
	*i = 0;
	*mod = SPACE_BEFORE;
	*arg_number = 0;
	if ((g_all->arg_exec = malloc(66 * sizeof(char *) *
			(ft_get_number_arg_exec(g_all) + 2))) == NULL)
		return (TRUE);
	g_all->arg_exec[*arg_number] = g_all->cp_argv[0];
	*arg_number = *arg_number + 1;
	g_all->arg_exec[*arg_number] = NULL;
	return (FALSE);
}

void	ft_put_space_in_arg(t_all *g_all, char replace)
{
	int	i;
	int	j;

	i = 0;
	while (g_all->arg_exec[i] != NULL)
	{
		j = 0;
		while (g_all->arg_exec[i][j])
		{
			if (g_all->arg_exec[i][j] == '@')
				g_all->arg_exec[i][j] = replace;
			j++;
		}
		i++;
	}
}
