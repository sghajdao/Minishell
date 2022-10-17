/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:35:55 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/17 08:59:00 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

size_t	env_name_size(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

void	delete_node(t_mini *mini, t_env *env)
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

int	delete_first_node(t_env **env, char **a, int *i)
{
	t_env	*tmp;

	if (!env || !*env)
		return (0);
	if (ft_strncmp(a[*i], (*env)->value, ft_strlen(a[*i])) == 0)
	{
		tmp = *env;
		*env = (*env)->next;
		ft_memdel(tmp->value);
		ft_memdel(tmp);
		++(*i);
		return (SUCCESS);
	}
	return (ERROR);
}

void	cut_and_past(t_mini *mini, t_env **env)
{
	t_env	*tmp;

	tmp = (*env)->next->next;
	delete_node(mini, (*env)->next);
	(*env)->next = tmp;
}
