/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_tools_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabois <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:02:40 by mabois            #+#    #+#             */
/*   Updated: 2019/11/20 18:32:27 by ldemesla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

char	*ft_new_empty_string(void)
{
	char	*str;

	if ((str = malloc(sizeof(char) * 1)) == NULL)
		return (NULL);
	*str = '\0';
	return (str);
}

char	*ft_add_char(char **str, char c)
{
	int		i;
	char	*new_str;

	if ((new_str = malloc(sizeof(char) * (ft_strlen(*str) + 2))) == NULL)
	{
		free(*str);
		return (NULL);
	}
	i = 0;
	while (str[0][i])
	{
		new_str[i] = str[0][i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(*str);
	*str = new_str;
	return (*str);
}

int		ft_compare_str(char *str_1, int limit, char *str_2)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (str_1[j] == ' ')
		j++;
	while (i < limit && str_1[j] && str_2[i])
	{
		if (str_1[j] != str_2[i])
			return (FALSE);
		i++;
		j++;
	}
	if (str_1[j] != ' ' && str_1[j] != '\0' && str_1[i] != '\\'
	&& str_1[j] != '$')
		return (FALSE);
	if (i != limit)
		return (FALSE);
	return (1);
}
