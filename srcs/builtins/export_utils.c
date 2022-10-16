/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:35:32 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/16 15:35:33 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	add_to_env(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		if (!env->value)
			return (ERROR);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	if (!new->value)
		return (ERROR);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

void	get_env_name(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && (ft_strlen(src) < BUFF_SIZE) && src[i] != '=' && src[i] != '+')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	already_exist_in_env(t_env *env, char *args)
{
	char	env_name[BUFF_SIZE];
	char	var_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			if (ft_search(args, '='))
			{
				ft_memdel(env->value);
				env->value = ft_strdup(args);
				if (!env->value)
					return (ERROR);
			}
			return (1);
		}
		env = env->next;
	}
	return (SUCCESS);
}

void	concat(char **env, t_env *e)
{
	char	*to_add;
	char	name[BUFF_SIZE];
	char	*old_value;
	char	*copy;

	to_add = ft_strdup(ft_strchr(*env, '+') + 2);
	if (!to_add)
		return ;
	get_env_name(name, *env);
	old_value = get_env_value(name, e);
	copy = ft_strjoin(name, "=");
	free(*env);
	*env = ft_strjoin(copy, old_value);
	free(old_value);
	free(copy);
	copy = ft_strjoin(*env, to_add);
	free(to_add);
	free(*env);
	*env = ft_strdup(copy);
	if (!*env)
		return ;
	free(copy);
}
