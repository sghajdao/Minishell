/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:27:34 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/17 08:57:38 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_error(char **a)
{
	int	i;

	i = 1;
	while (a[i])
	{
		if (ft_isdigit(a[i][0]))
		{
			ft_putstr_fd("unset: not a valid identifier: ", STDERR);
			ft_putendl_fd(a[i], STDERR);
		}
		else if (!ft_charscmp(a[i], "+-*/=()~`!@#$^"))
		{
			ft_putstr_fd("unset: not a valid identifier: ", STDERR);
			ft_putendl_fd(a[i], STDERR);
		}
		i++;
	}
}

void	secret_unset(char **a, t_mini *mini)
{
	t_env	*env;
	int		i;

	env = mini->copy_env;
	if (!(a[1]))
		return ;
	i = 1;
	ft_error(a);
	while (env && env->next)
	{
		i = 1;
		while (a[i])
		{
			if (!delete_first_node(&mini->copy_env, a, &i))
				continue ;
			if (ft_strncmp(a[i], env->next->value, \
				env_name_size(env->next->value)) == 0 && \
				ft_strlen(a[i]) == env_name_size(env->next->value))
				cut_and_past(mini, &env);
			(i)++;
		}
		env = env->next;
	}
}

int	ft_unset(char **a, t_mini *mini)
{
	t_env	*env;
	t_env	*tmp;
	int		i;
	int		error;

	secret_unset(a, mini);
	env = mini->env;
	if (!(a[1]))
		return (SUCCESS);
	while (env && env->next)
	{
		i = 1;
		while (a[i])
		{
			if (!delete_first_node(&mini->env, a, &i))
				continue ;
			if (ft_strncmp(a[i], env->next->value, \
				env_name_size(env->next->value)) == 0 && \
				ft_strlen(a[i]) == env_name_size(env->next->value))
				cut_and_past(mini, &env);
			i++;
		}
		env = env->next;
	}
	return (SUCCESS);
}
