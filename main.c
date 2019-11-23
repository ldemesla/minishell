/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:47:53 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/20 09:58:21 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_next_end(t_all *g_all)
{
	int i;

	i = 0;
	if (ft_check_commas())
		return ;
	while (ft_is_end_char(g_all->input[g_all->start + i]) == FALSE)
		i++;
	g_all->mod = g_all->input[g_all->start + i];
	if (g_all->mod == '>' && g_all->input[g_all->start + i + 1] == '>')
		g_all->mod = 'r';
	g_all->end = g_all->start + i;
	g_all->no_prompt = FALSE;
}

void	set_last(t_all *g_all)
{
	if (g_all->mod == '|')
	{
		g_all->last_is_pipe = TRUE;
		g_all->last_is_rdr = FALSE;
	}
	else if (g_all->mod == '>')
	{
		g_all->last_is_rdr = 1;
		g_all->last_is_pipe = FALSE;
	}
	else if (g_all->mod == 'r')
	{
		g_all->last_is_rdr = 2;
		g_all->last_is_pipe = 0;
	}
	else if (g_all->mod == '<')
	{
		g_all->last_is_rdr = 3;
		g_all->last_is_pipe = 0;
	}
	else
	{
		g_all->last_is_rdr = FALSE;
		g_all->last_is_pipe = FALSE;
	}
}

void	exec_input(t_all *g_all)
{
	if (ft_strlen(g_all->input + g_all->start) == 0)
		return ;
	else if (g_all->last_is_rdr > 0)
		create_file(g_all);
	else if (ft_compare_str(g_all->input + g_all->start, 4, "exit ") == TRUE)
		ft_exit_final(g_all);
	else if (ft_compare_str(g_all->input + g_all->start, 3, "pwd ") == TRUE)
		ft_bt_pwd(g_all);
	else if (ft_compare_str(g_all->input + g_all->start, 4, "echo ") == TRUE)
		g_all->ret = ft_bt_echo(g_all);
	else if (ft_compare_str(g_all->input + g_all->start, 2, "cd ") == TRUE)
		g_all->ret = ft_bt_cd(g_all);
	else if (ft_compare_str(g_all->input + g_all->start, 6, "export ") == TRUE)
		g_all->ret = ft_bt_export(g_all);
	else if (ft_compare_str(g_all->input + g_all->start, 3, "env ") == TRUE)
		g_all->ret = print_env(g_all);
	else if (ft_compare_str(g_all->input + g_all->start, 5, "unset ") == TRUE)
		g_all->ret = unset(g_all);
	else
	{
		g_all->no_prompt = TRUE;
		ft_execve(g_all, 0);
	}
}

int		ft_execute_input(t_all *g_all)
{
	g_all->start = 0;
	g_all->end = 0;
	g_all->mod = '?';
	while (g_all->mod != '\0')
	{
		ft_check_next_end(g_all);
		exec_input(g_all);
		g_all->no_prompt = FALSE;
		set_last(g_all);
		g_all->start = g_all->end + 1;
		if (g_all->mod == 'r')
			g_all->start++;
	}
	return (FALSE);
}

int		main(int argc, char **argv)
{
	(void)argc;
	signal(SIGINT, &ft_exit);
	signal(SIGQUIT, &ft_exit_final_3);
	if (!ft_init_all(&g_all))
		return (0);
	g_all.cp_argv = argv;
	ft_bt_export_path(&g_all);
	while (TRUE)
	{
		if (g_all.ctrd == FALSE)
			ft_putstr(PROMPT);
		g_all.input = ft_get_input(&g_all, 0, '@');
		if (g_all.input == NULL || g_all.ctrd == TRUE)
			ft_exit_final_2(66);
		g_all.in_exec = TRUE;
		if (g_all.x_q == FALSE && g_all.input != NULL && g_all.ctrd == FALSE)
			ft_execute_input(&g_all);
		g_all.in_exec = FALSE;
		g_all.x_q = FALSE;
		ft_clean_all(&g_all);
		dup2(g_all.stdin_cpy, 0);
		ft_clear_arg_exec(&g_all);
	}
}
