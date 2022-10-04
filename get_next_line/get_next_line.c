/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:54:12 by sghajdao          #+#    #+#             */
/*   Updated: 2022/09/30 17:01:53 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *str)
{
	int		len;
	int		x;
	char	*line;

	len = 0;
	if (*str == '\0')
		return (NULL);
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	line = (char *)malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	x = 0;
	while (x < len)
	{
		line[x] = str[x];
		x++;
	}
	line[x] = '\0';
	return (line);
}

static char	*after(char *str)
{
	char	*res;
	int		start;
	int		i;

	start = 0;
	while (str[start] && str[start] != '\n')
		start++;
	if (str[start] == '\n')
		start++;
	if (str[start] == '\0')
	{
		free(str);
		return (NULL);
	}
	res = malloc(sizeof(char) * (ft_strlen(str) - start + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[start])
		res[i++] = str[start++];
	res[i] = '\0';
	free(str);
	return (res);
}

static char	*read_line(char *str, int fd)
{
	int		byte;
	char	*buff;

	buff = malloc(42 + 1 * sizeof(char));
	if (!buff)
		return (NULL);
	byte = 1;
	while (byte > 0 && ft_search(str) == -1)
	{
		write(1, "> ", 2);
		byte = read(fd, buff, 42);
		if (byte == 0)
			break ;
		if (byte == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[byte] = '\0';
		str = my_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0)
		return (NULL);
	str = read_line(str, fd);
	if (!str)
		return (NULL);
	line = get_line(str);
	str = after(str);
	return (line);
}