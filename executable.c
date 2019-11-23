/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:20:08 by mabois            #+#    #+#             */
/*   Updated: 2019/11/19 13:20:10 by mabois           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_create_arg_exec(t_all *g_all)
{
	int		i;
	int		mod;
	int		arg_number;

	if (ft_create_arg_exec_init(g_all, &i, &mod, &arg_number) == TRUE)
		return (NULL);
	while (g_all->temp_str_1[i] && g_all->temp_str_1[i] != ' ')
		i++;
	if (g_all->temp_str_1[i] != ' ')
		return (g_all->arg_exec);
	while (g_all->temp_str_1[i])
	{
		if (mod == SPACE_BEFORE && g_all->temp_str_1[i] != ' ')
		{
			mod = CHAR_BEFORE;
			if (ft_create_one_arg_exec(g_all, arg_number, i) == NULL)
				return (NULL);
			arg_number++;
		}
		else if (mod == CHAR_BEFORE && g_all->temp_str_1[i] == ' ')
			mod = SPACE_BEFORE;
		i++;
	}
	g_all->arg_exec[arg_number] = NULL;
	return (g_all->arg_exec);
}

void	ft_execve_child(t_all *g_all, int pdes[2], int *fd)
{
	if (g_all->last_is_pipe == TRUE && (g_all->mod == '|' || g_all->mod == '>'))
	{
		*fd = open("pip_tampon", O_TRUNC | O_WRONLY);
		dup2(pdes[0], STDIN_FILENO);
		dup2(*fd, STDOUT_FILENO);
		close(pdes[1]);
	}
	else if (g_all->last_is_pipe == TRUE)
	{
		dup2(pdes[0], STDIN_FILENO);
		close(pdes[1]);
	}
	else if (g_all->mod == '|' || g_all->mod == '>')
	{
		dup2(pdes[1], STDOUT_FILENO);
		close(pdes[0]);
	}
	execve(g_all->exec_path, g_all->arg_exec, NULL);
	execve_error(g_all);
	exit(EXIT_FAILURE);
}

void	ft_execve_father(t_all *g_all, int pdes[2],
		char buffer_temp[MAX_LEN_BUFFER_TEMP], int *fd)
{
	int ret;

	close(pdes[1]);
	wait(&g_all->ret);
	g_all->ret = g_all->ret >> 8;
	if (g_all->last_is_pipe == TRUE && (g_all->mod == '|' || g_all->mod == '>'))
	{
		*fd = open("pip_tampon", O_RDONLY);
		ret = read(*fd, buffer_temp, MAX_LEN_BUFFER_TEMP);
		buffer_temp[ret] = 0;
		close(*fd);
		ft_init_str_for_pipe(g_all);
		ft_strcpy(g_all->str_for_pipe, buffer_temp);
	}
	else if (g_all->mod == '|' || g_all->mod == '>')
	{
		ret = read(pdes[0], buffer_temp, MAX_LEN_BUFFER_TEMP);
		buffer_temp[ret] = 0;
		close(pdes[0]);
		ft_init_str_for_pipe(g_all);
		ft_strcpy(g_all->str_for_pipe, buffer_temp);
	}
	else
		close(pdes[0]);
}

void	ft_execve_init_all(t_all *g_all)
{
	int ret;

	ft_input_to_temp_str(g_all, 0);
	ret = ft_parse_quote_cd(g_all, 0);
	ft_init_temp_str(g_all, 1);
	ft_strcpy(g_all->temp_str_1, g_all->temp_str_2);
	ft_init_temp_str(g_all, 2);
	if (ft_search_exec_path_abs_rel(g_all) == TRUE)
		ft_search_exec_path(g_all, 0, 0, 0);
	ft_clear_arg_exec(g_all);
	ft_create_arg_exec(g_all);
	ft_put_space_in_arg(g_all, ' ');
}

int		ft_execve(t_all *g_all, int fd)
{
	pid_t		id_fork;
	int			pdes[2];
	char		buffer_temp[MAX_LEN_BUFFER_TEMP];

	ft_execve_init_all(g_all);
	if (g_all->last_is_pipe == TRUE && (g_all->mod == '|' || g_all->mod == '>'))
	{
		pipe(pdes);
		write(pdes[1], g_all->str_for_pipe, ft_strlen(g_all->str_for_pipe));
		fd = open("pip_tampon", O_TRUNC | O_WRONLY);
		close(fd);
	}
	else if (g_all->last_is_pipe == TRUE)
	{
		pipe(pdes);
		write(pdes[1], g_all->str_for_pipe, ft_strlen(g_all->str_for_pipe));
	}
	else if (g_all->mod == '|' || g_all->mod == '>')
		pipe(pdes);
	id_fork = fork();
	if (id_fork == 0)
		ft_execve_child(g_all, pdes, &fd);
	else
		ft_execve_father(g_all, pdes, buffer_temp, &fd);
	return (0);
}
