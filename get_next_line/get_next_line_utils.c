/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:54:26 by sghajdao          #+#    #+#             */
/*   Updated: 2022/09/30 16:44:46 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_search(char *buff)
{
	unsigned int	i;

	i = 0;
	if (!buff)
		return (-1);
	while (buff[i])
	{
		if (buff[i] && buff[i] == '\n')
			return (1);
		i++;
	}
	return (-1);
}

char	*my_strjoin(char *s1, char const *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	x;

	if (!s1)
		s1 = ft_strdup("");
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	x = 0;
	while (s2[x])
		str[i++] = s2[x++];
	str[i] = 0;
	free(s1);
	return (str);
}
