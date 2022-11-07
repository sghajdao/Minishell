/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:31:57 by sghajdao          #+#    #+#             */
/*   Updated: 2022/11/07 17:28:55 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_search(char *str, int c)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c && c == '+')
			++j;
		else if (str[i] == c && c != '+')
			return (1);
		i++;
	}
	if (j == 1)
		return (1);
	return (0);
}
