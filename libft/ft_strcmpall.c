/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:41:07 by sghajdao          #+#    #+#             */
/*   Updated: 2022/09/30 13:44:28 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmpall(char *str, int start, int c)
{
    while (str[start] && str[start] == c)
        start++;
    if (str[start] != '\0')
        return (1);
    else
        return (0);
}
