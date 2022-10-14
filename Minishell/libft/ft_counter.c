/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_counter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:14:14 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/13 17:31:33 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t  ft_counter(char *str, int c)
{
    size_t  count;
    int     i;

    if (!str)
        return (0);
    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == c)
        {
             while (str[i] == c)
             {
                count++;
                i++;
             }
            return (count);
        }
        i++;
    }
    return (count);
}
