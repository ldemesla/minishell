/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:03:06 by mabois            #+#    #+#             */
/*   Updated: 2019/11/20 18:38:05 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_all(t_all *g_all)
{
	int i;

	if (g_all->ctrd == FALSE && g_all->input != NULL)
	{
		free(g_all->input);
		g_all->input = NULL;
	}
	i = 1;
	if (g_all->arg_exec != NULL)
	{
		while (g_all->arg_exec[i] != NULL)
		{
			free(g_all->arg_exec[i]);
			i++;
		}
		free(g_all->arg_exec);
		g_all->arg_exec = NULL;
	}
}

void	ft_exit(int num)
{
	char	del[2];
	int		stdin_cpy;

	stdin_cpy = dup(0);
	num = 0;
	del[0] = 127;
	del[0] = '\0';
	if (g_all.in_exec == FALSE)
		ft_putstr("\b\b  \b\b");
	ft_putstr("\n");
	g_all.s_q = FALSE;
	g_all.d_q = FALSE;
	g_all.x_q = TRUE;
	close(0);
}

void	ft_exit_final(t_all *g_all)
{
	ft_clean_all(g_all);
	ft_lstclear(&g_all->env);
	exit(0);
}

void	ft_exit_final_2(int num)
{
	int		i;

	num = 0;
	ft_putstr("  \b\b");
	i = 0;
	while (g_all.input[i])
	{
		write(1, "\b", 1);
		i++;
	}
	i = 0;
	while (g_all.input[i])
	{
		write(1, g_all.input + i, 1);
		i++;
	}
	num = 0;
	if (g_all.input[0] == '\0')
		ft_exit_final(&g_all);
}

void	ft_exit_final_3(int num)
{
	num = 0;
	if (g_all.in_exec == FALSE)
		ft_putstr("\b\b  \b\b");
	else
		ft_putstr("[1]    42983 quit       by ctr-\\\n");
}
