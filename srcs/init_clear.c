/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:04:19 by mabois            #+#    #+#             */
/*   Updated: 2019/11/20 10:35:57 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_temp_str(t_all *g_all, int id)
{
	int	i;

	i = 0;
	while (i < MAX_LEN_TEMP_STR)
	{
		if (id == 1)
			g_all->temp_str_1[i] = '\0';
		if (id == 2)
			g_all->temp_str_2[i] = '\0';
		else
			g_all->temp_str_3[i] = '\0';
		i++;
	}
}

void	ft_clear_arg_exec(t_all *g_all)
{
	int i;

	i = 1;
	if (g_all->arg_exec != NULL)
	{
		while (g_all->arg_exec[i] != NULL)
		{
			free(g_all->arg_exec[i]);
			g_all->arg_exec[i] = NULL;
			i++;
		}
		free(g_all->arg_exec);
		g_all->arg_exec = NULL;
	}
}

void	ft_init_str_for_pipe(t_all *g_all)
{
	int i;

	i = 0;
	while (i < MAX_LEN_STR_FOR_PIPE)
	{
		g_all->str_for_pipe[i] = '\0';
		i++;
	}
}

int		ft_init_all(t_all *g_all)
{
	int	i;

	i = 0;
	g_all->in_exec = FALSE;
	g_all->input = NULL;
	g_all->g_env_var = NULL;
	g_all->start = 0;
	g_all->end = 0;
	g_all->ret = 0;
	g_all->arg_exec = NULL;
	g_all->env = NULL;
	g_all->last_is_pipe = FALSE;
	g_all->new_line_signal = FALSE;
	g_all->last_is_echo = 0;
	g_all->no_prompt = FALSE;
	g_all->bks = 0;
	g_all->x_q = FALSE;
	g_all->stdin_cpy = dup(0);
	g_all->ctrd = FALSE;
	while (i < MAX_LEN_PATH)
	{
		g_all->current_path[i] = '\0';
		i++;
	}
	return (1);
}

void	ft_init_exec_path(t_all *g_all)
{
	int i;

	i = 0;
	while (i < MAX_LEN_EXEC_PATH)
	{
		g_all->exec_path[i] = '\0';
		i++;
	}
}
