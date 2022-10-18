/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:35:05 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/18 10:07:39 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cd_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static void	copy_value(t_env *env, size_t len, char *oldpwd)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (env->value[i++])
	{
		if (i > (int)len)
			oldpwd[j++] = env->value[i];
	}
	oldpwd[j] = '\0';
}

char	*get_path_from_env(t_env *env, const char *var, size_t len)
{
	int		s_alloc;
	char	*oldpwd;

	if (!env)
		return (NULL);
	while (env->next != NULL && env)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			oldpwd = malloc(sizeof(char) * s_alloc + 1);
			if (!oldpwd)
				return (NULL);
			copy_value(env, len, oldpwd);
			ft_putendl_fd(oldpwd, STDOUT);
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}
