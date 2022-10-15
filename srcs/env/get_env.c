/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:30:01 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/13 17:17:38 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	is_valid_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int	is_valid_env_str(const char *env)
{
	int	i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (0);
	while (env[i] && env[i] != '=')
	{
		if (ft_isalnum(env[i]) == 0)
			return (-1);
		i++;
	}
	if (env[i] != '=' || (env[i] == '=' && \
		(env[i + 1] == '\0' || env[i + 1] == ' ')))
		return (2);
	return (1);
}

int	env_val_length(const char *env)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	*envValueFromStr(char *env)
{
	int		size_alloc;
	int		i;
	int		j;
	char	*env_value;

	size_alloc = env_val_length(env) + 1;
	if (!(env_value = malloc(sizeof(char) * size_alloc)))
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*get_env_value(char *arg, t_env *env)
{
	char	name[BUFF_SIZE];
	char	*value;

	value = ft_strdup("");
	if (!value)
		return (NULL);
	while (env && env->value)
	{
		get_env_name(name, env->value);
		if (ft_strcmp(arg, name) == 0)
		{
			ft_memdel(value);
			value = envValueFromStr(env->value);
			return (value);
		}
		env = env->next;
	}
	return (value);
}
