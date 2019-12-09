/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldemesla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:42:33 by ldemesla          #+#    #+#             */
/*   Updated: 2019/11/21 15:48:31 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_input_init(t_all *g_all, char **input, char *last)
{
	if (g_all->ctrd == FALSE)
	{
		g_all->s_q = FALSE;
		g_all->d_q = FALSE;
	}
	*input = g_all->input;
	if (g_all->ctrd == FALSE)
		*input = ft_new_empty_string();
	*last = '\0';
	g_all->ctrd = FALSE;
}

void	ft_quote_cut(t_all *g_all)
{
	g_all->s_q = (g_all->d_q == TRUE) ? FALSE : g_all->s_q;
	g_all->d_q = (g_all->d_q == TRUE ||
	g_all->s_q == TRUE) ? FALSE : TRUE;
}

char	*ft_get_input(t_all *g_all, int ret, char last)
{
	char	*input;
	char	buffer;

	ft_get_input_init(g_all, &input, &last);
	while ((ret = read(0, &buffer, 1)))
	{
		if (g_all->x_q == TRUE)
			return (input);
		if (buffer == '\\' && g_all->s_q == 0 && g_all->d_q == 0)
			ret = new_term(&buffer);
		if (buffer == '\'' && last != '\\')
			g_all->s_q = (g_all->s_q == TRUE ||
			g_all->d_q == TRUE) ? FALSE : TRUE;
		else if (buffer == '\"' && last != '\\')
			ft_quote_cut(g_all);
		if (buffer == '\n' && (g_all->s_q == TRUE || g_all->d_q == TRUE))
			ft_putstr(PROMPT_QUOTE);
		if (buffer == '\n' && g_all->s_q == FALSE && g_all->d_q == FALSE)
			return (input);
		else if (ret == 1 && ((ret = 0) == 0))
			ft_add_char(&input, buffer);
		last = buffer;
	}
	g_all->ctrd = TRUE;
	return (input);
}

int		ft_is_end_char(char c)
{
	if (c == '\0' || c == '|' || c == '>')
		return (TRUE);
	return (FALSE);
}

int		set_mod(int i)
{
	g_all.mod = ';';
	g_all.end = i;
	g_all.no_prompt = FALSE;
	return (1);
}
