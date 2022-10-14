/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:27:34 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/14 17:34:12 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static size_t	env_name_size(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	delete_node(t_mini *mini, t_env *env)
{
	if (env->next == NULL && mini->env == env)
	{
		ft_memdel(mini->env->value);
		mini->env->value = NULL;
		mini->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

void	secret_unset(char **a, t_mini *mini)
{
	t_env	*tmp;
	t_env	*env;
	int		i;

	env = mini->copy_env;
	if (!(a[1]))
		return ;
	while (env && env->next)
	{
		i = 1;
		while (a[i])
		{
			if (ft_strncmp(a[i], env->next->value, \
				env_name_size(env->next->value)) == 0 && ft_strlen(a[i]) == env_name_size(env->next->value))
			{
				tmp = env->next->next;
				delete_node(mini, env->next);
				env->next = tmp;
			}
			i++;
		}
		env = env->next;
	}
}

int	ft_unset(char **a, t_mini *mini)
{
	t_env	*tmp;
	t_env	*env;
	int		i;

	secret_unset(a, mini);
	env = mini->env;
	if (!(a[1]))
		return (SUCCESS);
	while (env && env->next)
	{
		i = 1;
		while (a[i])
		{
			if (ft_strncmp(a[i], env->next->value, \
				env_name_size(env->next->value)) == 0 && ft_strlen(a[i]) == env_name_size(env->next->value))
			{
				tmp = env->next->next;
				delete_node(mini, env->next);
				env->next = tmp;
			}
			i++;
		}
		env = env->next;
	}
	return (SUCCESS);
}
